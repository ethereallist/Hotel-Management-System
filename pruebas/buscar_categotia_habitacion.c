#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int Hotel[4][5] = {{1, 1, 2, 2, 3},
                   {1, 1, 2, 2, 3},
                   {1, 3, 2, 2, 3},
                   {1, 1, 2, 2, 3}};

int Categorias_Precios[4] = {0, 50, 70, 90};

int Comision_Persona_Extra = 10;


typedef struct
{
	int Categoria;
	int Bool_Reservado;
} habextra;

typedef struct
{
	int Piso;
	int Puerta;
	habextra Extra;
} hab;







void Buscar_Habitacion_Por_Categoria(int Categoria, hab ** PtrVectorHabitaciones, int * Tam)
{
	(*Tam) = 1;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (Hotel[i][j] == Categoria)
			{
				(*Tam)++;
				hab * aux = (hab*)realloc(*PtrVectorHabitaciones, (*Tam) * sizeof(hab));
				free((void*)*PtrVectorHabitaciones);
				(*PtrVectorHabitaciones) = aux;
				
				(*PtrVectorHabitaciones)[(*Tam)-1].Piso = i+1;
				(*PtrVectorHabitaciones)[(*Tam)-1].Puerta = j+1;
				(*PtrVectorHabitaciones)[(*Tam)-1].Extra.Categoria = Categoria;
			}
		}
	}
}


int main()
{
	int Categoria;
	scanf("%i", &Categoria);
	hab * Habitaciones;
	int Matches;
	Buscar_Habitacion_Por_Categoria(Categoria, &Habitaciones, &Matches);
	
	for (int i = 1; i < Matches; i++)
	{
		printf("Habitacion %i-%i\n", Habitaciones[i].Piso, Habitaciones[i].Puerta);
	}
	
	return 0;
}
