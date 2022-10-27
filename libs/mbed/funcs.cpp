#include "mbed.h"

extern "C" pid_t _getpid();
extern "C" void _kill();

#ifdef STM32F746xx
extern "C" int __wrap_vsnprintf (char * s, size_t n, const char * format, va_list arg );
extern "C" int __wrap_vfprintf ( FILE * stream, const char * format, va_list arg );
#endif

pid_t _getpid(void)
{
    return(-1);
}

void _kill(void)
{
	;
}

#ifdef STM32F746xx
int __wrap_vsnprintf (char * s, size_t n, const char * format, va_list arg )
{
	return 0;
}

int __wrap_vfprintf ( FILE * stream, const char * format, va_list arg )
{
	return 0;
}
#endif
