#include "easy_log.h"

void console_error_log(const char *func, int line, int code)
{
   printf("%s,  line:%d, error string:[%d]%s \r\n", func, line, code, strerror(errno));
}


void console_error_log_fmt(const char *func, int line, int code, const char *fmt, ...)
{
  char buf[BUF_STRING_LEN_4K] = {0};

  va_list ap;
  va_start(ap, fmt);
  
  vsnprintf(buf, BUF_STRING_LEN_4K, fmt, ap);
  
  va_end(ap);
  
  printf("%s, line:%d, error:[%d]%s, %s \r\n", func, line, code, strerror(errno),  buf);
}

void console_info_log(const char *func, int line,  const char *fmt, ...)
{
 char buf[BUF_STRING_LEN_4K] = {0};

  va_list ap;
  va_start(ap, fmt);
  
  vsnprintf(buf, BUF_STRING_LEN_4K, fmt, ap);
  
  va_end(ap);
  
  printf("%s, line:%d, %s \r\n", func, line,  buf);
}