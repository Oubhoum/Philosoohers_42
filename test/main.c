#include <stdio.h>
#include <pthread.h>

FILE	*log_file;
int		incidents = 0;

int	main(void)
{
	log_file = fopen("log.txt", "w");
	if (log_file == NULL)
	{
		printf("Error oopening file.\n");
		return (1);
	}

	pthread_t	thread;
	int	return_value = 0;
	return_value = pthread_create(&thread, NULL, &logger, NULL);
	if (return_value != 0) return 1;
	return_value = pthread_detach(thread);
	if (return_value != 0) return 1;

	int input = 0;
	do
	{
		printf("Enter -1 to quit.\n");
		printf("New incidents: ");
		scanf("%d", &input);

		if (input != -1) incidents += input;
	} while (input != -1);
	

	return (0);
}