#include <stdio.h>

int main(int argc, char **argv){
	char *name = argv[1];
	char *name2 = argv[2];
	printf("Hello there %s. I didn't see you there\nOh and you too %s\n", name, name2);
}

