#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Este archivo debe contener las declaraciones de variables y funciones

// -----------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------DECLARACION DE LAS VARIABLES--------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
    int Habitaciones[4][5];
} T_Hotel;



typedef struct
{
	int dd;
	int mm;
	int aa;
}T_Fecha;




typedef struct 
{
    char Nombre[50];
    char Apellido[50];
    int Numero_Id;
    int Personas_Totales;
    T_Fecha Entrada;
    T_Fecha Salida;
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





// Asigno las categorias por defecto preexistentes en el hotel
T_Hotel Categorias = {{{1, 1, 2, 2, 3},
                       {1, 1, 2, 2, 3},
                       {1, 1, 2, 2, 3},
                       {1, 1, 2, 2, 3}}};

//Creo un """prototipo de vector""" para la Lista de las Reservas
T_Reserva * ListaDeReservas;
int CantidadReservas; 









// -----------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------DECLARACION DE LAS FUNCIONES--------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------


// MENUS INICIALES
int Iniciar();
int Bienvenida();
int MenuPrincipal();

// FUNCIONES DE VALIDAR
void Validar_Fecha(T_Fecha F, int *validar);



// FUNCIONES PARA T_RESERVA
void scan_Nombre(T_Reserva * PtrCliente);
void scan_Apellido(T_Reserva * PtrCliente);
void scan_Num_Id(T_Reserva * PtrCliente);
void scan_Personas_Totales(T_Reserva * PtrCliente);
void scan_Categoria(T_Reserva * PtrCliente);
void ModificarReserva(T_Reserva * PtrCliente);
void ImprimirReserva(T_Reserva Cliente);


// FUNCIONES PARA VECTORES DE T_RESERVA
int AgrandarUnoVectorReserva(T_Reserva * *PtrVector, int * PtrTam);

// FUNCIONES PARA ARCHIVOS-VECTORES
int DeArchivoAVectorReserva(T_Reserva * *PtrVector, int * PtrTam);
int DeVectorReservaAArchivo(T_Reserva * Vector, int Tam);

// FUNCIONES TONTAS
void Enter();
void LimpiarEntrada();
void Limpiar();
char Opcion();
int salir();









// -----------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------DEFINICION DE LAS FUNCIONES--------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------



//________________________MENUS INICIALES_____________________
int Iniciar()
{
    //LEO de nuestro archivo la lista que ya tenía (el archivo se llama reservas_data)
    //Lo paso todo de un Archivo a un Vector
    DeArchivoAVectorReserva(&ListaDeReservas, &CantidadReservas);
	
	
	/*___________BIENVENIDA________*/
    Bienvenida();
    MenuPrincipal();
}

int Bienvenida()
{	
	printf("Bienvenido al sistema de gestion del Hotel 'El Descanso del Páramo'\n");
}

int MenuPrincipal()
{
	while(1)
	{
		printf("1. Agg reserva\n");
		printf("2. Ver todas las reservas actuales\n");
		printf("3. Modificar reserva\n");
		printf("0. Salir\n");
		
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
					printf("\n-------------------------------------------\n");
					printf("CLIENTE #%i\n", i+1);
					ImprimirReserva(ListaDeReservas[i]);
				}
				break;
				
			case 3:
				printf("Qué reserva desea modificar?: #");
				int i; 	scanf("%i", &i);
				ModificarReserva(&ListaDeReservas[i-1]);
				DeVectorReservaAArchivo(ListaDeReservas, CantidadReservas);
				break;
			
			case 0:
				return 0;
				break;
		}
	}
}

















































































//_____________________FUNCIONES DE VALIDACION______________
void Validar_Fecha(T_Fecha F, int *validar)
{
    // Excluir fechas invalidas

    // BUGS: al introducir un caracter se rompe. Al introducir mes 04,06,09 con el 0 no entra en la condicion.

    if (F.dd > 31 || F.dd < 1)
    {
        printf("Introduce un dia valido para reservar: \n");
    }

    // Excluir los dias 31 de los meses abril, junio, septiembre y noviembre.

    else if (F.mm == 4 || F.mm == 6 || F.mm == 9 || F.mm == 11)
    {
        if (F.dd > 30)
        {
            printf("Este mes solo tiene 30 dias, escoja otro dia: ");
        }
        else if (F.aa < 2024)
        {
            printf("Introduce un año valido para reservar: \n");
        }
        else
        {
            *validar = 1;
        }
    }
    else if (F.mm > 12 || F.mm < 1)
    {
        printf("Introduce un mes valido para reservar: \n");
    }
    else if (F.aa < 2024)
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






































//________________________FUNCIONES PARA T_RESERVA __________________________
void scan_Nombre(T_Reserva * PtrCliente)
{
	int FueModificado = 0; //Hasta que no se modifique, no sale del ciclo
	
	do
	{
		char ch = 0;
		int i = 0;
		do
		{
			scanf("%c", &ch);
			if(ch != '\n')
			{
				FueModificado = 1;
				(*PtrCliente).Nombre[i] = ch;
				i++;
			}
		}
		while(ch != '\n' && i < 50);
		
		//Si sobraron caracteres
		if(ch != '\n')
		{
			do
			{
				ch = getchar();
			}
			while(ch != '\n');
		}
	}
	while(FueModificado != 1);
}


void scan_Apellido(T_Reserva * PtrCliente)
{
	int FueModificado = 0; //Hasta que no se modifique, no sale del ciclo
	
	do
	{
		char ch = 0;
		int i = 0;
		do
		{
			scanf("%c", &ch);
			if(ch != '\n')
			{
				FueModificado = 1;
				(*PtrCliente).Apellido[i] = ch;
				i++;
			}
		}
		while(ch != '\n' && i < 50);
		
		//Si sobraron caracteres
		if(ch != '\n')
		{
			do
			{
				ch = getchar();
			}
			while(ch != '\n');
		}
	}
	while(FueModificado != 1);
}


void scan_Num_Id(T_Reserva * PtrCliente)
{
	int Valido = 0;
	char Buffer[10];
	int Aux;
	
	do
	{
		
		printf("Identificación: ");
		scanf("%s", &Buffer);
		LimpiarEntrada();
		Aux = atoi(Buffer);
		
		if(Aux > 0) Valido = 1; 
	}
	while(Valido != 1);
	(*PtrCliente).Numero_Id = Aux;
}


void scan_Personas_Totales(T_Reserva * PtrCliente)
{
	int Valido = 0;
	char Buffer;
	int Aux;
	
	do
	{
		
		printf("Personas totales: ");
		Buffer = getchar();
		LimpiarEntrada();
		Aux = atoi(&Buffer);
		
		if(Aux > 0) Valido = 1; 
	}
	while(Valido != 1);
	
	(*PtrCliente).Personas_Totales = Aux;
}


void scan_Categoria(T_Reserva * PtrCliente)
{
	int Valido = 0;
	char Buffer;
	int Aux;
	
	do
	{
		printf("Categoria de habitacion deseada\n");
		printf("Seleccione su categoría de habitación:\n1. Habitación Sencilla\n2. Habitacion doble\n3. Habitacion triple\n");
		Buffer = getchar();
		LimpiarEntrada();
		Aux = atoi(&Buffer);
		
		if(Aux >= 1 && Aux <= 3) Valido = 1; 
	}
	while(Valido != 1);
	
	(*PtrCliente).Categoria = Aux;
	
}


void ModificarReserva(T_Reserva * PtrCliente)
{
    printf("Nombre: ");
    scan_Nombre(PtrCliente);
    printf("Apellido: ");
	scan_Apellido(PtrCliente);
    
    scan_Num_Id(PtrCliente);
    scan_Personas_Totales(PtrCliente);
    scan_Categoria(PtrCliente);


	
    printf("Introduzca la fecha de reserva (DD/MM/AAAA): ");
    int Fecha_Es_Valida = 0;
    do
    {
        scanf("%i/%i/%i", &(*PtrCliente).Entrada.dd, &(*PtrCliente).Entrada.mm, &(*PtrCliente).Entrada.aa);
        Validar_Fecha((*PtrCliente).Entrada, &Fecha_Es_Valida);
    } while (Fecha_Es_Valida == 0);

    Fecha_Es_Valida = 0;

    printf("Introduzca la fecha de salida (DD/MM/AAAA): ");
    do
    {
        scanf("%i/%i/%i", &(*PtrCliente).Salida.dd, &(*PtrCliente).Salida.mm, &(*PtrCliente).Salida.aa);
        Validar_Fecha((*PtrCliente).Salida, &Fecha_Es_Valida);
    } while (Fecha_Es_Valida == 0);
}





void ImprimirReserva(T_Reserva Cliente)
{
	printf("Los datos que tenemos del cliente %s %s son: \n", Cliente.Nombre, Cliente.Apellido);
    printf("-------------------------------------------\n");
    printf("Su nombre es: %s\n", Cliente.Nombre);
    printf("Su apellido es: %s\n", Cliente.Apellido);
    printf("Su numero de ID es: %i\n", Cliente.Numero_Id);
    printf("Personas totales: %i\n", Cliente.Personas_Totales);
    printf("Categoria de habitacion: %i\n", Cliente.Categoria);
    printf("Fecha de reserva: %i/%i/%i \n", Cliente.Entrada.dd, Cliente.Entrada.mm, Cliente.Entrada.aa);
    printf("Fecha de salida: %i/%i/%i \n", Cliente.Salida.dd, Cliente.Salida.mm, Cliente.Salida.aa);
    printf("-------------------------------------------\n");
}



























//__________________FUNCIONES PARA VECTORES DE T_RESERVA____________


int AgrandarUnoVectorReserva(T_Reserva * *PtrVector, int * PtrTam)
{
	/*DESCRIPCION: Agranda el VECTOR en 1
	Debes pasarle el int donde estas guardando el tamaño de ese vector*/
	(*PtrTam)++;
	printf("Nueva cantidad de elementos: %i\n", (*PtrTam));
	(*PtrVector) = realloc((*PtrVector), (*PtrTam) * sizeof(T_Reserva));

	//Si hay errores
	if((*PtrVector) == NULL) return 1;
	else return 0;
}










































//________________________FUNCIONES PARA ARCHIVOS-VECTORES__________________________
const char ArchivoReservas[] = "reservas_data";


int DeArchivoAVectorReserva(T_Reserva * *PtrVector, int * PtrTam)
{
	/*DESCRIPCION: Lee lo que hay en el archivo y lo pasa a UN VECTOR, y tambien te dice el TAMAÑO que tiene este
	Le tienes que pasar un apuntador a una direccion de vector para que guarde los datos ahí
	Tambien le pasas apuntador a un entero para que lo modifique y te diga el tamaño del vector que crea*/
	
	FILE * PtrFile = fopen(ArchivoReservas, "rb");
	if( PtrFile == NULL)
	{
		return 1;
	}
	else
	{
		//Se va al final, revisa cuanto pesa el archivo
		fseek(PtrFile, 0, SEEK_END);
		long TamArchivo = ftell(PtrFile);
		//Calcula cuantos elementos tiene: Peso/PesoElemento
		(*PtrTam) = TamArchivo / sizeof(T_Reserva);

		rewind(PtrFile); //Vuelve al inicio

		//Crea un vector: Reserva el espacio en memoria adecuado
		(*PtrVector) = calloc((*PtrTam), sizeof(T_Reserva));
		
		//Pasa los datos al vector recien creado
		fread((*PtrVector), sizeof(T_Reserva), (*PtrTam), PtrFile);
		
		fclose(PtrFile); //Cierra
		return 0;
	}
}


int DeVectorReservaAArchivo(T_Reserva * Vector, int Tam)
{
	/*DESCRIPCION: Fácil, toma lo que hay en un VECTOR (tmb le indicas el TAMAÑO) y lo guarda en el archivo
	CABE DESTACAR, que crea el archivo de 0*/
	
	FILE * PtrFile = fopen(ArchivoReservas, "wb"); //Crea archivo
	fwrite(Vector, sizeof(T_Reserva), Tam, PtrFile); //Escribe los datos
	fclose(PtrFile); //Cierra
}











































//__________________FUNCIONES TONTAS___________________
void Enter()
{
	while(getchar() != '\n');
}

void LimpiarEntrada()
{
	for(char ch; ch != EOF && ch != '\n'; ch = fgetc(stdin));
}

void Limpiar()
{
	system("clear");
}


char Opcion()
{
	//El primer caracter que introduces, el lo toma y lo devuelve
	
	printf("---> ");
	char ch;
	char chfinal = 0;
	int FueAlgoDiferenteDeN = 0;
	do
	{
		char ch = getchar();
		
		if(ch != '\n' && chfinal == 0) //Solo se va a ejecutar una vez
		{
			FueAlgoDiferenteDeN = 1;
			chfinal = ch;
		}
	}
	while(FueAlgoDiferenteDeN == 0);
	return chfinal;
}

