#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


void LeerCaracteres(char *cad){
        int it=0;
        char ch;            // Ultimo caracter leido
        while ( (ch = getchar() ) != '\n' && ch != EOF ){
            cad[it] = ch;
            it++;
        }
        cad[it] = '\0';
}

void structArr (char* File, char **argv2,char *inst){
    strcpy(File,"");
    strcat(File,strtok(inst," "));
    argv2[0]=File;
    int i=1;
    char *iterador;
    while(i==1 || (i<=20 && iterador != NULL )){
        iterador = strtok(NULL," ");
        argv2[i]=iterador;
        ++i;
    }
    argv2[i]=NULL;
}


void separarOR(char *cadena, char **arr){
        arr[0]=strtok(cadena,"||");
        int i = 1;
        char *iterador;
        while(i==1 || (i<=20 && iterador != NULL )){
        iterador = strtok(NULL,"||");
        arr[i]=iterador;
        ++i;
    }
i=0;
}


int main ( int argc, char** argv ){

    //Ciclo principal
    while ( 1 ){     

        char File[30]="";
        char *argv2[22]={};
        char cadena[1024];  // Almacena una linea
        char *arr[20]={};
        printf("--> ");     // Indicador de prompt 
        
        //Lectura de caracteres
        LeerCaracteres(cadena);

        if ( ! strcmp(cadena,"salir") ){
            printf("Adios.\n");
            exit(0);
        } exit;


/* ESTA SECCION ESTA EN REVISION */
        separarOR(cadena, arr);
        int cont=0;
        for(int i=0; arr[i]!=NULL;i++){
                cont++;
        }
        if(cont>1){     
       
        }
/* ESTA SECCION ESTA EN REVISION */

        structArr(File, argv2, cadena);
        int pid = fork();
            if(!pid){
                execvp(File,argv2);
                exit(-1);
            }
            wait(NULL);
//EJECUTANDO EL COMANDO
    }
   return 0;
}