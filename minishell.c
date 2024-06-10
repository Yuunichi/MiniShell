#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main ( int argc, char** argv ){

    //Ciclo principal
    while ( 1 ){     
        char ch;            // Ultimo caracter leido
        char cadena[1024];  // Almacena una linea
        char path[]="/bin/";
        int it = 0;         // Iterador para _cadena_
        char *arr[10];
        printf("--> ");     // Indicador de prompt 
        
        //Lectura de caracteres
        while ( (ch = getchar() ) != '\n' && ch != EOF ){
            cadena[it] = ch;
            it++;
        }
        cadena[it] = '\0';
        it=0;
// Carccter nulo para indicar fin del string

        if ( ! strcmp(cadena,"salir") ){
            printf("Adios.\n");
            exit(0);
        } exit;

//Aqui separo en tokens la cadena //
        char *token = strtok(cadena, " "); 
        while(token != NULL){
                arr[it]=token;
                token = strtok(NULL, " ");
                it++;
        }
        arr[it]=NULL;
//Aqui termina la separacion de tokens//

//EJECUTANDO EL COMANDO
        //char *argv2[22]={};

        strcat(path,arr[0]);
        execvp(path,arr);
    }

   return 0;
}