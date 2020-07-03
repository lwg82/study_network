#ifndef DAYTIME_TCP_CLIENT_H
#define DAYTIME_TCP_CLIENT_H


#include <string.h> // strerror
#include <stdarg.h> // va_list
#include <stdio.h>
#include <stdlib.h>

#include <sys/errno.h>

#define BUF_STRING_LEN_4K 4096

void console_error_log(const char *func, int line, int code);

void console_error_log_fmt(const char *func, int line, int code, const char *fmt, ...);

void console_info_log(const char *func, int line,  const char *fmt, ...);

#define CONSOLE_ERROR_LOG(n) console_error_log(__FUNCTION__, __LINE__, n);
#define CONSOLE_ERROR_LOG_FMT(n, format, ...) console_error_log_fmt(__FUNCTION__, __LINE__, n, format, ##__VA_ARGS__);

#define CONSOLE_INFO_LOG_FMT(format, ...) console_info_log(__FUNCTION__, __LINE__, format, ##__VA_ARGS__);

#endif