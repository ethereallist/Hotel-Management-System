/*1. Datos Predeterminados:
• Pisos: El hotel tendrá 4 pisos.
• Habitaciones por piso: Cada piso tendrá 5 habitaciones.
• Categorías de habitaciones:
◦ Sencilla: 1 cama individual, baño privado, $50 por noche.
◦ Doble: 1 cama matrimonial, baño privado, $70 por noche.
◦ Triple: 1 cama matrimonial + 1 cama individual, baño privado, $90 por
noche.*/

#include <stdio.h>
#include "defs.h"

int main()
{
    struct Reserva cliente;
    int Fecha_Es_Valida = 0;

    printf("Bienvenido al sistema de gestion del Hotel 'El Descanso del Páramo'\n");
    printf("Por favor, registrese para empezar.\n");
    printf("Nombre: ");
    scanf("%s", &cliente.Nombre);
    printf("Apellido: ");
    scanf("%s", &cliente.Apellido);
    printf("Personas totales: ");
    scanf("%i", &cliente.Personas_Totales);
    printf("Categoria de habitacion deseada\n");
    printf("Seleccione su categoría de habitación:\n1 para Habitación Sencilla, 2 para doble, 3 para triple: ");
    scanf("%i", &cliente.Categoria);

    printf("Introduzca la fecha de reserva: ");
    do
    {
        scanf("%i/%i/%i", &cliente.dd_Entrada, &cliente.mm_Entrada, &cliente.aa_Entrada);
        Validar_Fecha(cliente.dd_Entrada, cliente.mm_Entrada, cliente.aa_Entrada, &Fecha_Es_Valida);
    } while (Fecha_Es_Valida == 0);

    Fecha_Es_Valida = 0;

    printf("Introduzca la fecha de salida: ");
    do
    {
        scanf("%i/%i/%i", &cliente.dd_Salida, &cliente.mm_Salida, &cliente.aa_Salida);
        Validar_Fecha(cliente.dd_Salida, cliente.mm_Salida, cliente.aa_Salida, &Fecha_Es_Valida);
    } while (Fecha_Es_Valida == 0);

    printf("Los datos que tenemos del cliente %s %s son: \n", cliente.Nombre, cliente.Apellido);
    printf("-------------------------------------------\n");
    printf("Su nombre es: %s\n", cliente.Nombre);
    printf("Su apellido es: %s\n", cliente.Apellido);
    printf("Personas totales: %i\n", cliente.Personas_Totales);
    printf("Fecha de reserva: %i/%i/%i \n", cliente.dd_Entrada, cliente.mm_Entrada, cliente.aa_Entrada);
    printf("Fecha de salida: %i/%i/%i \n", cliente.dd_Salida, cliente.mm_Salida, cliente.aa_Salida);
    printf("-------------------------------------------");

    printf("\n");

    return 0;
}

// Bugs: Cuando se introduce mas de un nombre o apellido se rompe.