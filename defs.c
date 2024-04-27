#include "defs.h"

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
    int Fecha_Entrada[5][7]; //formato de calendario 5 filas 7 columnas
    int Fecha_Salida[5][7]; //formato de calendario 5 filas 7 columnas
    char Tipo_Habitacion[20];
    float Precio_Total;
};


// Validación de la disponibilidad de habitaciones según la categoría y fecha seleccionada:



