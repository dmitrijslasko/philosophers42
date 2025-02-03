#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

int	main(void)
{
	sem_t *semaphore;

	sem_unlink("/sem1");
	semaphore = sem_open("/sem1", O_CREAT, 0666, 1);
	if (semaphore == SEM_FAILED)
	{
		perror("sem_open failed");
		return (1);
	}
	printf("Hello!\n");
	sem_close(semaphore);
	//sem_unlink("/sem1");
	return (0);
}
