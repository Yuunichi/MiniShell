#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include "change_pipes.h"

// Declaración de funciones 
void LeerCaracteres(char *cad);
void structArr(char *File, char **argv2, char *inst);
void separarOR(char *cadena, char **arr);
void separarAND(char *cadenaAND, char **arr);
void separarPepe(char *cadena_tuberia, char **arr);

// Implementación
#include "minishell.h"

// Main
int main(int argc, char **argv)
{

	// Ciclo principal
	while (1)
	{	
		char Pbuffer[1024] = {};
		char File[30] = "";
		char *argv2[22] = {};	// Tokens " "
		char cadena[1024]; 		// Almacena una linea
		char *arr[20] = {};		// Tokens ||
		char *arr2[20] = {}; 	// Tokens &&
		char *arr3[20] = {};	// Tokens |
		printf("--> "); 		// Indicador de prompt

		LeerCaracteres(cadena);	// Lectura de caracteres
		change_pipes(cadena);	// Cambiar | por #

		printf("\n");

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
				
				int stdout_original = dup(STDOUT_FILENO);	// Para restaurarla stdout
				int fd1 = open("tuberia.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
				dup2(fd1,1); 	// Redireccion de la salida estandar al archivo tuberia.txt
				
				memset(Pbuffer, '\0', sizeof(Pbuffer));  // Llena Pbuffer de caracteres NULL

				while (arr3[k] != NULL)
				{	
					int pid = fork();
					if (pid == 0)	// Hijo que ejecuta exec
					{
						structArr(File, argv2, arr3[k]);
						close(fd1);
						execvp(File, argv2);
						printf("%s No es un comando valido:\n", argv2[0]);
						perror(NULL);
						exit(-1);
					}

					k++;
					wait(&status); // Estatus del ultimo comando ejecutado en los tokens de |
					// Testing
								
					dup2(stdout_original, STDOUT_FILENO); 	// Restaura la salida estandar
					close(stdout_original);					// Ya no es necesario, cerramos
					
					int fd2 = open("tuberia.txt", O_RDONLY );		// Abrimos el archivo para lectura
					read(fd2, Pbuffer, sizeof(Pbuffer));			// y guardamos su contenido en Pbuffer
					close(fd2);

					if ( status != 0 ){
						printf("%s\n" , Pbuffer);
						memset(Pbuffer, '\0', sizeof(Pbuffer));  // Llena Pbuffer de caracteres NULL
						close(fd1);
						fd1 = open("tuberia.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
					}
				}

				printf("%s\n" , Pbuffer);
				
				if (status)
				{ // Ejecuto el AND (&&), si el primero se ejecuto correctamente retorno 0 continuo con el segundo comando
					break;
				}else{
					
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