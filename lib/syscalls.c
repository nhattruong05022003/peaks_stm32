/* Includes */
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include "bsp_common.h"

/* Variables */
extern int errno;
extern int __io_putchar(int ch) __attribute__((weak));
extern int __io_getchar(void) __attribute__((weak));

register char * stack_ptr asm("sp");

char *__env[1] = { 0 };
char **environ = __env;

/* Functions */
void initialise_monitor_handles()
{

}

int _getpid(void)
{
	return 1;
}

int _kill(int pid, int sig)
{
	PARAM_UNUSED(pid);
	PARAM_UNUSED(sig);
	errno = EINVAL;
	return -1;
}

void _exit (int status)
{
	_kill(status, -1);
	/* Make sure we hang here */
	while (1) 
	{

	}
}

__attribute__((weak)) int _read(int file, char *ptr, int len)
{
	PARAM_UNUSED(file);
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		*ptr++ = __io_getchar();
	}

return len;
}

__attribute__((weak)) int _write(int file, char *ptr, int len)
{
	PARAM_UNUSED(file);
	int DataIdx;

	for (DataIdx = 0; DataIdx < len; DataIdx++)
	{
		__io_putchar(*ptr++);
	}
	return len;
}

int _close(int file)
{
	PARAM_UNUSED(file);
	return -1;
}


int _fstat(int file, struct stat *st)
{
	PARAM_UNUSED(file);
	st->st_mode = S_IFCHR;
	return 0;
}

int _isatty(int file)
{
	PARAM_UNUSED(file);
	return 1;
}

int _lseek(int file, int ptr, int dir)
{
	PARAM_UNUSED(file);
	PARAM_UNUSED(ptr);
	PARAM_UNUSED(dir);
	return 0;
}

int _open(char *path, int flags, ...)
{
	PARAM_UNUSED(path);
	PARAM_UNUSED(flags);
	/* Pretend like we always fail */
	return -1;
}

int _wait(int *status)
{
	PARAM_UNUSED(status);
	errno = ECHILD;
	return -1;
}

int _unlink(char *name)
{
	PARAM_UNUSED(name);
	errno = ENOENT;
	return -1;
}

int _times(struct tms *buf)
{
	PARAM_UNUSED(buf);
	return -1;
}

int _stat(char *file, struct stat *st)
{
	PARAM_UNUSED(file);
	st->st_mode = S_IFCHR;
	return 0;
}

int _link(char *old, char *new)
{
	PARAM_UNUSED(old);
	PARAM_UNUSED(new);
	errno = EMLINK;
	return -1;
}

int _fork(void)
{
	errno = EAGAIN;
	return -1;
}

int _execve(char *name, char **argv, char **env)
{
	PARAM_UNUSED(name);
	PARAM_UNUSED(argv);
	PARAM_UNUSED(env);
	errno = ENOMEM;
	return -1;
}

void abort(void)
{
    while(1)
    {
        __asm__ volatile("nop");
    }
}

/**
 _sbrk
 Increase program data space. Malloc and related functions depend on this
**/
caddr_t _sbrk(uint32_t incr)
{
	extern uint8_t _sheap asm("_sheap");
	extern uint8_t _eheap asm("_eheap");
	static uint8_t *heap_end = NULL;
	uint8_t *prev_heap_end;

	/* Initialize heap_end on the first call */
	if (heap_end == NULL) {
		heap_end = (uint8_t *)&_sheap;
	}

	prev_heap_end = heap_end;

	/* Check against the RESERVED heap limit, not the moving stack pointer */
	if ((uint32_t)(heap_end) + (uint32_t)(incr) > (uint32_t)(&_eheap)) {
		errno = ENOMEM; // Out of memory
		return (caddr_t) -1;
	}

	heap_end += (uint32_t)incr;

	return (caddr_t) prev_heap_end;
}
