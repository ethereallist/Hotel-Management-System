#include <stdio.h>
#include "defs.h"

int main()
{
<<<<<<< Updated upstream
    return 0;
}
=======
    
    
    // Asigno las categorias por defecto preexistentes en el hotel
    T_Hotel Categorias = {{{1, 1, 2, 2, 3},
                           {1, 1, 2, 2, 3},
                           {1, 1, 2, 2, 3},
                           {1, 1, 2, 2, 3}}};

    printf("Bienvenido al sistema de gestion del Hotel 'El Descanso del Páramo'\n");
    
    
    T_Reserva Cliente;
    
   

    ModificarReserva(&Cliente);
    ImprimirReserva(Cliente);

    Asignar_Categorias(Categorias);
    printf("\n");

    return 0;
}

// Bugs: Cuando se introduce mas de un nombre o apellido se rompe.
