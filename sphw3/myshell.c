#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MAX 1024

int main( int argc, char **argv)
{
	int j;
	if(argc>1)
	{
		for(j=3;j<argc;j++)
		{printf("%s ",argv[j]);
		}
		
	}
	while (1)
	{
		printf("$ ");
		char cmd[MAX];
		char pat[MAX];
		char *input[100] = { NULL, };    // 크기가 100인 문자열 포인터 배열을 선언하고 NULL로 초기화
		int i = 0;
		fgets(cmd,sizeof(cmd),stdin);
	//	printf("%s\n",cmd);

    		char *ptr = strtok(cmd, " ");    

    		while (ptr != NULL)            
    		{
			if(i==0)
			{
				input[i] = ptr;
				i++;
				input[i] = ptr;
				i++;
			}
			else
			{
				input[i] = ptr;
				i++;
			}
        		ptr = strtok(NULL, " ");   
    		}


		if(feof(stdin))
		{
			printf("\n");
			exit(0);
		}
		int j;	
		int child_pid = fork();
		if (child_pid == 0)
		{
			if(argc > 1)
			{
				execvp(argv[0],argv);
			}
			if(input[4] == ">")
			{
				int fd = open(input[5],O_WRONLY);
				fclose(stdout); dup(fd); close(fd);
				execvp(input[0],input);
			}
			if(input[2] == "|")
			{
				int fd[2];
				pipe(fd);
				fclose(stdout); dup(fd[1]);
				close(fd[1]); close(fd[0]);
				execvp(input[0],input);
			}
				
			else if(execvp(input[0],input)==-1)
			{
				printf("error!!!!!\n");
			}
		}
		else
		{
			waitpid(child_pid);
		}
	}
}
