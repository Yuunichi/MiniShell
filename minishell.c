#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void LeerCaracteres(char *cad)
{
	int it = 0;
	char ch; // Ultimo caracter leido
	while ((ch = getchar()) != '\n' && ch != EOF){
		cad[it] = ch;
		it++;
	}
	cad[it] = '\0';
}

void structArr(char *File, char **argv2, char *inst){
	strcpy(File, "");
	strcat(File, strtok(inst, " "));
	argv2[0] = File;
	int i = 1;
	char *iterador;
	while (i == 1 || (i <= 20 && iterador != NULL))	{
		iterador = strtok(NULL, " ");
		argv2[i] = iterador;
		++i;
	}
	argv2[i] = NULL;
}

void separarOR(char *cadena, char **arr){
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

void separarAND(char *cadenaAND, char **arr){
	arr[0] = strtok(cadenaAND, "&&");
	int i = 1;
	char *iterador;
	while (i == 1 || (i <= 20 && iterador != NULL)){
		iterador = strtok(NULL, "&&");
		arr[i] = iterador;
		++i;
	}
}

int main(int argc, char **argv)
{

	// Ciclo principal
	while (1){

		char File[30] = "";
		char *argv2[22] = {};
		char cadena[1024]; // Almacena una linea
		char *arr[20] = {};
		char *arr2[20] = {};
		printf("--> "); // Indicador de prompt

		// Lectura de caracteres
		LeerCaracteres(cadena);

		if (!strcmp(cadena, "salir")){
			printf("Adios.\n");
			exit(0);
		}
		exit;

	/* ESTA SECCION ESTA EN REVISION */
		int i = 0;
		int status,statusOR=0;

		separarOR(cadena, arr);
		while (arr[i] != NULL){
			separarAND(arr[i], arr2);
			int j=0;
			
			while(arr2[j]!=NULL){ // ls || ls -l//
				int pid = fork();
				if (pid == 0){ //HIJO
					structArr(File, argv2, arr2[j]);			
					execvp(File, argv2);
					printf("%s No es un comando valido:\n", argv2[0]);
					perror("");
					exit(-1);
				}
				wait(&status);
				if (status){ //Ejecuto el AND (&&), si el primero se ejecuto correctamente retorno 0 continuo con el segundo comando
					break;
				}
				j++;
			}
				statusOR=(status || statusOR);
				if (!statusOR){ //Ejecuto el OR (&&), si el primero se ejecuto correctamente retorno 0 continuo con el segundo comando
					break;
				}
			i++;
		}

	/* ESTA SECCION ESTA EN REVISION */
	}
	return 0;
}