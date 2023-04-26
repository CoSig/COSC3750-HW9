/*
 * wyshell.c
 * Author : Cole Sigmon
 * Date : April 25, 2023
 * 
 * COSC 3750, Homework 9
 * 
 * This is wyshell.c it is a beginning of a shell.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wyscanner.h"

int main()
{
	char input[1024];
	char *args[64];
	int token, argc, status;
	pid_t pid;

	while (1)
	{
		printf("$> ");
		fflush(stdout);

		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			printf("\n");
			exit(0);
		}

		input[strcspn(input, "\n")] = '\0';
		
		token = parse_line(input);
		while ((token = parse_line(input)) != EOL)
		{
			if (token == WORD)
			{
				args[argc++] = strdup(lexeme);
			}
			else if (token == ERROR_CHAR)
			{
				perror("error character: ");
				perror(error_char);
			}
			else if (token == SYSTEM_ERROR)
			{
				perror("system error");
				return 0;
			}
			else if (token == QUOTE_ERROR)
			{
				perror("quote error");
			}
			else
			{
				perror("unexpected token");
			}
		}

		if (argc > 0)
		{
			args[argc] = NULL;
			if (strcmp(args[argc - 1], "&") == 0)
			{
				args[argc - 1] = NULL;

				if ((pid = fork()) == -1)
				{
					perror("fork");
				}
				else if (pid == 0)
				{
					execvp(args[0], args);
					perror(args[0]);
					exit(1);
				}
			}
			else
			{
				if ((pid = fork()) == -1)
				{
					perror("fork");
				}
				else if (pid == 0)
				{
					execvp(args[0], args);
					perror(args[0]);
					exit(1);
				}
				else
				{
					waitpid(pid, &status, 0);
				}
			}
		}

		for (int i = 0; i < argc; i++)
		{
			free(args[i]);
		}
		argc = 0;
	}

	return 0;
}
