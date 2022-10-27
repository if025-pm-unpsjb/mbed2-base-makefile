#include "mbed.h"

extern "C" pid_t _getpid();
extern "C" void _kill();
extern "C" int __wrap_vsnprintf (char * s, size_t n, const char * format, va_list arg );
extern "C" int __wrap_vfprintf ( FILE * stream, const char * format, va_list arg );

pid_t _getpid(void)
{
    return(-1);
}

void _kill(void)
{
	;
}

int __wrap_vsnprintf (char * s, size_t n, const char * format, va_list arg )
{
	return 0;
}

int __wrap_vfprintf ( FILE * stream, const char * format, va_list arg )
{
	return 0;
}
