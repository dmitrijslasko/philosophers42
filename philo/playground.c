#include <string.h>
#include <stdio.h>

int	main(void)
{
	char text[] = "abcde";
	printf("TEXT: %s\n", text);
	memset(text, '-', 3);
	printf("TEXT: %s\n", text);
	return (0);
}