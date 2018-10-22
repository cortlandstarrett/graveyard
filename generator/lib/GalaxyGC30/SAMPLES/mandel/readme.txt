

Welcome to the DAS Mandelbrot demo!

-------------------------------------------------------------------------

The Mandel sample uses distributed processing techniques (DAS) to
compute a Mandelbrot set using any number of slave processes which may
be resident anywhere on network.  The sample consists of two
parts, Master and Slave.

    Master is the DAS master service for mandelbrot set.  It breaks the
    entire mandelbrot image into cells and then allocates tasks for
    these cells to Slaves, which each takes responsibility for each cell. 
    Master requires at least one Slave running in order to work.

    Slave is the DAS slave service for mandelbrot set.  It computes, 
    draws and sends a cell of the image to Master, which then combines 
    all collected cells into entire mandelbrot image.
    Slave does nothing unless Master is running.

--------------------------------------------------------------------------

To start the Mandel sample:

        1. Start the DAS Service Broker (vdasserv). If you plan to
           start slaves on several systems you will need to start 
           service brokers on each one, all parented to a common
           master broker.

        2. Start any number of Slaves (slave). Three or four Slaves 
           is a good starting point. You can use the preferences
           -Transport and -Port to start up slaves with a particular
           transport/port if you do not wish to use the defaults
	   for your platform.

        3. After the Slaves have displayed their window, start one 
           Master (master).

Master will send portions of the calculation off to all available
Slaves.  The slave will compute its portion of the image, return it to
the Master, and await another request. Slaves display the result of
the last calculation.

After a succesful calculation, mark a rectangle on the Master by
clicking, dragging and releasing. Then press the Zoom In button to
initiate another calculation.

--------------------------------------------------------------------------

Enjoy.



