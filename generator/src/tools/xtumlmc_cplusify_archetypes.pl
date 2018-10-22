#!perl -w
#===========================================================================
my $file_version = '$RCSfile xtumlmc_cplusify_archetypes.pl$ $Revision: 1.13 $';
#
# Description:
# Use this script to convert archetypes into encrypted C constant data
# for inclusion in the generator application.
#
# Notice:
my $copyright = "(c) Copyright 2006-2013 by Mentor Graphics Corp. All rights reserved. Reverse engineering is strictly prohibited.";
#===========================================================================
use File::Copy;

my $key_byte = 0;
my $line_length_counter = 0;
my $file_counter = 0;
my $number_of_files = 0;
my @archetypes = ();  # 4 fields:  name, ename, namelen, econtent, length
my $file_length = 0;
my $model_compiler_model_number = "";

# These routines will insulate perl operations.
# Use automatic "my" filehandles that politely go out of scope.
sub xtumlmc_open($);
sub xtumlmc_open($)
{
  my $path = shift;
  open( my $fh, $path ) or die "ERROR:  Could not open file $path.\n";
  return $fh;
}
sub xtumlmc_opendir($);
sub xtumlmc_opendir($)
{
  my $path = shift;
  opendir( my $fh, $path ) or die "ERROR:  Could not open directory $path.\n";
  return $fh;
}
sub xtumlmc_copy($$);
sub xtumlmc_copy($$)
{
  my $src = shift; my $dest = shift;
  copy( $src, $dest ) or die "Could not copy $src to $dest.\n";
}
sub xtumlmc_mkdir($);
sub xtumlmc_mkdir($)
{
  my $path = shift;
  mkdir( $path ) or die "ERROR:  Could not create directory $path.\n";
}
sub xtumlmc_rmdir($);
sub xtumlmc_rmdir($)
{ # Recursively erase the passed-in directory.
  my $file = shift;
  if ( -f $file ) {
    unlink $file;
  } elsif ( -d $file ) {
    my $DIR = xtumlmc_opendir( $file ); my @entries = readdir $DIR;
    foreach $entry ( @entries ) {
      xtumlmc_rmdir( "$file/$entry" ) if ( $entry ne '.' && $entry ne '..' );
    }
    rmdir $file;
  }
}

#
# encrypt/decrypt a string using XOR of another string
#
sub xorit($$$);
sub xorit($$$)
{
  my $line = shift;
  my $text_length = shift;
  my $copyright = shift;
  my $len = length( $copyright );

  for( $i = 0; $i < $text_length; ++$i ) { 
    $crypt = substr( $line, $i, 1 ) ^ substr( $copyright, $key_byte, 1 );
    $key_byte = ( $key_byte + 1 ) % $len;
    $line_length_counter = ( $line_length_counter + 1 ) % 10;
    ++$file_length;
    my $o = sprintf( "%o", ord( $crypt ) ); 
    print "'\\$o',"; 
    if ( $line_length_counter == 0 ) { print "\n"; }
  }
}

#
# Open a file, encrypt it and output a C initializer for it.
#
sub encrypt_archetype($$);
sub encrypt_archetype($$)
{
  my $filename = shift;
  my $copyright = shift;
  my $I = xtumlmc_open( $filename );

  $key_byte = 0;     # Each file begins at the front of the key.
  $line_length_counter = 0;  # Reset line length truncator.
  print "static char $archetypes[ $file_counter ][3]\[\] = {\n";
  while ( <$I> ) {
    s/\r\n/\n/;     # Avoid doubling up on line terminators (DOS/Unix).
    s/^\s*\./\./;
    if ( /^\.\/\// ) { next; }
    s/\.\/\/.*//;
    xorit( $_, length( $_ ), $copyright );
  }
  print "\n};\n";
}



#
# MAIN
#
my $arc_dir = shift;
$model_compiler_model_number = shift;
my $build_dir = shift;

print "/*\n * $copyright\n */\n";
print "#ifndef XTUMLMC_CPLUSIFY_ARCHETYPES\n";
print "#define XTUMLMC_CPLUSIFY_ARCHETYPES\n";
print "static const char * xtumlmc_cplusify_archetype_file_version = \"$file_version\";\n";
print "static const char * xtumlmc_key_copyright = \"$copyright\";\n";

my $head = <<'##header##'; 
#include <map>
#include <string>

std::map< std::string, int > arch_map;
std::map< std::string, int >::iterator arch_map_iter;

##header##
print $head;

print "#endif\n\n";

#
# Handle the situation where we're building new-style archetype folder
#
my $specialized_arcdir = "$arc_dir/c";
if ( -d "$specialized_arcdir" ) {
    # create temporary arc dir 
    my $build_arcdir = "$build_dir/arc";
    xtumlmc_rmdir($build_arcdir);
    xtumlmc_mkdir($build_arcdir);

    # copy arc/* to <tmp>/arc
    my $DIR = xtumlmc_opendir( $arc_dir ); my @entries = readdir $DIR;
    foreach $entry ( @entries ) {
      if ( -f "$arc_dir/$entry" ) {
        xtumlmc_copy( "$arc_dir/$entry", "$build_arcdir/$entry" );
      }
    }
    
    # copy arc/<specialization>/* to <tmp>/arc
    $DIR = xtumlmc_opendir( $specialized_arcdir ); @entries = readdir $DIR;
    foreach $entry ( @entries ) {
      if ( -f "$specialized_arcdir/$entry" ) {
        xtumlmc_copy( "$specialized_arcdir/$entry", "$build_arcdir/$entry" );
      }
    }
    
    # use new arc dir
    $arc_dir = "$build_arcdir";
}

#
# Output the converted archetypes as C data.
#
my $DIR = xtumlmc_opendir( $arc_dir );
my @entries = grep{ /[a-zA-Z]/ && -f "$arc_dir/$_" } readdir $DIR;
chdir $arc_dir;
foreach my $arc_file ( @entries ) {
  $archetypes[ $file_counter ] =
    [ $arc_file, "xtumlmc_${model_compiler_model_number}_name${file_counter}", length( $arc_file ), "xtumlmc_${model_compiler_model_number}_arc${file_counter}", 0 ];
  $file_length = 0;
  encrypt_archetype( $arc_file, $copyright );
  $archetypes[ $file_counter ][4] = $file_length;
  ++$file_counter;
}
$number_of_files = $file_counter;

#
# Output encrypted names for the archetypes.
#
$file_counter = 0;
foreach my $arc_file ( @entries ) {
  $key_byte = 0;     # Each file begins at the front of the key.
  $line_length_counter = 0;  # Reset line length truncator.
  print "static char $archetypes[ $file_counter ][1]\[\] = {\n";
  xorit( $arc_file, length( $arc_file ), $copyright );
  print "'\\0'\n};\n";
  ++$file_counter;
}

#
# Output a structure containing meta-data about the archetypes.
# Note:  The file name here is still in plain text.
#
print "\nstatic struct {\n";
#print "  const char * name;\n";
print "  char * ename;\n";
print "  int namelen;\n";
print "  char * content;\n";
print "  int length;\n";
print "} xtumlmc_${model_compiler_model_number}_archetypes[ $number_of_files ] = {\n";
for ( my $i = 0; $i < $number_of_files; $i++ ) {
  print "  { $archetypes[$i][1], $archetypes[$i][2], $archetypes[$i][3], $archetypes[$i][4] },"; 
  print " // $archetypes[$i][0]\n";
}
print "};\n\n";

print "\n";
print "static void xtumlmc_init_${model_compiler_model_number}_map( void );\n";
print "static void xtumlmc_init_${model_compiler_model_number}_map() {\n";
for ( my $i = 0; $i < $number_of_files; $i++ ) {
  print "  arch_map[std::string($archetypes[$i][1], $archetypes[$i][2])] = $i;\n"; 
}
print "}\n\n";

my $crypt_function = <<'##crypt_function##';
static void xtumlmc_crypt( char *, const char *, int );
static void xtumlmc_crypt( char * dest, const char * src, int src_length )  
{  
  const int key_length = strlen( xtumlmc_key_copyright );  
  int xor_index = 0;  
  
  for ( int i = 0; i < src_length; ++i ) {
    dest[i] = src[i] ^ xtumlmc_key_copyright[ xor_index ];  
    xor_index = ( xor_index + 1 ) % key_length;  
  }
}
##crypt_function##

my $getline_function = <<'##getline_function##';
static void xtumlmc_getline( char *, istrstream *, int );
static void xtumlmc_getline( char * dest, istrstream * src, int max )
{
  const int key_length = strlen( xtumlmc_key_copyright );
  int xor_index = src->tellg() % key_length;

  while ( 0 < --max ) {
    unsigned char c;
    c = src->get() ^ xtumlmc_key_copyright[ xor_index ];
    xor_index = ( xor_index + 1 ) % key_length;
    if ( ( '\n' == c ) || ( src->eof() ) ) {
      break;
    } else {
      *dest++ = c;
    }
  }
  *dest = 0;
}
##getline_function##

print "#ifndef XTUMLMC_CRYPT_ROUTINES\n";
print "#define XTUMLMC_CRYPT_ROUTINES\n";
print $crypt_function;
print $getline_function;
print "#endif\n";

my $test_program = <<'##test_program##';
#include <stdio.h>

int main( int argc, char * argv[] )
{
  int i, j;

  for ( i = 0; i < sizeof( xtumlmc_${model_compiler_model_number}_archetypes ) / sizeof( xtumlmc_${model_compiler_model_number}_archetypes[ 0 ] ); i++ ) {
    const char * c;
    char p[ 65000 ];
    xtumlmc_crypt( p, xtumlmc_${model_compiler_model_number}_archetypes[ i ].ename, xtumlmc_${model_compiler_model_number}_archetypes[ i ].namelen );
    p[ xtumlmc_${model_compiler_model_number}_archetypes[ i ].namelen ] = 0;
    printf( ".// %s\n", p );
    xtumlmc_crypt( p, xtumlmc_${model_compiler_model_number}_archetypes[ i ].content, xtumlmc_${model_compiler_model_number}_archetypes[ i ].length );
    printf( "%s\n", p );
    xtumlmc_getline( p, xtumlmc_${model_compiler_model_number}_archetypes[ i ].content, 256 );
    printf( "%s\n", p );
  }
}
##test_program##

#print $test_program;
