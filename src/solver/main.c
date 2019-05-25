#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "../watcher/watcher.h"

int main(int argc, char** argv)
{
	// Revisamos que los parámetros sean correctos
	if(argc != 3)
	{
		printf("Uso: %s <test> <out>\nDonde\n", argv[0]);
    printf("\t<test> es la ruta al archivo a resolver\n");
		printf("\t<out> es la ruta al archivo donde se imprimirá el output\n");
		return 1;
	}

  // Abrimos el archivo en modo lectura
  char* input_filename = argv[1];
  FILE* input_file = fopen(input_filename, "r");

  if(!input_file)
  {
    fprintf(stderr, "El archivo %s no se pudo abrir. ¿Seguro que existe?\n", input_filename);
    return 2;
  }


	// Las dimensiones del problema
	int height;
	int width;

	// Leemos las dimensiones del  a partir del archivo
	fscanf(input_file, "%d %d", &height, &width);

	// Abrimos una ventana de las dimensiones dadas
	watcher_open(height, width);

  // La cantidad de puentes que tiene el problema
  int puentes;

  fscanf(input_file, "%d", &puentes);

  for(int i = 0; i < puentes; i++)
  {
    int row;
    int col;
    int degree;
    fscanf(input_file, "%d %d %d", &row, &col, &degree);

    watcher_set_cell_status(row, col, true);
    watcher_set_cell_degree(row, col, degree);
  }

  // Las coordenadas de la meta
  int goal_row;
  int goal_col;

  fscanf(input_file, "%d %d", &goal_row, &goal_col);

  watcher_set_cell_goal(goal_row, goal_col);

	// Cerramos el archivo
	fclose(input_file);

	// Paramos por 5 segundos para poder ver la ventana
	// OJO: borra los sleeps o tu código puede dar timeout
  usleep(5000000);

  watcher_snapshot("snap.png");

	// Cerramos la ventana
	watcher_close();

  // Abrimos el archivo en modo escritura
  char* output_filename = argv[2];
  FILE* output_file = fopen(output_filename, "w");

  if(!output_file)
  {
    fprintf(stderr, "El archivo %s no se pudo abrir. ¿Tienes los permisos necesarios?\n", input_filename);
    return 2;
  }

  // Imprimimos un mensaje de prueba en el archivo
  fprintf(output_file,"Hola mundo %d\n", 42);

  // Cerramos el archivo
  fclose(output_file);

	/* Retornamos 0 indicando que todo salió bien */
  return 0;
}
