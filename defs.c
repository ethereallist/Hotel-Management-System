#include "defs.h"

//-----------------------VARIABLES GLOBALES--------------------
// Hay que declararlas aquí o sino no sirve

// Asigno las categorias por defecto preexistentes en el hotel
T_Hotel Categorias = {{{1, 1, 2, 2, 3},
                       {1, 1, 2, 2, 3},
                       {1, 1, 2, 2, 3},
                       {1, 1, 2, 2, 3}}};


//Creo un """prototipo de vector""" para la Lista de las Reservas, y su tamaño
re * RESERVAS; //NO BORRAR
int Tam_RESERVAS; //NO BORRAR
const char NombreArchivoRESERVAS[] = "reservas_data"; //Modificable



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


































//_____________________FUNCIONES DE FECHA______________

int Validar_Fecha(date F)
{
    // VOY TIRANDO ERROR POR CADA FECHA INVALIDA

    if (F.aa < 1800) 						return 0; // AÑO "INVALIDO"
	else
	{
		if ( F.mm < 1 || F.mm > 12) 		return -1; // MES INVALIDO
		else
		{
			//Dia invalido
			if (F.dd < 1) 					return -2; // DIA INVALIDO (No es positivo)
			else
			{
				
				//MESES DE 31 DÍAS
				if (F.mm == 1 || F.mm == 3 || F.mm == 5 || F.mm == 7 || F.mm == 8 || F.mm == 10 || F.mm == 12) 
				{
					if (F.dd > 31) 			return -3; // DÍA INVALIDO (muy grande para mes de 31 dias)
				}
				//MESES DE 30 DÍAS
				else if (F.mm == 4 || F.mm == 6 || F.mm == 9 || F.mm == 11) 
				{
					if (F.dd > 30)			return -4; // DÍA INVALIDO (muy grande para mes de 30 dias)
				}
				//FEBRERO
				else if (F.mm == 2)
				{
					if(Es_Bisiesto(F.aa))
					{
						if (F.dd > 29) 		return -5; // DÍA INVALIDO (muy grande para mes de 29 dias)
					}
					else
					{
						if (F.dd > 28) 		return -6; // DÍA INVALIDO (muy grande para mes de 28 dias)
					}
					
				}
				else 						return -7; // DÍA INVALIDO
			}
		}
	}
    
    
    //Si paso TODAS LAS PRUEBAS, la fecha el valida:
    return 1;
}



int Es_Bisiesto(int aa)
{
	return (aa % 4 == 0 && aa % 100 != 0) || (aa % 400 == 0);
}


int Dia_Anio(date F)
{
    // Cada indice es un mes del anio y la cantidad de dias que equivalen en cada tipo de anio

    int Dia_Anio_Normal[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    
    // Dias de cada mes en un anio bisiesto
    int Dia_Anio_Bisiesto[12] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
    int Indice_Mes = F.mm;
    int dda; //Dia del año
    
    if (Validar_Fecha(F) == 1)
    {
        if(Es_Bisiesto(F.aa) == 1)
        {
            // Sumo los dias que ingreso el usuario + los dias que representa el mes en el anio
            dda = F.dd + Dia_Anio_Bisiesto[Indice_Mes-1];
        }
        else
        {
            dda = F.dd + Dia_Anio_Normal[Indice_Mes-1];
        }
        
        return dda;
    }
    else 
    {
        return 0;
    }
    
}


int ContarBisiestos(int aaI, int aaF)
{
	int Num;
	if(aaI < aaF)
	{
		Num = Es_Bisiesto(aaI) + ContarBisiestos(aaI+1, aaF);
	}
	else if (aaI == aaF)
	{
		Num = Es_Bisiesto(aaI);			//Condicion de parada
	}
	else if (aaI > aaF)
	{
		Num = -ContarBisiestos(aaF, aaI);
	}
	
	return Num;
}


int Relacion_Fechas(date I, date F)
{
	//Voy matando
	if 		(I.aa > F.aa) 	return -1;
	else if (I.aa == F.aa)
	{
		if(Dia_Anio(I) > Dia_Anio(F)) return -1;
		else if(Dia_Anio(I) == Dia_Anio(F)) return 0;
	}
	return 1;
}


int Restar_Fechas(date I, date F) //F - I
{
	int DiferenciaEnDias = 0;
	int Relacion = Relacion_Fechas(I, F);
	
	if (Relacion == 1)
	{
		//Los años
		int AniosDePorMedio = F.aa - I.aa - 1;
		int DiasDeAniosDePorMedio = 365*AniosDePorMedio   + ContarBisiestos(I.aa + 1, F.aa - 1);
		
		//Los cachitos
		int CachitoF = Dia_Anio(F);
		
		int CachitoI = 365 + Es_Bisiesto(I.aa) - Dia_Anio(I);
		
		DiferenciaEnDias = CachitoI + DiasDeAniosDePorMedio + CachitoF - 1; //Para no contar el propio dia
		
	}
	else if (Relacion == 0)
	{
		DiferenciaEnDias = 0;
	}
	else if (Relacion == -1)
	{
		DiferenciaEnDias = -Restar_Fechas(F, I);
	}
	
	return DiferenciaEnDias;
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
    printf("Habitacion: Piso %i. Puerta %i\n", Reserva.Habitacion_Id.Piso, Reserva.Habitacion_Id.Puerta);
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
    scan_Habitacion_Id(PtrReserva);
	
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


void scan_Habitacion_Id(re * PtrReserva)
{
	int Valido = 0;
	char Buffer;
	int Aux;
	
	do
	{
		printf("Seleccione el piso de su habitacion: ");
		Buffer = getchar();
		LimpiarEntrada();
		Aux = atoi(&Buffer);
		
		if(Aux >= 1 && Aux <= 4) Valido = 1; 
	}
	while(Valido != 1);
	
	(*PtrReserva).Habitacion_Id.Piso= Aux;
	
	Valido = 0;
	Buffer = 0;
	Aux = 0;
	do
	{
		printf("Seleccione la puerta de su habitacion: ");
		Buffer = getchar();
		LimpiarEntrada();
		Aux = atoi(&Buffer);
		
		if(Aux >= 1 && Aux <= 5) Valido = 1; 
	}
	while(Valido != 1);
	
	(*PtrReserva).Habitacion_Id.Puerta= Aux;
}

void scan_Fecha_Entrada(re * PtrReserva)
{
    do
    {
		printf("Introduzca la fecha de entrada (DD/MM/AAAA): ");
        scanf("%i/%i/%i", &(*PtrReserva).Entrada.dd, &(*PtrReserva).Entrada.mm, &(*PtrReserva).Entrada.aa);
	} while ( Validar_Fecha((*PtrReserva).Entrada) != 1);
}

void scan_Fecha_Salida(re * PtrReserva)
{
    do
    {
		printf("Introduzca la fecha de salida (DD/MM/AAAA): ");
        scanf("%i/%i/%i", &(*PtrReserva).Salida.dd, &(*PtrReserva).Salida.mm, &(*PtrReserva).Salida.aa);
    } while ( Validar_Fecha((*PtrReserva).Salida) != 1);
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

