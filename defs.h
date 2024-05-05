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

// OPCIONES MENU
void OpcionAgregarReserva();
void OpcionVerReservas();
void OpcionSobreescribirReserva();
void OpcionConsultaDisponibilidad();
void OpcionBuscarID();
int OpcionCancelarReserva();


// FUNCIONES PARA RE
void printReserva(re* PtrReserva);
void scanReserva(re * PtrReserva);
void CalcularExtra(re* PtrReserva);


// SUB-FUNCIONES DE SCANRESERVA()
void scan_Nombre(re * PtrReserva);
void scan_Apellido(re * PtrReserva);
void scan_Num_Id(re * PtrReserva);
void scan_Personas_Totales(re * PtrReserva);


// SUB-FUNCIONES DE FECHA Y CATEGORIA
void scan_Fecha_Categoria(re * PtrReserva);
void scan_Fecha_Entrada_Salida(re * PtrReserva);
void scan_Categoria(re * PtrReserva);
void scan_Habitacion(re * PtrReserva);
//~ void scan_Habitacion_Fecha(re * PtrReserva);

// FUNCIONES BUSCAR
void BuscarReservasRango(date Entrada, date Salida);
int BuscarHabitacionFechaCategoria (re * PtrReserva);
void BuscarHabitacionPorCategoria(int Categoria, hab ** PtrVectorHabitaciones, int * Tam);
void BuscarHabitacionesPorFechas(date Entrada, date Salida);
void BuscarFechas(hab Habitacion);
//~ void BuscarReservasCoincidentes(re * PtrReserva);

// VALIDAR DISPONIBILIDAD
int ValidarDisponibilidad2(hab Habitacion, date Entrada, date Salida);
int ValidarDisponibilidadYPrint(re * PtrReserva);




// FUNCIONES DE FECHA
int Las_Fechas_Coinciden(date Entrada1, date Salida1, date Entrada2, date Salida2);
int Fecha_En_El_Rango_Abierto(date I, date F, date X);
int Restar_Fechas(date I, date F); //F - I
int Contar_Bisiestos(int aaI, int aaF);
int Comparar_Fechas(date I, date F);
int Validar_Fecha(date F);
int Es_Bisiesto(int aa);
int Dia_Anio(date F);



// FUNCIONES PARA VECTORES DE T_RESERVA
int Agrandar_RESERVAS();

// FUNCIONES PARA ARCHIVOS-VECTORES
int READ_RESERVAS();
int WRITE_RESERVAS();


// FUNCIONES TONTAS
int scan_Date(date* Fecha);
date get_Date();
void Enter2(char Ultimo);
void Enter();
void LimpiarEntrada();
void LimpiarPantalla();
int Opcion();
int getInt10();
char* getString10();
int Salir();





int Busqueda_ID(int ID_Buscar);
int Pedir_ID();
int Menu_Editar_Reserva();
void CancelarReserva();
int ConfirmarCancelacion();

