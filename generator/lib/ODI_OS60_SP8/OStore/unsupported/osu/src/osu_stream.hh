#ifndef OSU_STREAM_HH
#define OSU_STREAM_HH

class osu_datetime;
class os_timesecs;

class osu_event_stream {
public:
  osu_event_stream() { ; }
  virtual ~osu_event_stream() { ; }
  virtual void begin() = 0;
  virtual void write(unsigned int) = 0;
  virtual void write(osu_datetime&) = 0;
  virtual void write(os_timesecs&) = 0;
  virtual void write(void*) = 0;
  virtual void write(const char* str) = 0;
  virtual void end() = 0;
  virtual void flush() = 0;
public:
  static osu_event_stream* makeInstance(const char* uri);
};

class osu_buffered_stream :public osu_event_stream {
public:
  osu_buffered_stream();
  virtual ~osu_buffered_stream();
  virtual void begin();
  virtual void write(unsigned int);
  virtual void write(osu_datetime&);
  virtual void write(os_timesecs&);
  virtual void write(void*);
  virtual void write(const char* str);
  virtual void end();
protected:
  char* ebyte;
  char* nbyte;
  char  buffer[4096];
};

class osu_event_fstream :public osu_buffered_stream {
public:
  osu_event_fstream(const char* filename);
  virtual ~osu_event_fstream();
  virtual void flush();
protected:
  void* _stream;
};

class osu_event_sstream :public osu_buffered_stream {
public:
  osu_event_sstream(const char* hostname = 0, int port = 65020);
  virtual ~osu_event_sstream();
  virtual void flush();
  int valid() { return fd_ != -1; }
public:
  int fd_;
};


#endif

