#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int dd;
    int mm;
    int aa;
} date;

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

typedef struct
{
    int Tiempo_Estadia;
    int Precio_Total; // = tiempo_Estadia * Categorias_Precios[Categoria] + (Personas_Extra * Comision);
} reextra;

typedef struct
{
    char Nombre[50];
    char Apellido[50];
    int Numero_Id;
    int Personas_Totales;
    date Entrada;
    date Salida;
    hab Habitacion_Id;
    reextra Extra;
} re;

typedef struct
{
    int Categoria; // Sencilla, doble o triple
    int Reservada; // Si o no
    int N_Dias_Ocupada;
    char Nombre_Reserva[50];
    int Id_Reserva;
    int Numero_Habitacion;
    int Numero_Piso;
    int Fecha_Reserva;
    int Fecha_Libre;
} T_Habitacion;

re *RESERVAS;     // NO BORRAR
int Tam_RESERVAS; // NO BORRAR

void printReserva(re Reserva)
{
    printf("Los datos que tenemos del cliente %s %s son: \n", Reserva.Nombre, Reserva.Apellido);
    printf("-------------------------------------------\n");
    printf("Su nombre es: %s\n", Reserva.Nombre);
    printf("Su apellido es: %s\n", Reserva.Apellido);
    printf("Su numero de ID es: %i\n", Reserva.Numero_Id);
    printf("Personas totales: %i\n", Reserva.Personas_Totales);
    printf("Habitacion: Piso %i. Puerta %i\n", Reserva.Habitacion_Id.Piso, Reserva.Habitacion_Id.Puerta);
    printf("Fecha de reserva: %i/%i/%i \n", Reserva.Entrada.dd, Reserva.Entrada.mm, Reserva.Entrada.aa);
    printf("Fecha de salida: %i/%i/%i \n", Reserva.Salida.dd, Reserva.Salida.mm, Reserva.Salida.aa);
    printf("-------------------------------------------\n");
}

int Print_Scan_ID()
{
    // ID que se quiere buscar
    int ID_Buscar;
    char aux[10];

    do
    {
        printf("Introduzca el ID para buscar la reserva: ");
        scanf("%s", &aux);
        while (getchar() != '\n')
            ;
        ID_Buscar = atoi(aux);

    } while (ID_Buscar <= 0 || ID_Buscar > 99999999);

    return ID_Buscar;
}

//re RESERVAS[2] = {"Rosa", "Rosales", 29794677};

int Busqueda_ID(re *RESERVAS, int ID_Buscar)
{
    for (int i = 0; i < Tam_RESERVAS; i++)
    {
        if (RESERVAS[i].Numero_Id == ID_Buscar)
        {
            printf("La habitacion %i tiene el mismo ID", i);
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

 re reservas = {
        .Nombre = "María",
        .Apellido = "González",
        .Numero_Id = 29794677,
        .Personas_Totales = 3,
        .Entrada = {20, 6, 2024},  // Fecha de entrada
        .Salida = {25, 6, 2024},   // Fecha de salida
        .Habitacion_Id = {102},    // ID de habitación
        };

int main()
{
    printReserva(reservas);
    Print_Scan_ID();
    return 0;
}