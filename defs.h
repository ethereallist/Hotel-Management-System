#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Este archivo debe contener las declaraciones de variables y funciones

// ---------------------------------------------------------------------

// Declaracion de funciones:

<<<<<<< Updated upstream


// Declaracion de variables:
=======
typedef struct
{
    int Habitaciones[4][5];
} T_Hotel;

typedef struct 
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
}T_Reserva;

typedef struct
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
} T_Habitacion;

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
    else if (aa < 2024)
    {
        printf("Introduce un año valido para reservar: \n");
    }

    // Esto cambia la variable Fecha_Es_Valida del main para salir del bucle.

    else
    {
        *validar = 1;
    }
}

void Asignar_Categorias(T_Hotel Categorias)
{
    // Asigno 2 habitaciones sencillas, 2 dobles y 1 triple por piso del hotel en el main y aqui las visualizo.
    printf("Categorias de cada habitacion del hotel: \n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            
            printf("%i", Categorias.Habitaciones[i][j]);
        }
        printf("\n");
    }
}






































//________________________Funciones PARA T_Reserva __________________________


void ModificarReserva(T_Reserva * PtrCliente)
{
	 printf("Por favor, registrese para empezar.\n");
    printf("Nombre: ");
    scanf("%s", &(*PtrCliente).Nombre);
    printf("Apellido: ");
    scanf("%s", &(*PtrCliente).Apellido);
    printf("Personas totales: ");
    scanf("%i", &(*PtrCliente).Personas_Totales);
    printf("Categoria de habitacion deseada\n");
    printf("Seleccione su categoría de habitación:\n1 para Habitación Sencilla, 2 para doble, 3 para triple: ");
    scanf("%i", &(*PtrCliente).Categoria);


	
    printf("Introduzca la fecha de reserva (DD/MM/AAAA): ");
    int Fecha_Es_Valida = 0;
    do
    {
        scanf("%i/%i/%i", &(*PtrCliente).dd_Entrada, &(*PtrCliente).mm_Entrada, &(*PtrCliente).aa_Entrada);
        Validar_Fecha((*PtrCliente).dd_Entrada, (*PtrCliente).mm_Entrada, (*PtrCliente).aa_Entrada, &Fecha_Es_Valida);
    } while (Fecha_Es_Valida == 0);

    Fecha_Es_Valida = 0;

    printf("Introduzca la fecha de salida (DD/MM/AAAA): ");
    do
    {
        scanf("%i/%i/%i", &(*PtrCliente).dd_Salida, &(*PtrCliente).mm_Salida, &(*PtrCliente).aa_Salida);
        Validar_Fecha((*PtrCliente).dd_Salida, (*PtrCliente).mm_Salida, (*PtrCliente).aa_Salida, &Fecha_Es_Valida);
    } while (Fecha_Es_Valida == 0);
}


void ImprimirReserva(T_Reserva Cliente)
{
	printf("Los datos que tenemos del cliente %s %s son: \n", Cliente.Nombre, Cliente.Apellido);
    printf("-------------------------------------------\n");
    printf("Su nombre es: %s\n", Cliente.Nombre);
    printf("Su apellido es: %s\n", Cliente.Apellido);
    printf("Personas totales: %i\n", Cliente.Personas_Totales);
    printf("Fecha de reserva: %i/%i/%i \n", Cliente.dd_Entrada, Cliente.mm_Entrada, Cliente.aa_Entrada);
    printf("Fecha de salida: %i/%i/%i \n", Cliente.dd_Salida, Cliente.mm_Salida, Cliente.aa_Salida);
    printf("-------------------------------------------\n");
}



























//_______________________Funciones para VECTORES DE T_Reserva____________


int AgrandarVectorReserva(T_Reserva * *PtrVector, int * PtrTam)
{
	(*PtrTam)++;
	printf("Nueva cantidad de elementos: %i\n", (*PtrTam));
	(*PtrVector) = realloc((*PtrVector), (*PtrTam) * sizeof(T_Reserva));

	//Si hay errores
	if((*PtrVector) == NULL) return 1;
	else return 0;
}










































//________________________FUNCIONES PARA ARCHIVOS-VECTORES__________________________


const char ArchivoReservas[] = "reservas_data";


int DeArchivoAVector(T_Reserva * *PtrVector, int * Tam)
{
	FILE * PtrFile = fopen(ArchivoReservas, "rb");
	if( PtrFile == NULL)
	{
		return 1;
	}
	else
	{

		fseek(PtrFile, 0, SEEK_END);
		long TamArchivo = ftell(PtrFile);

		(*Tam) = TamArchivo / sizeof(T_Reserva);

		rewind(PtrFile);


		(*PtrVector) = calloc((*Tam), sizeof(T_Reserva));

		fread((*PtrVector), sizeof(T_Reserva), (*Tam), PtrFile);
		fclose(PtrFile);
		return 0;
	}
}

int DeVectorAArchivo(T_Reserva * Vector, int Tam)
{
	FILE * PtrFile = fopen(ArchivoReservas, "wb");
	fwrite(Vector, sizeof(T_Reserva), Tam, PtrFile);
	fclose(PtrFile);
}
