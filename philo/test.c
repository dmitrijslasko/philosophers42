#include <unistd.h>
#include <stdio.h>

int main(void)
{
	char *test;

	test = "Hello";
	write(1, "a", 1);
	printf("%c\n", test[0]);

}