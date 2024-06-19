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

void structArr(char *File, char **argv2, char *inst, bool flag_pipe)
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
	if (flag_pipe)
	{
		argv2[i-1] = "tuberia.txt";
		argv2[i] = NULL;
	}
	else
	{
		argv2[i] = NULL;
	}

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

void crear_copia(const char *file_name, int file_size)
{

	int file_fd = open(file_name, O_RDONLY);
	int copy_fp = open("tuberia_copia.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	char buffer[1024];

	struct stat file_stat;
	if (stat("tuberia.txt", &file_stat) == -1)
		perror(NULL);

	read(file_fd, buffer, file_size);
	write(copy_fp, buffer, file_size);

	close(file_fd);
	close(copy_fp);
}