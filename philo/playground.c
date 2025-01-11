#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_PHILOS  200

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define MSG_WRONG_ARGUMENT_COUNT "Please provide 4-5 arguments.\n"
#define MSG_TOO_MANY_PHILOS "Too many philosophers, keep the count under " STRINGIFY(VALUE) ".\n"

void ft_putchar(char c)
{
	write(1, &c, 1);
}

void ft_putstr(char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}

int	main(void)
{
	printf(MSG_TOO_MANY_PHILOS);
}

