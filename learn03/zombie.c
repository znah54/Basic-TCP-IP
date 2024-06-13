#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
	pid_t pid = fork();

	if(pid==0)
	{
		puts("Hi, I am a child process");
	}
	else
	{
		printf("child Process ID : %d \n", pid);
		sleep(30);
	}

	if(pid==0)
			puts("End child process");
	else
			puts("End Parent process");
	return 0;
}

