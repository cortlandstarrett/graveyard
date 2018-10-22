#!perl -w
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# (C) Copyright Mentor Graphics Corporation  (2004-2005)                #
# All rights reserved.                                                  #
#_______________________________________________________________________#

  
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
# For help by user...
my $help_info = <<'##done##';
# Title:               Cleaner                                          #
# File Name:           cleaner     .pl                                  #
#                                                                       #
# Protocol -                                                            #
#   $ cleaner.pl -f <file> -d <directory>                               #
#                -f = the file that holds the filenames to clean up     #
#                -d = the directory where these files reside (optional) #
# Examples -                                                            #
#   $ cleaner.pl -f files_to_clean.txt -d /cygdrive/c/root_dir          #
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
# AJW  07/22/05  initial creation                                       #
#########################################################################

use File::Copy;

my $prepend_dir;
my $file_list;

#----------------------------------------------------------------------
# clean_file
# parameters - file to clean
# returns    - nothing
# This strips the file passed in of all instances of ostore/*.h that
# aren't ostore.hh, and makes sure the file has ostore.h in it.
#---------------------------------------------------------------------

sub clean_file( $ ){
  my $file = shift( @_ );
  
  # Strip off the newline
  chop( $file );
  my $file_res = 0;
  # Open the file and a file to dump the temporary contents into.
  open FILE_TO_CLEAN,"<$file" or $file_res = 1;
  open FILE_TO_WRITE,">temp" or die "Failed to create temp file.\n";
  
  if( $file_res == 1 )
  {
    print "Failed to open file $file for cleaning.\n";
    return;
  }
    
  
  # Read in the files to clean.
  my @dirty_lines = <FILE_TO_CLEAN>;
  # Strip out every line with ostore/ in it
  my @clean_lines = grep { !/ostore\//i } @dirty_lines;
  # Add the ostore.hh line
  
  # Find the end of the prologue
  my $spot_to_insert;
  my $i = 0;
  foreach $line ( @clean_lines )
  {
    if( $line !~ /\/\// && !defined $spot_to_insert )
    {  
      $spot_to_insert = $i;
    }
    $i++;
  }
  
  # Slice the 2.
  @arr1 = @clean_lines[0 .. $spot_to_insert-1];
  @arr2 = @clean_lines[$spot_to_insert .. $i-1];
  @clean_lines = @arr2;
  unshift @clean_lines,"#include <ostore/ostore.hh>\n";
  unshift @clean_lines,@arr1;
  print FILE_TO_WRITE  @clean_lines;
  close FILE_TO_WRITE;
  close FILE_TO_CLEAN;
  
  # Delete the old file and copy the new one on it.
  $cmd = "cp temp $file";
  system $cmd;
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
my %comnd_opts;
for ( my $i = 0; $i < @ARGV; $i++ ) {
  $ARGV[$i] =~ s/^-// and $comnd_opts{ $ARGV[$i] }= "";
  @ARGV >= ($i+2) and $ARGV[$i+1] !~ /^-/ and ($comnd_opts{ $ARGV[$i] } = $ARGV[$i + 1], ++$i);
}

foreach $k ( sort keys %comnd_opts ) {
  $k =~ /^(f|file)$/i and $file_list = $comnd_opts{ $k };
  $k =~ /^(d|directory)$/i and $prepend_dir = $comnd_opts{ $k };
}

if( !defined $file_list )
{
  print "Please specify the file that holds the file list.\n";
  exit;
}

# Open the file that holds the list of files to change.
open( LIST_OF_FILES,"$file_list" );

# Go through the file, append the prepend directory to the file,
# and call clean_file to clean it up.
my @array_of_files = <LIST_OF_FILES>;
foreach $file ( @array_of_files )
{
  my $total_path;
  if( defined $prepend_dir )
  {
   $total_path = "$prepend_dir/$file";
  }
  else
  {
    $total_path = $file;
  }
  clean_file( $total_path );
}

close LIST_OF_FILES;