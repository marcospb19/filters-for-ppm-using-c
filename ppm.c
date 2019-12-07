#include <stdio.h>
#include <stdlib.h>
#include "ppm_functions.c"

int main()
{
	FILE* file = fopen("blackbuck.ascii.ppm" , "r");

	if (!file)
		return 1;

	skip_one_line(file);
	skip_one_line(file);
	int n, m; fscanf(file , "%d %d\n" , &n , &m);
	skip_one_line(file);

	short*** original = ler_imagem(file , n , m);
	short*** copia = filtro_gaussiano(original , n , m);
	salvar_imagem(copia , n , m , "new.ppm");
}
