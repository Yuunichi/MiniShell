#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <semaphore.h>

#include "change_pipes.h"

// Declaración de funciones 
void LeerCaracteres(char *cad);
void structArr(char *File, char **argv2, char *inst);
void separarOR(char *cadena, char **arr);
void separarAND(char *cadenaAND, char **arr);
void separarPepe(char *cadena_tuberia, char **arr);

// Main

int main(int argc, char **argv)
{
	
	sem_t mutex;
	sem_init( &mutex, 0, 1);

	// Ciclo principal
	while (1)
	{	char Pbuffer[1024] = {};
		char File[30] = "";
		char *argv2[22] = {};	// Tokens " "
		char cadena[1024]; 		// Almacena una linea
		char *arr[20] = {};		// Tokens ||
		char *arr2[20] = {}; 	// Tokens &&
		char *arr3[20] = {};	// Tokens |
		printf("--> "); 		// Indicador de prompt

		LeerCaracteres(cadena);	// Lectura de caracteres
		change_pipes(cadena);	// Cambiar | por #

		if (!strcmp(cadena, "salir"))
		{
			printf("Adios.\n");
			exit(0);
		}
		exit;

		/* ESTA SECCION ESTA EN REVISION */
		int i = 0;
		int status, statusOR = 0;

		separarOR(cadena, arr);
		while (arr[i] != NULL)
		{
			separarAND(arr[i], arr2);
			int j = 0;

			while (arr2[j] != NULL)
			{								
				separarPepe(arr2[j], arr3); // Tokenizamos por |
				int k = 0;
				// Redireccion de la salida estandar al archivo tuberia.txt
				int stdout_original = dup(STDOUT_FILENO);	// para restaurarla después
				int fd1 = open("tuberia.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
				dup2(fd1,1);
				while (arr3[k] != NULL)
				{
					int pid = fork();
					if (pid == 0)	// Hijo que ejecuta exec
					{ 
						close(fd1);

						structArr(File, argv2, arr3[k]);
						execvp(File, argv2);
						printf("%s No es un comando valido:\n", argv2[0]);
						perror("");
						exit(-1);
					}
					k++;
				}
				// Probando
				wait(&status);
				dup2(stdout_original, STDOUT_FILENO); // Restaura la salida estandar
				close(stdout_original);

				int fd2 = open("tuberia.txt", O_RDONLY );
				read(fd2, Pbuffer, sizeof(Pbuffer));
				sem_wait(&mutex);
				printf("%s\n" , Pbuffer);
				sem_post(&mutex);
				
				close(fd2);
				
				// close(fd1);
				// - - - - - - - - - - -

				//wait(&status);
				if (status)
				{ // Ejecuto el AND (&&), si el primero se ejecuto correctamente retorno 0 continuo con el segundo comando
					break;
				}
				j++;
			}
			statusOR = (status || statusOR);
			if (!statusOR)
			{ // Ejecuto el OR (&&), si el primero se ejecuto correctamente retorno 0 continuo con el segundo comando
				break;
			}
			i++;
		}

		/* ESTA SECCION ESTA EN REVISION */
	}
		return 0;
}


//--------------------------------------//
//										//
//	 Implementación de las funciones	//
//										//
// -------------------------------------//

void LeerCaracteres(char *cad)
{
	int it = 0;
	char ch; // Ultimo caracter leido
	while ((ch = getchar()) != '\n' && ch != EOF)
	{
		cad[it] = ch;
		it++;
	}
	cad[it] = '\0';
}

void structArr(char *File, char **argv2, char *inst)
{
	strcpy(File, "");
	strcat(File, strtok(inst, " "));
	argv2[0] = File;
	int i = 1;
	char *iterador;
	while (i == 1 || (i <= 20 && iterador != NULL))
	{
		iterador = strtok(NULL, " ");
		argv2[i] = iterador;
		++i;
	}
	argv2[i] = NULL;
}

void separarOR(char *cadena, char **arr)
{
	arr[0] = strtok(cadena, "||");
	int i = 1;
	char *iterador;
	while (i == 1 || (i <= 20 && iterador != NULL))
	{
		iterador = strtok(NULL, "||");
		arr[i] = iterador;
		++i;
	}
}

void separarAND(char *cadenaAND, char **arr)
{
	arr[0] = strtok(cadenaAND, "&&");
	int i = 1;
	char *iterador;
	while (i == 1 || (i <= 20 && iterador != NULL))
	{
		iterador = strtok(NULL, "&&");
		arr[i] = iterador;
		++i;
	}
}

void separarPepe(char *cadena_tuberia, char **arr)
{
	arr[0] = strtok(cadena_tuberia, "#");
	int i = 1;
	char *iterador;
	while (i == 1 || (i <= 20 && iterador != NULL))
	{
		iterador = strtok(NULL, "#");
		arr[i] = iterador;
		++i;
	}
}
