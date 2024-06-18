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