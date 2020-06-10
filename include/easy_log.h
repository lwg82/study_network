#ifndef DAYTIME_TCP_CLIENT_H
#define DAYTIME_TCP_CLIENT_H


#include <string.h> // strerror
#include <stdarg.h> // va_list

#define BUF_STRING_LEN_4K 4096

void console_error_log(const char *func, int line, int code)
{
   printf("%s, %d, error string:%s:%d \r\n", func, line, strerror(errno), code);
   exit(EXIT_FAILURE);
}

void console_error_log_fmt(const char *func, int line, int code, const char *fmt, ...)
{
  char buf[BUF_STRING_LEN_4K] = {0};

  va_list ap;
  va_start(ap, fmt);
  
  vsnprintf(buf, BUF_STRING_LEN_4K, fmt, ap);
  
  va_end(ap);
  
  printf("%s, %d, error string:%s:%d, %s \r\n", func, line, strerror(errno), code, buf);
  
  exit(EXIT_FAILURE);
}



#define CONSOLE_ERROR_LOG(n) console_error_log(__FUNCTION__, __LINE__, n);
#define CONSOLE_ERROR_LOG_FMT(n, format, ...) console_error_log_fmt(__FUNCTION__, __LINE__, n, format, ##__VA_ARGS__);

#endif