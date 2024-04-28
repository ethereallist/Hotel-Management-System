#include <stdio.h>

// Este archivo debe contener las declaraciones de variables y funciones

// ---------------------------------------------------------------------

// Declaracion de variables y funciones:

struct Hotel
{
    int habitaciones[4][5];
};

struct Reserva
{
    char Nombre[50];
    char Apellido[50];
    int Numero_Id;
    int Personas_Totales;
    int dd_Entrada, mm_Entrada, aa_Entrada;
    int dd_Salida, mm_Salida, aa_Salida;
    int Categoria;
    int Num_Habitacion;
    float Precio_Total;
};

struct Habitacion
{
    int Categoria; // Sencilla, doble o triple
    int Reservada; // Si o no
    int N_Dias_Ocupada;
    char Nombre_Cliente[50];
    int Id_Cliente;
    int Numero_Habitacion;
    int Numero_Piso;
    int Fecha_Reserva;
    int Fecha_Libre;
};

void Validar_Fecha(int dd, int mm, int aa, int *validar)
{
    // Excluir fechas invalidas

    // BUGS: al introducir un caracter se rompe. Al introducir mes 04,06,09 con el 0 no entra en la condicion.

    if (dd > 31 || dd < 1)
    {
        printf("Introduce un dia valido para reservar: \n");
    }

    // Excluir los dias 31 de los meses abril, junio, septiembre y noviembre.

    else if (mm == 4 || mm == 6 || mm == 9 || mm == 11)
    {
        if (dd > 30)
        {
            printf("Este mes solo tiene 30 dias, escoja otro dia: ");
        }
        else if (aa < 2024)
        {
            printf("Introduce un año valido para reservar: \n");
        }
        else
        {
            *validar = 1;
        }
    }
    else if (mm > 12 || mm < 1)
    {
        printf("Introduce un mes valido para reservar: \n");
    }

    // Esto cambia la variable Fecha_Es_Valida del main para salir del bucle.

    else
    {
        *validar = 1;
    }
}

void Asignar_Categorias(struct Hotel)
{
    // Asigno 2 habitaciones sencillas, 2 dobles y 1 triple por piso del hotel.
    struct Hotel Categorias = {1,1,2,2,3};
    for (int i = 0; i < Categorias.habitaciones; i++)
    {
       printf("imprimo a ver si esta bien");
    }
    
}