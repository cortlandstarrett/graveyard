#include "osu_stream.hh"
#include "osu_datetime.hh"
#include <ostore/ostore.hh>
#include <ostore/dbutil.hh>
#include <iostream.h>
#ifdef _MSC_VER 
#include <strstrea.h>
#else
#include <strstream.h>
#endif
#include <iomanip.h>
#include <fstream.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#ifdef _WIN32
#define STREQ(A,B) (::stricmp(A,B) == 0)
#include <winsock.h>
#else
#define STREQ(A,B) (::strcasecmp(A,B) == 0)
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

char* ultoa(unsigned long n, char* bytes, int ord) {
  if (ord == 10) {
    sprintf(bytes,"%d",n);
  } else {
    sprintf(bytes,"%x",n);    
  }
  return bytes;
}

#endif

#ifdef _WIN32
static void cleanup_winsock()
{
  /* have to call WSACleanup once for each call to WSAStartup */
  WSACleanup();
}

static int init_winsock()
{
  /* This code is basically lifted from the VC++ 5.0 Help file for WSAStartup */

  WSADATA wsaData;

  WORD wVersionRequested = MAKEWORD(1,1);
  int err = WSAStartup( wVersionRequested, &wsaData );
  if (err != 0)
    return err;

  if (LOBYTE(wsaData.wVersion) != 1 && HIBYTE(wsaData.wVersion) != 1) {
    WSACleanup();
    return -1;
  }

  /* use the atexit routine to register a callback to cleanup_winsock so that
	 * the winsock DLL frees the network resources for this application.
	 */

  return atexit (cleanup_winsock);
}
#else
static int init_winsock() { return 0; }
#endif

static int setup = 0;

osu_buffered_stream::osu_buffered_stream()
  : ebyte(buffer+sizeof(buffer)-16),
    nbyte(buffer)
{
  ;
}

osu_buffered_stream::~osu_buffered_stream()
{
  ;
}

void osu_buffered_stream::begin()
{ 
  ;
}

void osu_buffered_stream::end()
{ 
  *(nbyte-1) = '\n';
}

void osu_buffered_stream::write(unsigned int n)
{
  // should write no more than 12 bytes...
  if (nbyte > ebyte) flush();

  ultoa(n,nbyte,10);
  while (*nbyte) nbyte++;
  *(nbyte++) = ' ';
  *nbyte = '\0';
}

void osu_buffered_stream::write(osu_datetime& dt)
{
  // not sure if ebyte has enough buffer space
  // to handle write.
  if (nbyte > (ebyte-24)) flush();

  char buf[128];
  ostrstream str(buf,sizeof(buf));
  str << dt << ends;
  write(buf);
}

void osu_buffered_stream::write(os_timesecs& time)
{
  if (nbyte > (ebyte-1)) flush();

  // we add 1000 to millisecs to pad with leading 0s.
  // x is used to overwrite the leading 1 with decimal
  // point.
  write(time.tv_sec);
  char* x = --nbyte;
  write(1000+time.tv_usec/1000);
  *x = '.';
}

void osu_buffered_stream::write(void* ptr)
{
  // should write no more than 10 bytes...
  if (nbyte > ebyte) flush();

  ultoa((unsigned long)ptr,nbyte,36);
  while (*nbyte) nbyte++;
  *(nbyte++) = ' ';
  *nbyte = '\0';
}

void osu_buffered_stream::write(const char* str)
{
  if (nbyte >= ebyte) flush();
    
  int nchars = ebyte-nbyte;
  while (*str) {
    *(nbyte++) = *(str++);
    nchars--;
    if (nchars == 0) {
      flush();
      nchars = ebyte - nbyte;
    }
  }
  *(nbyte++) = ' ';
  *nbyte = '\0';
}


osu_event_fstream::osu_event_fstream(const char* filename)
  : osu_buffered_stream()
{
  _stream = ::fopen(filename,"a");
}

osu_event_fstream::~osu_event_fstream()
{
  flush();
  ::fclose((FILE*)_stream);
  _stream = 0;
}


void osu_event_fstream::flush()
{
  ::fputs(buffer,(FILE*)_stream);
  ::fflush((FILE*)_stream);
  nbyte = buffer;
  *nbyte ='\0';
}


osu_event_sstream::osu_event_sstream(const char* hostname, int port)
  : fd_(-1)
{
  if (setup == 0) {
    setup = 1;
    init_winsock();
  }

  sockaddr_in address_;

  char hostname_buffer[256];
  if ( hostname == 0) {
    ::gethostname(hostname_buffer,sizeof(hostname_buffer));
    hostname = hostname_buffer;
  }

  // get host entry for hostname
  hostent *pHostEntry = ::gethostbyname( hostname );
  if ( pHostEntry ) {
    memcpy(&address_.sin_addr,pHostEntry->h_addr,pHostEntry->h_length);
    address_.sin_family = pHostEntry->h_addrtype;
    address_.sin_port = htons(port);

    fd_ = ::socket( AF_INET, SOCK_STREAM, 0 );
    if (fd_ >= 0) {
      if (::connect( fd_,(sockaddr*)&address_, sizeof(address_)) == -1) {
	fd_ = -1;
      }
    }
  }
}

osu_event_sstream::~osu_event_sstream()
{
  flush();
#ifdef _WIN32
  ::closesocket(fd_);
#else
  ::close(fd_);
#endif
}

void osu_event_sstream::flush()
{
  char* msgbuf = buffer;

  int nleft = (nbyte - msgbuf);

  if (fd_ >= 0) {
    while ( nleft > 0 ) {
      int nwritten = ::send( fd_, msgbuf, nleft, 0 );
      if ( nwritten <= 0 ) {
	fd_ = -1;
	break;
      }
      nleft -= nwritten;
      msgbuf += nwritten;
    }
    nbyte = buffer;
    *nbyte ='\0';
  }
}

osu_event_stream* osu_event_stream::makeInstance(const char* uri)
{
  osu_event_stream* estream = 0;
  if (uri) {
    char* opcode = ::strdup(uri);
    char* arg    = ::strchr(opcode,':');
    if (arg) {
      *arg = '\0';
      arg++;
      if (STREQ(opcode,"file")) {
	estream = new osu_event_fstream(arg);
      } else if (STREQ(opcode,"tcp")) {
	char* hostname = arg;
	char* port = ::strrchr(arg,':');
	int portn = 0;
	if (port) {
	  *port = '\0';
	  port++;
	  ::sscanf(port,"%d",&portn);
	}
	estream = new osu_event_sstream(hostname,portn);
	if (!((osu_event_sstream*)estream)->valid()) {
	  delete estream;
	  estream = 0;
	}
      }
    } else {
	estream = new osu_event_fstream(arg);
    }
    ::free(opcode);
  }
  return estream;
}

