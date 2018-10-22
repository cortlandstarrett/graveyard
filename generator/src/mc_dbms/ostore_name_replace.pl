#!perl -w
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# (C) Copyright Mentor Graphics Corporation  (2004-2005)                #
# All rights reserved.                                                  #
#_______________________________________________________________________#

  
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# For help by user...
my $help_info = <<'##done##';
# Title:               ObjectStore to Mentor Graphics Name Replacer     #
# File Name:           ostore_name_replace.pl                           #
#                                                                       #
# Protocol -                                                            #
#   $ ostore_name_replace.pl -d <directory>                             #
#                -d = the directory where these files reside (optional) #
# Examples -                                                            #
#   $ ostore_name_replace.pl -d /cygdrive/c/dev/model_compilers/        #
#                                                                       #
# Abstract -                                                            #
#   This file removes all instances of ostore/*.h that aren't ostore.hh #
#   from the files listed in the file with -f.  Additionally, it makes  #
#   sure all files have ostore.hh in it.                                #   
# -- End information for help
##done##
#                                                                       #
# Notes -                                                               #
#   Requires Perl.                                                      #
#                                                                       #
# Who  Date      Change                                                 #
# --------------------------------------------------------------------- #
# SKB  07/26/05  initial creation                                       #
#########################################################################

#  This script has some short-comings.  It ended up touching every file 
#  regardless, and I had to go in and replace the makefiles and the build_scipts
#  with versions from head.  Additionally, I had to rename u_ostore.* to
#  u_mc_dbms.*, and rename the mc_dbms files to match the new naming scheme.
use File::Find;

sub edits() 
{
  # skip directories
  return unless -f;
  # skip non-sourcefiles
  return unless ( /.cc$/ || /.cpp$/ || /.c$/ || /.hh$/ || /.h$/ || /.sor$/ );

  $file = $_;
  open FILE, $file;
  @lines = <FILE>;
  close FILE;
  $changed = 0;

  for $line ( @lines ) 
  {
    $origline = $line;
    $line =~ s/os_/mc_dbms_/g; 
    $line =~ s/OS_/MC_DBMS_/g; 
    $line =~ s/objectstore/dbms_config/g; 
    $line =~ s/tix_/mc_dbms_tx_/g; 
    $line =~ s/TIX_/MC_DBMS_TX_/g; 
    $line =~ s/ostore/mc_dbms/g;
    # Log the files and lines that have been changed.
    if ( $origline ne $line ) {
      if ( $changed == 0 ) {
        print "working on file $file\n";
        $changed = $changed + 1;
      }
      print "$line";
    }
  }

  # write the new data back to the file
  if ( $changed > 0 ) { 
    open FILE, ">$file";
    print FILE @lines;
    close FILE;
  }

}


#----------------------------------------------------------------------------
# This is Clay's awsome command line argument interpreter.  Run this to
# load all options in a hash called "%comnd_opts".  The hash key values are
# the command line switches, for example "-path" and the matching value
# of the hash is the option that follows the switch.  A switch is
# identified as a sting that starts with a '-' or a '/' any other
# arguments are considered an option for the preceding switch.
#----------------------------------------------------------------------------

# Read the command line options
my $dir;
my %comnd_opts;
for ( my $i = 0; $i < @ARGV; $i++ ) {
  $ARGV[$i] =~ s/^-// and $comnd_opts{ $ARGV[$i] }= "";
  @ARGV >= ($i+2) and $ARGV[$i+1] !~ /^-/ and ($comnd_opts{ $ARGV[$i] } = $ARGV[$i + 1], ++$i);
}

foreach $k ( sort keys %comnd_opts ) {
  $k =~ /^(d|directory)$/i and $dir = $comnd_opts{ $k };
}

#----------------------------------------------------------------------------
# Main functionality
#----------------------------------------------------------------------------
print "working in directory $dir\n";
find(\&edits, $dir);


