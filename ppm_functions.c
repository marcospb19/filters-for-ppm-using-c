#include <stdio.h>
#include <stdlib.h>


short*** criar_matriz(int n , int m)
{
	short*** matriz = malloc(sizeof(short**[n]));
	for (int i = 0; i < n; ++i)
	{
		matriz[i] = malloc(sizeof(short*[m]));
		for (int j = 0; j < m; ++j)
		{
			matriz[i][j] = malloc(sizeof(short[3]));
			matriz[i][j][0] = 0;
			matriz[i][j][1] = 0;
			matriz[i][j][2] = 0;
		}
	}
	return matriz;
}

short*** ler_imagem(FILE* file , int n , int m)
{
	short*** matriz = criar_matriz(n , m);

	short input;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				fscanf(file , "%hd" , &input);
				matriz[i][j][k] = input;
			}
		}
	}
	return matriz;
}

short*** filtro_gaussiano(short*** original , int n , int m)
{
	const int intensidade = 18;
	long media_aritmetica;
	long maximo = 0;

	short*** matriz = criar_matriz(n , m);
	for (int i = intensidade; i < n - intensidade; ++i)
	{
		for (int j = intensidade; j < m - intensidade; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				media_aritmetica = 0;

				for (int y = -intensidade; y <= intensidade; ++y)
				{
					for (int x = -intensidade; x <= intensidade; ++x)
					{
						media_aritmetica += original[i+y][j+x][k];
					}
				}
				matriz[i][j][k] = media_aritmetica /
						((intensidade * 2 + 1) * (intensidade * 2 + 1));
			}
		}
	}
	return matriz;
}

void skip_one_line(FILE* file)
{
	fscanf(file , "%*[^\n]\n");
}

int salvar_imagem(short*** matriz , int n , int m , char filename[])
{
	FILE* file = fopen(filename , "w");
	if (!file)
		exit(1);

	fprintf(file, "P3\n"
	        "# new.ppma\n"
	        "512 512\n"
	        "255\n");

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			fprintf(file , "%hd %hd %hd\n" ,
			        matriz[i][j][0],
			        matriz[i][j][1],
			        matriz[i][j][2]);
		}
	}
	return fclose(file);
}
