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
}re;

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





// Asigno las categorias por defecto preexistentes en el hotel
T_Hotel Categorias = {{{1, 1, 2, 2, 3},
                       {1, 1, 2, 2, 3},
                       {1, 1, 2, 2, 3},
                       {1, 1, 2, 2, 3}}};


//Creo un """prototipo de vector""" para la Lista de las Reservas, y su tamaño
re * RESERVAS; //NO BORRAR
int Tam_RESERVAS; //NO BORRAR









// -----------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------DECLARACION DE LAS FUNCIONES--------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------


// MENUS INICIALES
int Iniciar();
int Bienvenida();
int MenuPrincipal();


void OpcionAgregarReserva();
void OpcionVerReservas();
void OpcionModificarReserva();


// FUNCIONES DE VALIDAR
void Validar_Fecha(T_Fecha F, int *validar);



// FUNCIONES PARA T_RESERVA
void printReserva(re Reserva);
void scanReserva(re * PtrReserva);

// SUB-FUNCIONES DE SCANRESERVA()
void scan_Nombre(re * PtrReserva);
void scan_Apellido(re * PtrReserva);
void scan_Num_Id(re * PtrReserva);
void scan_Personas_Totales(re * PtrReserva);
void scan_Categoria(re * PtrReserva);
void scan_Fecha_Entrada(re * PtrReserva);
void scan_Fecha_Salida(re * PtrReserva);



// FUNCIONES PARA VECTORES DE T_RESERVA
int Agrandar_RESERVAS();

// FUNCIONES PARA ARCHIVOS-VECTORES
int READ_RESERVAS();
int WRITE_RESERVAS();

// FUNCIONES TONTAS
void Enter();
void CualquierTecla();
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
    ///LEO EL ARCHIVO Y LO PASO AL VECTOR (EXTRAIGO SU INFORMACION)
    READ_RESERVAS();
	
    Bienvenida();
    MenuPrincipal();
}

int Bienvenida()
{	
	Limpiar();
	printf("Bienvenido al sistema de gestion del Hotel 'El Descanso del Páramo'\n");
	Enter();
}

int MenuPrincipal()
{
	while(1)
	{
		Limpiar();
		printf("1. Agregar reserva\n");
		printf("2. Ver todas las reservas actuales\n");
		printf("3. Modificar reserva\n");
		printf("0. Salir\n");
		
		switch(Opcion()-48) //-48 por ser ascii
		{
			case 1:
				OpcionAgregarReserva();
				break;
			
			case 2:
				OpcionVerReservas();
				break;
				
			case 3:
				OpcionModificarReserva();
				break;
			
			case 0:
				Limpiar();
				return 0;
				break;
		}
	}
}





void OpcionAgregarReserva()
{
	Agrandar_RESERVAS();
	Limpiar();
	scanReserva(&RESERVAS[Tam_RESERVAS-1]);
	WRITE_RESERVAS(); //ESCRIBO (GUARDO) EN EL ARCHIVO
}


void OpcionVerReservas()
{
	Limpiar();
	for(int i = 0; i < Tam_RESERVAS; i++)
	{
		printf("\n-------------------------------------------\n");
		printf("CLIENTE #%i\n", i+1);
		printReserva(RESERVAS[i]);
	}
	Enter();
	Enter();
	
}


void OpcionModificarReserva()
{
	Limpiar();
	printf("Qué reserva desea modificar?: ");
	
	
	int i;
	do
	{
		scanf("%i", &i);
	}
	while(!(i >= 1 && i <= Tam_RESERVAS));
	
	i--; //Uno menos porque vamos a trabajar con vectores
	
	printReserva(RESERVAS[i]);
	scanReserva(&RESERVAS[i]);
	WRITE_RESERVAS(); //ESCRIBO (GUARDO) EN EL ARCHIVO
	Enter();
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




void printReserva(re Reserva)
{
	printf("Los datos que tenemos del cliente %s %s son: \n", Reserva.Nombre, Reserva.Apellido);
    printf("-------------------------------------------\n");
    printf("Su nombre es: %s\n", Reserva.Nombre);
    printf("Su apellido es: %s\n", Reserva.Apellido);
    printf("Su numero de ID es: %i\n", Reserva.Numero_Id);
    printf("Personas totales: %i\n", Reserva.Personas_Totales);
    printf("Categoria de habitacion: %i\n", Reserva.Categoria);
    printf("Fecha de reserva: %i/%i/%i \n", Reserva.Entrada.dd, Reserva.Entrada.mm, Reserva.Entrada.aa);
    printf("Fecha de salida: %i/%i/%i \n", Reserva.Salida.dd, Reserva.Salida.mm, Reserva.Salida.aa);
    printf("-------------------------------------------\n");
}

void scanReserva(re * PtrReserva)
{
    
    scan_Nombre(PtrReserva);
	scan_Apellido(PtrReserva);
    
    scan_Num_Id(PtrReserva);
    scan_Personas_Totales(PtrReserva);
    scan_Categoria(PtrReserva);
	
	scan_Fecha_Entrada(PtrReserva);
	scan_Fecha_Salida(PtrReserva);
}

//_________________________SUB-FUNCIONES DE SCANRESERVA()_________________________

void scan_Nombre(re * PtrReserva)
{
	printf("Nombre: ");
	
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
				(*PtrReserva).Nombre[i] = ch;
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


void scan_Apellido(re * PtrReserva)
{
	printf("Apellido: ");
	
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
				(*PtrReserva).Apellido[i] = ch;
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


void scan_Num_Id(re * PtrReserva)
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
	(*PtrReserva).Numero_Id = Aux;
}


void scan_Personas_Totales(re * PtrReserva)
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
	
	(*PtrReserva).Personas_Totales = Aux;
}


void scan_Categoria(re * PtrReserva)
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
	
	(*PtrReserva).Categoria = Aux;
	
}

void scan_Fecha_Entrada(re * PtrReserva)
{
	printf("Introduzca la fecha de entrada (DD/MM/AAAA): ");
    int Fecha_Es_Valida = 0;
    do
    {
        scanf("%i/%i/%i", &(*PtrReserva).Entrada.dd, &(*PtrReserva).Entrada.mm, &(*PtrReserva).Entrada.aa);
        Validar_Fecha((*PtrReserva).Entrada, &Fecha_Es_Valida);
    } while (Fecha_Es_Valida == 0);
}

void scan_Fecha_Salida(re * PtrReserva)
{
	printf("Introduzca la fecha de salida (DD/MM/AAAA): ");
	int Fecha_Es_Valida = 0;
    do
    {
        scanf("%i/%i/%i", &(*PtrReserva).Salida.dd, &(*PtrReserva).Salida.mm, &(*PtrReserva).Salida.aa);
        Validar_Fecha((*PtrReserva).Salida, &Fecha_Es_Valida);
    } while (Fecha_Es_Valida == 0);
}
























//__________________FUNCIONES PARA VECTORES DE T_RESERVA____________


int Agrandar_RESERVAS()
{
	/*DESCRIPCION: Agranda el VECTOR en 1
	Debes pasarle el int donde estas guardando el tamaño de ese vector*/
	Tam_RESERVAS++;
	printf("Nueva cantidad de elementos: %i\n", Tam_RESERVAS);
	RESERVAS = realloc(RESERVAS, Tam_RESERVAS * sizeof(re));

	//Si hay errores
	if(RESERVAS == NULL) return 1;
	else return 0;
}










































//________________________FUNCIONES PARA ARCHIVOS-VECTORES__________________________
const char NombreArchivoRESERVAS[] = "reservas_data";


int READ_RESERVAS()
{
	/*DESCRIPCION: Lee la informacion del archivo y la pasa a RESERVAS*/
	
	FILE * PtrFile = fopen(NombreArchivoRESERVAS, "rb");
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
		Tam_RESERVAS = TamArchivo / sizeof(re);

		rewind(PtrFile); //Vuelve al inicio

		//Crea un vector: Reserva el espacio en memoria adecuado
		RESERVAS = calloc(Tam_RESERVAS, sizeof(re));
		
		//Pasa los datos al vector recien creado
		fread(RESERVAS, sizeof(re), Tam_RESERVAS, PtrFile);
		
		fclose(PtrFile); //Cierra
		return 0;
	}
}


int WRITE_RESERVAS()
{
	/*DESCRIPCION: Hace un archivo nuevo con lo que haya en RESEVAS*/
	
	FILE * PtrFile = fopen(NombreArchivoRESERVAS, "wb"); //Crea archivo
	fwrite(RESERVAS, sizeof(re), Tam_RESERVAS, PtrFile); //Escribe los datos
	fclose(PtrFile); //Cierra
}











































//__________________FUNCIONES TONTAS___________________
void Enter()
{
	while(getchar() != '\n');
}

void CualquierTecla()
{
	while(1)
	{
		printf("%i", getchar());
	}
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

