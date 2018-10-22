This is some code that accompanies the Galaxy Explorations Tips &
Techniques article (vol 2, Issue 4) on using events to slice up long
computations to prevent the user interface from locking up.

I had originally intended for this to be a minimal sample showing the
use of events, but had succumbed to the wouldntItBeCoolitis.  i.e.
"Wouldn't it be cool if the mechanism for driving a divided calculation
were encapsulated", and "wouldn't it be cool to show the percentage status
of the calculation being done", and "wouldn't it be cool to resurrect some
cool mathematical constructions I did during college."  So, what started
out as a 2-hour weekend project turned into  a 2-day weeknd project.

Here's the moving parts:

xpacemaker.h
pacemaker.c  -- this is an encapsulaton of the event-based heartbeat-style
                working engine.  You subclass xpacemaker, and override
                xpacemakerDO_WORK.  Folks using your calculation object then
                just need to create your object and tell it to start.  There
                exist notifications so the programmers can inform their users
                of the status of your work

xstatus.h
status.c  -- implements a status object.  It has two display modes:
               * percentage - a rectangle fills in to reflect the percentage
                              the work that's being completed.
               * barberpole - This is a set of lines that seem to "spin" as
                              the work is being done.
             If you're showing the status of an operation where you know the
             bounds (like calculating the colors of pixels in an image), you'd
             use the percentage mode.  If you don't know the bounds (like
             walking a big networked file system), you'd use the barberpole
             mode.  The user gets feedback that work is actually being done
             (e.g. you're not locked up), but you don't have to commit on
             a particular percentage being done

xgroup.h
group.c   -- this is a subclass of xpacemaker that calculates images based
             on (wrapping) integer math.  What's done is the pixel color 
             index for each point in the image is calculated by a function
             based on the (x,y) position of the point.  This value is then
             truncated to 8 bits and used as a color table index.  You can get
             some rather nice images using some creative arithmatic.
             Its main purpose is to show how to subclass xpacemaker and make
             your own event-driven calculation.  This thing is called "group"
             because I was studying Groups in Abstract Algebra at the time.
             There's no correlation to Groups in the mathematical sense.

main.c -- contains main() and a driver program that uses all of these.
          It presents a dialog with a set ofradio buttons to choose a 
          group calculation function, and a set of radio buttons to choose
          the status display style (e.g. percentage, barberpole, and none, so
          you can see the effects of locking up some machines doing
          calculations.)

Each x*.h file has comments in it on how to use each object.


and here is the text of the article:


One family of questions that seems to float by fairly often on the
galaxy-users mailing list and our support group is "I have a long
calculation to do.  How do I let the user terminate this processing?"
Related questions are also "How do I keep my user interface from
locking up while I'm doing these calculations?" and "How can I show
the progress to the user while I'm working?"

Before diving into these burning questions, though, let's take a step
back and see how Galaxy programs work.  Most every program you write
will have the incantation "veventProcess ();" in it.  veventProcess is
a loop inside of Galaxy that surveys the world surrounding it and
initiates actions based upon what it sees.  Stuff it looks for
includes activity on communication channels, platform-specific timing
mechanisms for driving vtimers, and the user banging away through the
windowing system.  When veventProcess detects activity on a socket, it
turns control over to the communications manager to handle it.
Similarly, when it detects activity with the mouse or a window needing
an update, it turns control over to the dialog manager who then
figures out the proper dialog items to redraw or whom to give the
mouse event to.

So, if you're doing a long calculation or some other "blocking"
operation, the user interface objects in your windows will no longer
respond.  The code in veventProcess will not be executed, meaning
windows that need redrawing won't be redrawn and mouse events won't
get processed.  They'll just take a number anda sit around in a queue
waiting to be serviced.  The program will appear to the user that it
has locked up.  On some platforms using a cooperative multitasking
model (such as the Macintosh), this will also prevent other programs
from running or being switched to, making it appear that the entire machine
has locked up.  In general, this is a particularly user-hostile
situation.

On some platforms, you'd spin off a thread to handle the calculation.
Unfortunately, threads are not available on many planforms now, so
some portable mechanism must be used.  The way I'm presenting here is
to use the event manager to drive the calculation: divide the
calcuation into small, easily digestible chunks and let the event
manager call you repeatedly to do an easily digested chunk of your
work.  Since veventProcess will driving things, the rest of the
program (window redrawing and event handling) will continue to work.
The Galaxy Help Compiler (vhelpcmp) uses this technique to compile and
link "in the background" while allowing the user interface to remain
active.

The way you get the event manager to call you repeatedly is to post a
client event, do the work in the event handler (and update any kind of
user-feedback), then repost the event if the work isn't completed.

The mechanism for posting an event (with a hunk of state attached) is this:

void postMyPacemakerEvent (calculationState *state)
{
    vevent *event = veventCreateClient ();
    veventSetTarget (event, myPacemakerFunction);
    veventSetClientData (event, state);

This creates a client event and sets the function to be called when the
event is ultimately handled by the event manager.  The client data is
a pointer to the state of the calculation.  More on that later.

    veventSetPriority (event, veventPRIORITY_MIN);
    veventPost (event);

This sets the event priority to be low, so that user actions and
window redrawing occur before the handling of the event.  If the
priority is too high, the "heartbeat" events will dominate the user
events, thereby defeating the whole reason we're doing this work.
veventPost puts it into the Event Manager's queue for subsequent
handling, as well as transferring owernship of the event to the event
manager.

    vwindowFlushRequests ();

On buffered window systems (such as the X Window System), this causes
drawing requests to actually become rendered on the screen.
In a busy environment (such as when the calculations are being
performed), the drawing requests are flushed at a slower rate causing
sluggishness in the program's windows.

} /* postMyPacemakerEvent */



The event handler (set via veventSetTarget) would look something like
this pseudo-code:

static int myPacemakerFunction (vevent *event)
{
    get our state structure from the event client data pointer

    do some work
    update progress meter if appropriate

    if we're not finished
        post the event using the above code

    return TRUE since we've handled this event

} /* myPacemakerFunction */


It is OK to re-use the event that's passed to this function, just
be sure never to destroy it.  Destroying an event that the event manager
owns can lead to unexpected, and sometimes surprising behavior.

There's one gotcha: terminating the whole process before it runs to
completion.  If you terminate the process (the clicks your "Stop Now!"
button), you'll probably want to destroy the calculation state you've
been keeping around.  The problem with that is that the event is still
in the queue without a clean way to remove it.  The next time the
pacemaker function is called, it'll try to access the freed memory,
which would really be a Bad Thing.  One way to avoid this is to keep a
reference to the event in a convenient place such as the state
structure.  NULL out the client data pointer and check for NULL in
your pacemaker function.  If it is NULL, do nothing and let the event
run down the drain without reposting.  Another way is to set a flag
in the state structure.  If that flag is set when the pacemaker function
is called, destroy the relevant pieces of allocated memory.


Now, what is this calculation state structure I've been talking about?
This is where you store the state of your calculation when you suspend
it, and later use to restore your position.  For instance, in a
Mandelbrot set calculator, this state would contain the (x,y) position
in the image being calculated, a pointer to the image being calculated
(so the pixels colors can be set), and the number of iterations
calculated for this point.  Typically, if the work is non-recursive in
nature, you can put the calculation function's local variables into
the structure and add some preamble/postamble code to save and restore
this state in the calculation code itself.

Things get more complicated with work that is recursive in nature.
The algorithm state that's being stored on the system call stack can't
live there any more.  In order to return control to the event manager,
you'll need to unwind the stack, thereby losing your carefully
constructed state.  To support recursive algorithms, you'll need to
explicitly use a stack to keep the state.  (This is similar to what
you'd have to do to implement a recursive algorithm in FORTRAN).
Using your own stack rather than the system call stack can be turned
into an advantage to the overall reliability to your program.  If you
overflow the stack due to deep recursion, you can easily recover if
you are maintaining the stack (e.g. expand the memory consumed by the
stack or use a "rainy-day" memory cache).  Recovering from an
overflowing system call stack is impossible to do, meaning you'll
most likely crash in this case.


How much work do you do each time through the pacemaker function?  You
don't want to do so much work that the program is blocked, but you
also don't want to do so little work that you spend all of your time
doing event bookkeeping and the program takes forever to do its work.
There are several alternatives.  One is to provide a visual control
and allow the user to decide.  The Help Compiler does this.  You can
tell it "I know what I'm doing.  Lock up my machine for however long
it takes.  I want this to be done ASAP." or tell it "I want to work on
other stuff while you're churning away."  Using this technique,
though, is usually a Bad Idea for software that's aimed for a
non-technical audience.  Another approach is to tune the calculations
done on a per-platform basis via trial-and-error or a more
quantitative route using a code profiler.  A third approach is to time
a small, but representative calculation, and scale the time results so
that each time through the pacemaker takes around than 1/15'th of a
second.


This is all well-and-good, but I know some folks out there are saying
"Where's the code?"  In the Galaxy (C and C++) distribution is a
sample called "progress" which shows a way of doing this
digestible-chunk style of calculation along with a dialog that shows
the progress of the work.  Another sample has been cooked up called
"xpacemaker" that provides a more objectified interface that handles
the gory event details and provides hooks for doing the Real Work and
for notifications that can be used to update status information.  This
sample can be found on the Visix ftp server as well, in the directory
/pub/Galaxy/Samples/C/pacemaker.  A C++ version will be forthcoming.


Mark Dalrymple is the mind responsible for, among other things, the
Galaxy List Manager.  He enjoys diluting liquid soap (OK!) and badger
collecting.  Got any questions that would inspire a cool article?  If
so, send it to "markd@visix.com", and you could win an autographed can
of Spam.

