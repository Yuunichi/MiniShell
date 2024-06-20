all: minishell 

clean:	
	rm -rf minishell minishell.o 
	
minishell:   minishell.o

minishell.o: minishell.c
