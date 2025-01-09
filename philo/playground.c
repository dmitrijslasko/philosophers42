#include <string.h>
#include <stdio.h>
#include <pthread.h>

void *my_thread_function2(void *arg) {
    printf("Hello from thread 2!\n");
    return (NULL);
}

void *my_thread_function1(void *arg) {
    printf("Hello from thread 1!\n");
    return (NULL);
}

int	main(void)
{
	pthread_t thread1;
	pthread_t thread2;

	pthread_create(&thread1, NULL, my_thread_function1, NULL);
	pthread_create(&thread2, NULL, my_thread_function2, NULL);

	// pthread_join(thread1, NULL);
	// pthread_join(thread2, NULL);

}

