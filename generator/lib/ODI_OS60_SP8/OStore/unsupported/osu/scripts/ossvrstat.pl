#!/opt/third-party/bin/perl

package ClientMeter;

sub new {
    my $type = shift;
    my $self = [];
    for ($N = 0; $N < 13; $N++) {
	$self->[$N] = 0;
    }
    bless $self, $type;
}

sub nmsgs()      {  my $self = shift; if (@_) { $self->[0]  = shift; } return $self->[0]; }
sub ncallbks()   {  my $self = shift; if (@_) { $self->[1]  = shift; } return $self->[1]; }
sub KB_callbk()  {  my $self = shift; if (@_) { $self->[2]  = shift; } return $self->[2]; }
sub KB_return()  {  my $self = shift; if (@_) { $self->[3]  = shift; } return $self->[3]; }
sub KB_read()    {  my $self = shift; if (@_) { $self->[4]  = shift; } return $self->[4]; }
sub KB_wrtn()    {  my $self = shift; if (@_) { $self->[5]  = shift; } return $self->[5]; }
sub commits()    {  my $self = shift; if (@_) { $self->[6]  = shift; } return $self->[6]; }
sub ro_commits() {  my $self = shift; if (@_) { $self->[7]  = shift; } return $self->[7]; }
sub aborts()     {  my $self = shift; if (@_) { $self->[8]  = shift; } return $self->[8]; }
sub twophase()   {  my $self = shift; if (@_) { $self->[9]  = shift; } return $self->[9]; }
sub lock_to()    {  my $self = shift; if (@_) { $self->[10] = shift; } return $self->[10]; }
sub lock_waits() {  my $self = shift; if (@_) { $self->[11] = shift; } return $self->[11]; }
sub deadlocks()  {  my $self = shift; if (@_) { $self->[12] = shift; } return $self->[12]; }

sub init() {
    my $self = shift;
    my $from = shift;
    my $N = 0;
    for ($N = 0; $N < 13; $N++) {
	$self->[$N] = $from->[$N];
    }
}

package LogMeter;

sub new {
    my $type = shift;
    my $self = [];
    for ($N = 0; $N < 10; $N++) {
	$self->[$N] = 0;
    }
    bless $self, $type;
}

sub mbuf_waits() {  my $self = shift; if (@_) { $self->[0]  = shift; } return $self->[0]; }
sub logrecs()    {  my $self = shift; if (@_) { $self->[1]  = shift; } return $self->[1]; }
sub rec_switch() {  my $self = shift; if (@_) { $self->[2]  = shift; } return $self->[2]; }
sub flushd()     {  my $self = shift; if (@_) { $self->[3]  = shift; } return $self->[3]; }
sub flushr()     {  my $self = shift; if (@_) { $self->[4]  = shift; } return $self->[4]; }
sub KB_data()    {  my $self = shift; if (@_) { $self->[5]  = shift; } return $self->[5]; }
sub KB_record()  {  my $self = shift; if (@_) { $self->[6]  = shift; } return $self->[6]; }
sub KB_prop()    {  my $self = shift; if (@_) { $self->[7]  = shift; } return $self->[7]; }
sub KB_direct()  {  my $self = shift; if (@_) { $self->[8]  = shift; } return $self->[8]; }
sub props()      {  my $self = shift; if (@_) { $self->[9]  = shift; } return $self->[9]; }
sub logsize()    {  my $self = shift; if (@_) { $self->[10]  = shift; } return $self->[10]; }

sub init() {
    my $self = shift;
    my $from = shift;
    my $N = 0;
    for ($N = 0; $N < 11; $N++) {
	$self->[$N] = $from->[$N];
    }
}


package ArgList;

sub new {
    my $type = shift;
    my $self = {};
    my $host = shift;
    my $filename = shift;

    $self->{"SERVER NAME"} = $host;
    $self->{"TIME INTERVAL"} = "60 secs";
    $self->{"NUMBER OF SECONDS"} = 60;
    $self->{"TIME UNIT"} = "seconds";
    $self->{"UNIT DIVISOR"} = 1;
    $self->{"DISPLAY MODE"} = "base0";
    $self->{"SORTED BY"} = "-client";
    $self->{"HEADER DISPLAYED"} = "once";
    $self->{"CLIENT METERS DISPLAYED"} = "activity";
    $self->{"SERVER METERS DISPLAYED"} = "always";
    $self->{"LOG FILENAME"} = "";
    $self->{"METER FILENAME"} = "";
    $self->{"LOGSIZE"} = "absolute";

    if ($filename ne "") {
	open(INFILE, "< $filename") || die("can't open parameter file: $filename\n");
    } else {
#TODO: make portable between NT and UNIX (I believe this works but should use forward or
#      backward slash as appropriate...
	open(INFILE, sprintf("< %s/etc/ossvrstat_%s_parameters.txt",$ENV{OS_ROOTDIR},$host)) ||
        open(INFILE, sprintf("< %s/etc/ossvrstat_parameters.txt",$ENV{OS_ROOTDIR})) ||
        die(sprintf("can't open parameter file: %s/etc/ossvrstat_parameters.txt",$ENV{OS_ROOTDIR}));
    }

    do {
	$_ = <INFILE>;

	$_ =~ /^[ \t]*([^ \t].*[^ \t])[ \t]*:[ \t]*(.*)[ \t]*$/;
	$self->{uc $1} = $2;
	
    } until (eof INFILE);

    close(INFILE);

    
    $_ = <PLOT>; $_ =~ /^[ ]+(\d+) [A-Za-z ]+(\d+)/;

    (lc $self->{"TIME INTERVAL"}) =~ /(\d+)[ \t]*((secs|sec|s|second|seconds)|(m|min|mins|minute|minutes)|(h|hr|hrs|hour|hours))/;
    if ($3 ne "") {
	$self->{"UNIT DIVISOR"} = 1;
	$self->{"NUMBER OF SECONDS"} = $1;
	$self->{"TIME UNIT"} = "secs";
    } elsif ($4 ne "") {
	$self->{"UNIT DIVISOR"} = 60;
	$self->{"NUMBER OF SECONDS"} = $1*60;
	$self->{"TIME UNIT"} = "mins";
    } elsif ($5 ne "") {
	$self->{"UNIT DIVISOR"} = 3600;
	$self->{"NUMBER OF SECONDS"} = $1*60*60;
	$self->{"TIME UNIT"} = "hrs";
    }

    $self->{"HEADER DISPLAYED"}        = lc $self->{"HEADER DISPLAYED"};
    $self->{"CLIENT METERS DISPLAYED"} = lc $self->{"CLIENT METERS DISPLAYED"};
    $self->{"SERVER METERS DISPLAYED"} = lc $self->{"SERVER METERS DISPLAYED"};
    $self->{"DISPLAY MODE"} = lc $self->{"DISPLAY MODE"};
    if ($self->{"DISPLAY MODE"} eq "delta"){
	$self->{"BASE"} = "LAST";
    } else {
	$self->{"BASE"} = "base0";
    }
    bless $self, $type;
}

sub hostname() {  my $self = shift; if (@_) { $self->{"SERVER NAME"}  = shift; } return $self->{"SERVER NAME"}; }
sub doServer() {  my $self = shift; if ($self->{"SERVER METERS DISPLAYED"} eq "never") { return 0; } else { return 1; }}
sub doClient() {  my $self = shift; if ($self->{"CLIENT METERS DISPLAYED"} eq "never") { return 0; } else { return 1; }}
sub base()     { my $self = shift; return $self->{"BASE"}; }

package main;

sub geterror() {
    format_top_name STDERR "STDOUT_TOP0";
    format_name     STDERR "USAGEERR";
    write STDERR;
    die("\n");
}

# $~ format_name
# $^ format_top_name
# $% format_page_name
# $= format_lines_per_page
# $| output_autoflush
# $^L format_formfeed

use FileHandle;
use Sys::Hostname;
my $host       = hostname;
my $parameters = "";
my $basetime   = time();
my $sortBy     = "client";
my $sortDir    = 1;

$^L = "";
format_top_name STDOUT "STDOUT_TOP0";

while ($arg = shift) {
    if ($arg =~ /^-/) {
	if ($arg eq "-h") {
            my $name = shift;
            if ($name ne "localhost") { $host = $name; }
	} elsif ($arg eq "-f") {
	    $parameters = shift;
	} else {
	    geterror();
	}
    } else {
	geterror();
    }
}

$ARGS = ArgList->new($host,$parameters);
$host = $ARGS->hostname();
my $filename = $ARGS->{"METER FILENAME"};
if ($filename ne "") {
  $filename =~ s/%h/$host/;
  $filename =~ s/%p/$$/;
  open(METERFILE, "> $filename") || die("can't create file: $filename\n");
  $METERFILE = METERFILE;
} else {
  $METERFILE = STDOUT;
}

$filename = $ARGS->{"LOG FILENAME"};
if ($filename ne "") {
  $filename =~ s/%h/$host/;
  $filename =~ s/%p/$$/;
  open(LOGFILE, "> $filename") || die("can't create file: $filename\n");
  format_top_name LOGFILE "LOGTOP_FORMAT";
  format_name LOGFILE "LOGFORMAT";
}

my $secs = $ARGS->{"NUMBER OF SECONDS"} + 0;

my $client = $ARGS->{"CLIENT METERS DISPLAYED"};
if ($client eq "always") {
  $client = 1;
} elsif ($client eq "activity") {
  $client = 2;
} elsif ($client eq "message") {
  $client = 3;
} elsif ($client eq "callback") {
  $client = 4;
}

$Hash{""}{OUT}   = ClientMeter->new;
$Hash{""}{LAST}  = ClientMeter->new;
$Hash{""}{base0} = ClientMeter->new;
$Log{OUT}   = LogMeter->new;
$Log{LAST}  = LogMeter->new;
$Log{base0} = LogMeter->new;

if ($ARGS->hostname() ne "") {
        if ($ARGS->{"HEADER DISPLAYED"} ne "never") {
            format_top_name $METERFILE "STDOUT_TOP1";
	}
        format_name $METERFILE "STDOUT1";

        if ($ARGS->{"DISPLAY MODE"} eq "base0") {

            $hostname = $ARGS->hostname();
            open(PLOT, "ossvrstat -meters -clients $hostname |") 
	         || die("can't pipe ossvrstat $hostname\n");

	    &doServer();
	    &doClient();

	    foreach $c (keys %Identity) {
                $Hash{$c}{base0}->init($Hash{$c}{LAST});
	    }
            $Log{base0}->init($Log{LAST});
            close(PLOT);
	}

        $loop = -1; # loop is incremented in doonce...
	for (;;) {
	    &doonce();
	    sleep $secs;
            if (($loop == 0) && ($ARGS->{"HEADER DISPLAYED"} eq "once")) {
                format_top_name METERFILE "STDOUT_TOP0";
                format_top_name LOGFILE   "STDOUT_TOP0";
	    }
	}
    exit(0);
} else {
    geterror();
}

#
sub doonce() {

    $time = time() - $basetime;
    $loop++;

    $hostname = $ARGS->hostname();
    open(PLOT, "ossvrstat $hostname |") 
	|| die("can't pipe ossvrstat $hostname\n");

    if ($ARGS->doServer()) {
        &doServer();
	if ($Identity{""}{delta}) {
	    $RECORD = $Hash{""}{OUT};
	    write $METERFILE;
	    flush $METERFILE;
	    if ($ARGS->{"LOG FILENAME"} ne "") {
		$LOG = $Log{OUT};
		write LOGFILE;
		flush LOGFILE;
	    }
	}
    }
    if ($ARGS->doClient()) {
	&doClient();
	foreach $c (sort sub_sort (keys %Identity)) {
	    if ($c ne "") {
		if ($Identity{$c}{delta} < 0) {
		    delete $Identity{$c};
		    delete $Hash{$c};
		} else {
		    if ($Identity{$c}{delta} > 0) {
			$RECORD = $Hash{$c}{OUT};
			write $METERFILE;
			flush $METERFILE;
		    }
		    $Identity{$c}{delta} = -1;
		}
	    }
	}
    }

    close(PLOT);
}

sub doLogMeters()
{
    my $BASELINE = $Log{$ARGS->base()};
    my $OUT      = $Log{OUT};
    my $RECORD   = $Log{LAST};

    $_ = <PLOT>; $_ =~ /^[ ]+(\d+) [A-Za-z ]+(\d+)/;
    $OUT->logrecs   ($1 - $BASELINE->logrecs());    $RECORD->logrecs($1);
    $OUT->rec_switch($2 - $BASELINE->rec_switch()); $RECORD->rec_switch($2);

    $_ = <PLOT>; $_ =~ /^[ ]+(\d+) [A-Za-z ]+(\d+)/;
    $OUT->flushd($1 - $BASELINE->flushd());         $RECORD->flushd($1);
    $OUT->flushr($2 - $BASELINE->flushr());         $RECORD->flushr($2);

    $_ = <PLOT>; $_ =~ /^[ ]+(\d+) [A-Za-z ]+(\d+)/;
    $OUT->KB_data  ($1 - $BASELINE->KB_data());     $RECORD->KB_data($1);
    $OUT->KB_record($2 - $BASELINE->KB_record());   $RECORD->KB_record($2);

    $_ = <PLOT>; $_ =~ /^[ ]+(\d+) [A-Za-z ]+(\d+)/;
    $OUT->KB_prop  ($1 - $BASELINE->KB_prop());     $RECORD->KB_prop($1);
    $OUT->KB_direct($2 - $BASELINE->KB_direct());   $RECORD->KB_direct($2);

    $_ = <PLOT>; $_ =~ /^[ ]+(\d+) [A-Za-z ]+/;
    $OUT->props($1 - $BASELINE->props());           $RECORD->props($1);
}

#
sub doClientMeters()
{
    my $CLIENTNAME = shift;
    my $BASELINE = $Hash{$CLIENTNAME}{$ARGS->base()};
    my $OUT      = $Hash{$CLIENTNAME}{OUT};
    my $RECORD   = $Hash{$CLIENTNAME}{LAST};

    $_ = <PLOT>; $_ =~ /^[ ]+(\d+) [A-Za-z ]+(\d+)/;
    $OUT->nmsgs($1 - $BASELINE->nmsgs());           $RECORD->nmsgs($1);
    $OUT->ncallbks($2 - $BASELINE->ncallbks());     $RECORD->ncallbks($2);

# KB_callbk and KB_return in sectors need to convert to KB.
    $_ = <PLOT>; $_ =~ /^[ ]+(\d+) [A-Za-z ]+(\d+)/;
    $OUT->KB_callbk($1 - $BASELINE->KB_callbk());   $RECORD->KB_callbk($1);
    $OUT->KB_return($2 - $BASELINE->KB_return());   $RECORD->KB_return($2);

    $_ = <PLOT>; $_ =~ /^[ ]+(\d+) [A-Za-z ]+(\d+)/;
    $OUT->KB_read($1 - $BASELINE->KB_read());       $RECORD->KB_read($1);
    $OUT->KB_wrtn($2 - $BASELINE->KB_wrtn());       $RECORD->KB_wrtn($2);

    $_ = <PLOT>; $_ =~ /^[ ]+(\d+) [A-Za-z ]+(\d+)/;
    $OUT->commits($1 - $BASELINE->commits());       $RECORD->commits($1);
    $OUT->ro_commits($2 - $BASELINE->ro_commits()); $RECORD->ro_commits($2);

    $_ = <PLOT>; $_ =~ /^[ ]+(\d+) [A-Za-z ]+(\d+)/;
    $OUT->aborts($1 - $BASELINE->aborts());         $RECORD->aborts($1);
    $OUT->twophase($2 - $BASELINE->twophase());     $RECORD->twophase($2);

    $_ = <PLOT>; $_ =~ /^[ ]+(\d+) [A-Za-z ]+(\d+)/;
    $OUT->lock_to($1 - $BASELINE->lock_to());       $RECORD->lock_to($1);
    $OUT->lock_waits($2 - $BASELINE->lock_waits()); $RECORD->lock_waits($2);

# CLIENTNAME eq "" implies Server meters which include mbuf waits.

    if ($CLIENTNAME eq "") {
	$_ = <PLOT>; $_ =~ /^[ ]+(\d+) [A-Za-z ]+(\d+)/;
	$OUT->deadlocks($1 - $BASELINE->deadlocks());   $RECORD->deadlocks($1);
	$Log{OUT}->mbuf_waits($2 - $Log{$ARGS->base()}->mbuf_waits());
	$Log{LAST}->mbuf_waits($2);        
    } else {
	$_ = <PLOT>; $_ =~ /^[ ]+(\d+) [A-Za-z ]+/;
	$OUT->deadlocks($1 - $BASELINE->deadlocks());   $RECORD->deadlocks($1);
    }
}


#
sub doClient()
{
    do {
	$_ = <PLOT>;
    } until (!$_ || $_ =~ /^Client Meters: \((\d+) active client\(s\)\)$/);

    if ($_) {
	$active = $1;
	$exit = 0;
	do {
	    $_ = <PLOT>;
	    if ($_ =~ /^[ ]+Client #(\d+) \((.*)\/([0-9]+)\/(.*)\)$/) {
		$c = $1;
		$Identity{$c}{host} = $2;
		$Identity{$c}{pid}  = $3;
		$Identity{$c}{name} = $4;

		if ($Hash{$c}) {
		    $ID1 = $Hash{$c}{LAST}->ncallbks();
		    $ID2 = $Hash{$c}{LAST}->nmsgs();
		} else {
		    $ID1 = 0;
		    $ID2 = 0;
		    $Hash{$c}{OUT} = ClientMeter->new;
		    $Hash{$c}{LAST} = ClientMeter->new;
		    $Hash{$c}{base0} = ClientMeter->new;
		}

		&doClientMeters($c);

		if ($client == 1) {
		    $Identity{$c}{delta} = 1;
		} elsif ($client == 2) {
		    $Identity{$c}{delta} = $Hash{$c}{LAST}->ncallbks() - $ID1;
		    $Identity{$c}{delta} += $Hash{$c}{LAST}->nmsgs() - $ID2;
		} elsif ($client == 3) {
		    $Identity{$c}{delta} = $Hash{$c}{LAST}->nmsgs() - $ID2;
		} elsif ($client == 4) {
		    $Identity{$c}{delta} = $Hash{$c}{LAST}->ncallbks() - $ID1;
		}

		$exit++;
	    }
	} until $active == $exit;
    }
}

#
sub doServer()
{
    $exit = 0;
    do {
	$_ = <PLOT>;
	if ($_ =~ /^Current Log Size:[ ]+(\d+) sectors.*$/) {
	    if ($ARGS->{"LOGSIZE"} != "absolute") {
		$Log{OUT}->logsize($1/2 - $Log{$ARGS->base()}->logsize()); $Log{LAST}->logsize($1/2);
	    } else {
		$Log{OUT}->logsize($1/2); $Log{LAST}->logsize($1/2);
	    }
	}
	if ($_ =~ /^[ ]+Client Meters:$/) {
	    $c = "";
	    $Identity{$c}{delta} = 1;
	    $Identity{$c}{host} = "ObjectStore";
	    $Identity{$c}{pid}  = "";
	    $Identity{$c}{name} = "Server";

	    $ID1 = $Hash{$c}{LAST}->ncallbks();
	    $ID2 = $Hash{$c}{LAST}->nmsgs();

	    &doClientMeters($c);

	    if ($ARGS->{"SERVER METERS DISPLAYED"} eq "always") {
		$Identity{$c}{delta} = 1;
	    } elsif ($ARGS->{"SERVER METERS DISPLAYED"} eq "activity") {
		$Identity{$c}{delta} =  $Hash{$c}{LAST}->ncallbks() - $ID1;
		$Identity{$c}{delta} += $Hash{$c}{LAST}->nmsgs() - $ID2;
	    } elsif ($ARGS->{"SERVER METERS DISPLAYED"} eq "message") {
		$Identity{$c}{delta} = $Hash{$c}{LAST}->nmsgs() - $ID2;
	    } elsif ($ARGS->{"SERVER METERS DISPLAYED"} eq "callback") {
		$Identity{$c}{delta} = $Hash{$c}{LAST}->ncallbks() - $ID1;
	    } else {
                die (sprintf("don't understand SERVER METERS DISPLAYED = %s\n",$ARGS->{"SERVER METERS DISPLAYED"})),
            }
	}
	if ($_ =~ /^[ ]+Log Meters:$/) {
	    &doLogMeters();
	    $exit = 1;
	}
    } until ($exit == 1 || eof PLOT);
}

#
sub sub_sort
{
    if ($a eq "" || $b eq "") {
	return 1;
    }
    
    if ($sortBy eq "client") {
	if ($sortDir < 0) {
	    $b <=> $a;
	} else {
	    $a <=> $b;
	}
    } elsif ($sortBy eq "name") {
	if ($sortDir < 0) {
	    $Identity{$b}{name} cmp $Identity{$a}{name}
	    || $Identity{$b}{host} cmp $Identity{$a}{host}
	    || $Identity{$b}{pid} <=> $Identity{$a}{pid};
	} else {
	    $Identity{$a}{name} cmp $Identity{$b}{name}
	    || $Identity{$a}{host} cmp $Identity{$b}{host}
	    || $Identity{$a}{pid} <=> $Identity{$b}{pid};
	}
    } elsif ($sortBy eq "host") {
	if ($sortDir < 0) {
	    $Identity{$b}{host} cmp $Identity{$a}{host}
	    || $Identity{$b}{pid} <=> $Identity{$a}{pid};
	} else {
	    $Identity{$a}{host} cmp $Identity{$b}{host}
	    || $Identity{$a}{pid} <=> $Identity{$b}{pid};
	}
    } else {
	if ($sortDir < 0) {
	    $Hash{$b}{OUT}->[$sortBy] <=> $Hash{$a}{OUT}->[$sortBy]
	    || $b <=> $a;
	} else {
	    $Hash{$a}{OUT}->[$sortBy] <=> $Hash{$b}{OUT}->[$sortBy]
	    || $a <=> $b;
	}
    }
}

sub getTimeOfDay()
{
    my $now_string = localtime;
}

#
# FORMATS:
#   format 0 does not print header (-nh option).
#   format 1 contains loop count and timestamp
#   format 2 does not contain loop count and timestamp

format STDOUT_TOP0=
.

format STDOUT_TOP1=
=================================================================================================================================================
 Hostname:   @<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
$hostname
     Date:   @<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
&getTimeOfDay()
   Length:   @<<<<<<<<<<<<
sprintf "%d:%02d:%02d",($time/3600),($time/60)%60,$time%60
Iteration:   @<<<<<<<<<<<<
$loop
=================================================================================================================================================
                                                     KB         KB          KB         KB                                    lock     msg  callbk
 loop @>>>>> client   pid        host  client       read    written    callbck   returned commits rcommit  aborts deadlck   waits recieve    sent
$ARGS->{"TIME UNIT"}
----- ------ ------ ----- ----------- ------- ---------- ---------- ---------- ---------- ------- ------- ------- ------- ------- ------- -------
.

format STDOUT1=
@>>>> @>>>>> @>>>>> @>>>> @>>>>>>>>>> @<<<<<< @>>>>>>>>> @>>>>>>>>> @>>>>>>>>> @>>>>>>>>> @>>>>>> @>>>>>> @>>>>>> @>>>>>> @>>>>>> @>>>>>> @>>>>>>
$loop,int $time/$ARGS->{"UNIT DIVISOR"},$c,$Identity{$c}{pid},$Identity{$c}{host},$Identity{$c}{name},$RECORD->KB_read(),$RECORD->KB_wrtn(),$RECORD->KB_callbk(),$RECORD->KB_return(),$RECORD->commits(),$RECORD->ro_commits(),$RECORD->aborts(),$RECORD->deadlocks(),$RECORD->lock_waits(),$RECORD->nmsgs(),$RECORD->ncallbks()
.


    format LOGTOP_FORMAT=
=====================================================================================================================================
 Hostname:   @<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
$hostname
     Date:   @<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
&getTimeOfDay()
   Length:   @<<<<<<<<<<<<
sprintf "%d:%02d:%02d",($time/3600),($time/60)%60,$time%60
Iteration:   @<<<<<<<<<<<<
$loop
=====================================================================================================================================
 loop @>>>>>  msg buf  KB        KB         KB         KB         log        record     flush      flush      N
$ARGS->{"TIME UNIT"}
                waits  data      record     propagate  direct     records    seg switch data       record     propagates log size
----- ------ -------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ---------- ------------
.

    format LOGFORMAT=
@>>>> @>>>>> @>>>>>>> @>>>>>>>>> @>>>>>>>>> @>>>>>>>>> @>>>>>>>>> @>>>>>>>>> @>>>>>>>>> @>>>>>>>>> @>>>>>>>>> @>>>>>>>>> @>>>>>>>>>>>
$loop,int $time/$ARGS->{"UNIT DIVISOR"},$LOG->mbuf_waits(),$LOG->KB_data(),$LOG->KB_record(),$LOG->KB_prop(),$LOG->KB_direct(),$LOG->logrecs(),$LOG->rec_switch(),$LOG->flushd(),$LOG->flushr(),$LOG->props(),$LOG->logsize()
.

#
    format USAGEERR=
usage: ossvrstat  [-h hostname] [-f parameter file]

-h hostname - server to take statistics on.
              This argument is used to identify parameter file in $OS_ROOTDIR/etc.

-f parameter file - Use this parameter file instead of default.  The default is
              $OS_ROOTDIR/etc/ossvrstat_$hostname_parameters.txt or
              $OS_ROOTDIR/etc/ossvrstat_parameters.txt
.

