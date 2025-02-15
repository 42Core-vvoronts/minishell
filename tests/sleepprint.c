#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	main()
{
	printf("Sleeping...\n");
	fflush(stdout);
	sleep(10);
	printf("Woke up\n");
	printf("Exiting...\n");
	fflush(stdout);
}
