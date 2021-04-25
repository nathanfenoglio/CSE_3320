#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv){
	//either way works for getting the page size which is 4096 btw 2^12
	long sz = getpagesize();
	printf("page size: %ld\n", sz);
	printf("The page size for this system is %ld bytes.\n", sysconf(_SC_PAGE_SIZE));
	
	printf("Checking out some other stuff that you can grab with sysconf(whatev)\n");
	printf("sysconf(_SC_STREAM_MAX): %ld\n", sysconf(_SC_STREAM_MAX));
	printf("sysconf(_SC_TTY_NAME_MAX): %ld\n", sysconf(_SC_TTY_NAME_MAX));
	printf("sysconf(_SC_VERSION): %ld\n", sysconf(_SC_VERSION));
	printf("sysconf(_SC_NPROCESSORS_CONF): %ld\n", sysconf(_SC_NPROCESSORS_CONF));
	printf("sysconf(_SC_NPROCESSORS_ONLN): %ld\n", sysconf(_SC_NPROCESSORS_ONLN));
	return 0;
}
