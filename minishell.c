#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main ( int argc, char** argv ){

    //Ciclo principal
    while ( 1 )
    {
        char ch;            // Ultimo caracter leido
        char cadena[1024];  // Almacena una linea
        int it = 0;         // Iterador para _cadena_

        printf("--> ");     // Indicador de prompt 
        
        //Lectura de caracteres
        while ( (ch = getchar() ) != '\n' && ch != EOF )
        {
            cadena[it] = ch;
            it++;
        }
        // Carccter nulo para indicar fin del string
        cadena[it + 1] = '\0';
        //printf("La cadena es: %s\n", cadena);

        if ( ! strcmp(cadena,"salir") ){
            printf("Adios.\n");
            exit(0);
        } exit;
    }   

    return 0;
}