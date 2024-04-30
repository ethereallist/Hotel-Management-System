#include <stdio.h>
#include "defs.h"

int main()
{      
	
	/*________PROCESOS INICIALES________*/
    // Asigno las categorias por defecto preexistentes en el hotel
    T_Hotel Categorias = {{{1, 1, 2, 2, 3},
                           {1, 1, 2, 2, 3},
                           {1, 1, 2, 2, 3},
                           {1, 1, 2, 2, 3}}};
	
	//Creo un vector de tamaño no definido aún (en realidad un puntero). Este será la lista de Reservas
    T_Reserva * ListaDeReservas;
    int CantidadReservas; 
    
    //LEO de nuestro archivo la lista que ya tenía (el archivo se llama reservas_data)
    //Lo paso todo de un Archivo a un Vector
    DeArchivoAVectorReserva(&ListaDeReservas, &CantidadReservas);
	
	
	
	
	/*___________BIENVENIDA________*/
    printf("Bienvenido al sistema de gestion del Hotel 'El Descanso del Páramo'\n");
    
    printf("1. Agg reserva\n");
    printf("2. Ver todas las reservas actuales\n");
    
    switch(Opcion()-48) //-48 por ser ascii
    {
		case 1:
			AgrandarUnoVectorReserva(&ListaDeReservas, &CantidadReservas);
			ModificarReserva(&ListaDeReservas[CantidadReservas-1]);
			DeVectorReservaAArchivo(ListaDeReservas, CantidadReservas);
			break;
		
		case 2:
			for(int i = 0; i < CantidadReservas; i++)
			{
				printf("CLIENTE #%i\n", i+1);
				ImprimirReserva(ListaDeReservas[i]);
			}
			break;
	}
	
	
    Asignar_Categorias(Categorias);
    printf("\n");

    return 0;
}

// Bugs: Cuando se introduce mas de un nombre o apellido se rompe.
