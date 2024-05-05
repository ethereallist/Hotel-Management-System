#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Este archivo debe contener las declaraciones de variables y funciones

// -----------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------DECLARACION DE LAS VARIABLES--------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------------


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
	int Precio_Total;// = tiempo_Estadia * Categorias_Precios[Categoria] + (Personas_Extra * Comision);
} reextra;

typedef struct 
{
	char Nombre[50];
    char Apellido[50];
    int Numero_Id;
    int Personas_Totales;
    date Entrada;
    date Salida;
    hab Habitacion;
    reextra Extra;
} re;



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


// FUNCIONES DE FECHA
int Validar_Fecha(date F);
int Es_Bisiesto(int aa);
int Dia_Anio(date F);
int Contar_Bisiestos(int aaI, int aaF);
int Comparar_Fechas(date I, date F);
int Restar_Fechas(date I, date F); //F - I
int Fecha_En_El_Rango_Abierto(date I, date F, date X);
int Las_Fechas_Coinciden(date Entrada1, date Salida1, date Entrada2, date Salida2);

// FUNCIONES PARA T_RESERVA
void printReserva(re Reserva);
void scanReserva(re * PtrReserva);

// SUB-FUNCIONES DE SCANRESERVA()
void scan_Nombre(re * PtrReserva);
void scan_Apellido(re * PtrReserva);
void scan_Num_Id(re * PtrReserva);
void scan_Personas_Totales(re * PtrReserva);
void scan_Habitacion_Fecha(re * PtrReserva);

void scan_Fecha_Categoria(re * PtrReserva);
int BuscarHabitacionFechaCategoria (re * PtrReserva);
void scan_Categoria(re * PtrReserva);
void scan_Fecha_Entrada_Salida(re * PtrReserva);

void scan_Habitacion(re * PtrReserva);






int ValidarDisponibilidad(hab Habitacion, date Entrada, date Salida);
int ValidarDisponibilidadYPrint(re * PtrReserva);
void printReservasYaHechas(re * PtrReserva);
void VerHabitaciones(date Entrada, date Salida);
void VerFechas(hab Habitacion);

void Buscar_Habitacion_Por_Categoria(int Categoria, hab ** PtrVectorHabitaciones, int * Tam);



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
