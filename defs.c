#include "defs.h"

//-----------------------VARIABLES GLOBALES--------------------
// Hay que declararlas aquí o sino no sirve

// Asigno las categorias por defecto preexistentes en el hotel
int Hotel[4][5] = {{1, 1, 2, 2, 3},
				   {1, 1, 2, 2, 3},
				   {1, 1, 2, 2, 3},
				   {1, 1, 2, 2, 3}};

int Categorias_Precios[4] = {0, 50, 70, 90};

int Comision_Persona_Extra = 10;

// Creo un """prototipo de vector""" para la Lista de las Reservas, y su tamaño
re *RESERVAS;										  // NO BORRAR
int Tam_RESERVAS;									  // NO BORRAR
const char NombreArchivoRESERVAS[] = "reservas_data"; // Modificable

// -----------------------------------------------------------------------------------------------------------------------------------------
// -----------------------------------------------DEFINICION DE LAS FUNCIONES--------------------------------------------------------------
// -----------------------------------------------------------------------------------------------------------------------------------------

//________________________MENUS INICIALES_____________________
int Iniciar()
{
	/// LEO EL ARCHIVO Y LO PASO AL VECTOR (EXTRAIGO SU INFORMACION)
	READ_RESERVAS();

	Bienvenida();
	MenuPrincipal();
}

int Bienvenida()
{
	LimpiarPantalla();
	printf("\n");
	printf("            /\\      /\\      /\\      /\\      /\\      /\\      /\\\n");
	printf("           /  \\    /  \\    /  \\    /  \\    /  \\    /  \\    /  \\\n");
	printf("               \\  /    \\  /    \\  /    \\  /    \\  /    \\  /    \\\n");
	printf("                \\/      \\/      \\/      \\/      \\/      \\/      \\\n");
	printf("\n");
	printf(" ¡Bienvenido al sistema de gestion del Hotel 'El Descanso del Páramo! \n");
	printf("\n");
	Enter();
}

int MenuPrincipal()
{
	while (1)
	{
		LimpiarPantalla();
		printf("1. Agregar reserva\n");
		printf("2. Ver todas las reservas actuales\n");
		printf("3. Consultar disponibilidad\n");
		printf("4. Buscar por número de ID\n");
		printf("0. Salir\n");

		switch (Opcion())
		{
		case 1:
			OpcionAgregarReserva();
			break;

		case 2:
			OpcionVerReservas();
			break;

			//~ case 3:
			//~ OpcionSobreescribirReserva();
			//~ break;

		case 3:
			OpcionConsultaDisponibilidad();
			break;

		case 4:
			OpcionBuscarID();
			break;

		case 0:
			MensajeSalir();
			return 0;
			break;
		}
	}
}

// ________________OPCIONES MENU_____________________-

void OpcionAgregarReserva()
{
	Agrandar_RESERVAS();
	LimpiarPantalla();
	scanReserva(&RESERVAS[Tam_RESERVAS - 1]);
	WRITE_RESERVAS(); // ESCRIBO (GUARDO) EN EL ARCHIVO
}

void OpcionVerReservas()
{
	LimpiarPantalla();

	for (int i = 0; i < Tam_RESERVAS; i++)
	{
		printf("CLIENTE #%i\n", i + 1);
		printReserva(&RESERVAS[i]);
	}
	Enter();
}

void OpcionSobreescribirReserva()
{
	LimpiarPantalla();
	printf("¿Qué reserva desea modificar?: ");

	int i;
	do
	{
		i = getInt10();
	}
	while (!(i >= 1 && i <= Tam_RESERVAS));

	i--; // Uno menos porque vamos a trabajar con vectores

	printReserva(&RESERVAS[i]);
	scanReserva(&RESERVAS[i]);
	WRITE_RESERVAS(); // ESCRIBO (GUARDO) EN EL ARCHIVO
	Enter();
}

void OpcionConsultaDisponibilidad()
{
	LimpiarPantalla();
	date E, S;

	printf("Fecha de Entrada (DD/MM/AAAA): ");
	while (scan_Date(&E) != 1);

	int Errores;
	do
	{
		printf("Fecha de Salida (DD/MM/AAAA): ");
		Errores += scan_Date(&S);
		Errores += Comparar_Fechas(E, S) != 1;
	}
	while (Errores != 0);

	BuscarHabitacionesPorFechas(E, S);
}

void OpcionBuscarID()
{
	int ID_Buscar = Pedir_ID();
	Busqueda_ID(ID_Buscar);
}

//_______________________FUNCIONES BUSQUEDA POR ID ___________________________

int Pedir_ID()
{
	// ID que se quiere buscar
	int ID_Buscar;
	do
	{
		printf("Introduzca su ID para buscar la reserva: ");
		ID_Buscar = getInt10();
	} while (ID_Buscar <= 0);

	return ID_Buscar;
}

int Busqueda_ID(int ID_Buscar)
{
	int Hay_Coincidencia = 0;
	for (int i = 0; i < Tam_RESERVAS; i++)
	{
		if (RESERVAS[i].Numero_Id == ID_Buscar)
		{
			printf("Encontré una coincidencia.\nSu reserva es la número %i\n", i + 1);
			Menu_Editar_Reserva(i);
			Hay_Coincidencia++;
			return 1;
		}
	}
	if (Hay_Coincidencia != 1)
	{
		printf("La habitacion esta libre");
		MenuPrincipal();
		return 0;
	}
}

int Menu_Editar_Reserva(int Numero_Reserva)
{

	//  Permitir la modificación de la fecha de entrada, la categoría de habitación
	// o la cancelación de la reserva.
	while (1)
	{
		LimpiarPantalla();
		printf("--------- MODIFICANDO LA RESERVA n° %i -------\n", Numero_Reserva + 1);
		printf("1. Modificar fecha de entrada y categoria de habitacion\n");
		printf("2. Cancelar reserva\n");
		printf("0. Menu principal\n");

		switch (Opcion())
		{
		case 1:
			scan_Fecha_Entrada_Solo_Categoria(&RESERVAS[Numero_Reserva]);
			break;

		case 2:
			OpcionCancelarReserva(Numero_Reserva);
			break;

		case 0:
			MenuPrincipal();
			break;
		}
	}
}

//_______________________FUNCIONES PARA CANCELAR RESERVA_____________________

int OpcionCancelarReserva(int Numero_Reserva)
{
	printReserva(&RESERVAS[Numero_Reserva]);
	ConfirmarCancelacion(Numero_Reserva);
};

int ConfirmarCancelacion(int Numero_Reserva)
{
	printf("\n¿Está seguro de que quiere cancelar la reservación?");
	int v;
	do
	{
		LimpiarPantalla();
		printf("------------------------------------------\n");
		printf("  ¿CANCELAR RESERVA?			  \n");
		printf("------------------------------------------\n");
		printf("1. SI\n");
		printf("0. Volver\n");

		
		switch (Opcion())
		{
		case 1:
			CancelarReserva(Numero_Reserva);
			v = 1;
			MenuPrincipal();
			break;

		case 0:
			v = 1;
			LimpiarPantalla();
			MenuPrincipal();
			break;
		}
	} while (v == 1);
}

void CancelarReserva(int Numero_Reserva)
{
	strcpy(RESERVAS[Numero_Reserva].Nombre, "00000000000000000000000000000000000000000000000000");
	strcpy(RESERVAS[Numero_Reserva].Apellido, "00000000000000000000000000000000000000000000000000");
	RESERVAS[Numero_Reserva].Numero_Id = 0;
	RESERVAS[Numero_Reserva].Personas_Totales = 0;
	RESERVAS[Numero_Reserva].Entrada.dd = 0;
	RESERVAS[Numero_Reserva].Entrada.mm = 0;
	RESERVAS[Numero_Reserva].Entrada.aa = 0;
	RESERVAS[Numero_Reserva].Salida.dd = 0;
	RESERVAS[Numero_Reserva].Salida.mm = 0;
	RESERVAS[Numero_Reserva].Salida.aa = 0;
	RESERVAS[Numero_Reserva].Extra.Tiempo_Estadia = 0;
	RESERVAS[Numero_Reserva].Extra.Precio_Total = 0;
	RESERVAS[Numero_Reserva].Habitacion.Piso = 0;
	RESERVAS[Numero_Reserva].Habitacion.Puerta = 0;
	RESERVAS[Numero_Reserva].Habitacion.Extra.Categoria = 0;
	RESERVAS[Numero_Reserva].Habitacion.Extra.Bool_Reservado = 0;

	WRITE_RESERVAS(); // ESCRIBO (GUARDO) EN EL ARCHIVO
	Enter();
}

//________________________FUNCIONES PARA RE __________________________
int printReserva(re *PtrReserva)
{
	for (int i = 0; i < Tam_RESERVAS; i++)
	{
		if (RESERVAS[i].Nombre == "00000000000000000000000000000000000000000000000000")
		{
			return 0;
		}
		else
		{
			CalcularExtra(PtrReserva);
			printf("\n-------------------------------------------\n");
			printf("  CLIENTE: %s %s\n", PtrReserva->Nombre, PtrReserva->Apellido);
			printf("-------------------------------------------\n");
			printf("Nombre: %s\n", PtrReserva->Nombre);
			printf("Apellido: %s\n", PtrReserva->Apellido);
			printf("Numero de identificacion: %i\n", PtrReserva->Numero_Id);
			printf("Personas totales: %i\n", PtrReserva->Personas_Totales);
			printf("Habitacion: Piso %i. Puerta %i (CATEGORIA: %i)\n", PtrReserva->Habitacion.Piso, PtrReserva->Habitacion.Puerta, PtrReserva->Habitacion.Extra.Categoria);
			printf("Fecha de reserva: %i/%i/%i \n", PtrReserva->Entrada.dd, PtrReserva->Entrada.mm, PtrReserva->Entrada.aa);
			printf("Fecha de salida: %i/%i/%i \n", PtrReserva->Salida.dd, PtrReserva->Salida.mm, PtrReserva->Salida.aa);
			printf("(Tiempo de estadía: %i noches)\n", PtrReserva->Extra.Tiempo_Estadia);
			printf("-------------------------------------------");
			printf("\n	PRECIO TOTAL A PAGAR: $%i\n", PtrReserva->Extra.Precio_Total);
			printf("\n");
			printf("-------------------------------------------\n");
			return 1;
		}
	}
}

void scanReserva(re *PtrReserva)
{

	scan_Nombre(PtrReserva);
	scan_Apellido(PtrReserva);

	scan_Num_Id(PtrReserva);
	scan_Personas_Totales(PtrReserva);

	scan_Fecha_Categoria(PtrReserva);

	// CALCULO LO DEMÁS
	// LO EXTRA
	CalcularExtra(PtrReserva);
}

void CalcularExtra(re *PtrReserva)
{
	PtrReserva->Extra.Tiempo_Estadia = Restar_Fechas(PtrReserva->Entrada, PtrReserva->Salida);
	PtrReserva->Habitacion.Extra.Categoria = Hotel[PtrReserva->Habitacion.Piso - 1][PtrReserva->Habitacion.Puerta - 1];
	int PrecioCategoria = Categorias_Precios[PtrReserva->Habitacion.Extra.Categoria];
	PtrReserva->Extra.Precio_Total = PtrReserva->Extra.Tiempo_Estadia * PrecioCategoria;
}

//_________________________SUB-FUNCIONES DE SCANRESERVA()_________________________

void scan_Nombre(re *PtrReserva)
{
	printf("Nombre: ");

	int FueModificado = 0; // Hasta que no se modifique, no sale del ciclo
	do
	{
		char ch = 0;
		int i = 0;
		do
		{
			scanf("%c", &ch);
			if (ch != '\n')
			{
				FueModificado = 1;
				(*PtrReserva).Nombre[i] = ch;
				i++;
			}
		} while (ch != '\n' && i < 50);

		// Si sobraron caracteres
		if (ch != '\n')
		{
			do
			{
				ch = getchar();
			} while (ch != '\n');
		}
	} while (FueModificado != 1);
}

void scan_Apellido(re *PtrReserva)
{
	printf("Apellido: ");

	int FueModificado = 0; // Hasta que no se modifique, no sale del ciclo
	do
	{
		char ch = 0;
		int i = 0;
		do
		{
			scanf("%c", &ch);
			if (ch != '\n')
			{
				FueModificado = 1;
				(*PtrReserva).Apellido[i] = ch;
				i++;
			}
		} while (ch != '\n' && i < 50);

		// Si sobraron caracteres
		if (ch != '\n')
		{
			do
			{
				ch = getchar();
			} while (ch != '\n');
		}
	} while (FueModificado != 1);
}

void scan_Num_Id(re *PtrReserva)
{
	int Valido = 0;
	int Aux;

	do
	{
		printf("Identificación: ");
		Aux = getInt10();

		if (Aux > 0) Valido = 1;
	}
	while (Valido != 1);
	(*PtrReserva).Numero_Id = Aux;
}

void scan_Personas_Totales(re *PtrReserva)
{
	int Valido = 0;
	int Aux;

	do
	{
		printf("Personas totales: ");
		Aux = getInt10();

		if (Aux > 0 && Aux < 10) Valido = 1;
	} while (Valido != 1 );

	(*PtrReserva).Personas_Totales = Aux;
}

// ___________________________________________HABITACION Y FECHA____________

void scan_Fecha_Categoria(re *PtrReserva)
{
	scan_Fecha_Entrada_Salida(PtrReserva);
	scan_Categoria(PtrReserva);
	while (0 == BuscarHabitacionFechaCategoria(PtrReserva));
}

void scan_Fecha_Entrada_Solo_Categoria(re *PtrReserva)
{
	scan_Fecha_Entrada_Solo(PtrReserva);
	scan_Categoria(PtrReserva);
	while (0 == BuscarHabitacionFechaCategoria(PtrReserva));
}

void scan_Fecha_Entrada_Salida(re *PtrReserva)
{
	do
	{
		printf("---------------------------------------------------\n");
		printf("   Introduzca la fecha de entrada (DD/MM/AAAA): \n");
		printf("---------------------------------------------------\n");
		scan_Date(&PtrReserva->Entrada);
	} while (Validar_Fecha((*PtrReserva).Entrada) != 1);

	int Entrada__Salida = 0;
	int Error = 0;
	do
	{
		Error = 0;
		printf("---------------------------------------------------\n");
		printf("   Introduzca la fecha de salida (DD/MM/AAAA): \n");
		printf("---------------------------------------------------\n");
		scan_Date(&PtrReserva->Salida);

		int Entrada__Salida = Comparar_Fechas(PtrReserva->Entrada, PtrReserva->Salida);

		if (!(Validar_Fecha(PtrReserva->Salida)))
		{
			Error = 1;
		}

		if (Entrada__Salida != 1)
		{
			Error = 1;
		}
	} while (Error == 1);
}

void scan_Fecha_Entrada_Solo(re *PtrReserva)
{
	do
	{
		printf("---------------------------------------------------\n");
		printf("   Introduzca la fecha de entrada (DD/MM/AAAA): \n");
		printf("---------------------------------------------------\n");
		scan_Date(&PtrReserva->Entrada);
	} while (Validar_Fecha((*PtrReserva).Entrada) != 1);

	int Entrada__Salida = 0;
	int Error = 0;
	do
	{
		Error = 0;
		printf("---------------------------------------------------\n");
		printf("  La Fecha de Salida es (DD/MM/AAAA): %i/%i/%i\n", PtrReserva->Salida.dd, PtrReserva->Salida.mm, PtrReserva->Salida.aa);
		printf("---------------------------------------------------\n");
		Enter();

		int Entrada__Salida = Comparar_Fechas(PtrReserva->Entrada, PtrReserva->Salida);

		if (!(Validar_Fecha(PtrReserva->Salida)))
		{
			Error = 1;
		}

		if (Entrada__Salida != 1)
		{
			Error = 1;
		}
	} while (Error == 1);
}

void scan_Categoria(re *PtrReserva)
{
	int Categoria;
	do
	{
		printf("---------------------------------------------------\n");
		printf("    Seleccione una categoria de Habitacion:\n");
		printf("---------------------------------------------------\n");
		printf("--> 1. Sencilla\n");
		printf("--> 2. Doble\n");
		printf("--> 3. Triple\n");
		Categoria = getInt10();
		PtrReserva->Habitacion.Extra.Categoria = Categoria;
	} while (Categoria < 1 || Categoria > 3);
}

void scan_Habitacion(re *PtrReserva)
{
	int Valido = 0;
	int Aux;

	do
	{
		printf("Seleccione el piso de su habitacion: ");
		Aux = getInt10();
		if (Aux >= 1 && Aux <= 4) Valido = 1;
	} while (Valido != 1);

	(*PtrReserva).Habitacion.Piso = Aux;

	Valido = 0;
	Aux = 0;
	do
	{
		printf("Seleccione la puerta de su habitacion: ");
		LimpiarEntrada();
		Aux = getInt10();
		if (Aux >= 1 && Aux <= 5) Valido = 1;
	} while (Valido != 1);

	(*PtrReserva).Habitacion.Puerta = Aux;
}



//~ void scan_Habitacion_Fecha(re * PtrReserva)
//~ {
//~ int Disponible = 0;

//~ do
//~ {
//~ scan_Habitacion(PtrReserva);
//~ scan_Fecha_Entrada_Salida(PtrReserva);
//~ int Disponible = ValidarDisponibilidadYPrint(PtrReserva);

//~ }
//~ while (Disponible != 1);
//~ }

// __________________FUNCIONES BUSCAR_________________________________-

int BuscarHabitacionFechaCategoria(re *PtrReserva)
{
	int Categoria = PtrReserva->Habitacion.Extra.Categoria;
	date Entrada = PtrReserva->Entrada;
	date Salida = PtrReserva->Salida;

	hab *HabitacionesDeLaCategoria = NULL; // Habitaciones de la categoria deseada
	int Tam_Hab_Cat;

	BuscarHabitacionPorCategoria(Categoria, &HabitacionesDeLaCategoria, &Tam_Hab_Cat);

	int Invalido = 0;

	// IMPRIMIR reservas disponibles y borrar las no disponibles
	printf("-------------------------------------------------------------\n");
	printf("    Las habitaciones disponibles para esa categoría son:\n");
	printf("-------------------------------------------------------------\n");
	printf("            PISO           |            PUERTA            \n");
	printf("-------------------------------------------------------------\n");
	for (int i = 0; i < Tam_Hab_Cat; i++)
	{
		hab Habitacion = HabitacionesDeLaCategoria[i];
		int DisponibleEsaFecha = ValidarDisponibilidad2(Habitacion, Entrada, Salida);
		if (DisponibleEsaFecha == 1)
		{
			printf("            %i              |              %i            \n", Habitacion.Piso, Habitacion.Puerta);
		}
		else
		{
			HabitacionesDeLaCategoria[i].Piso = 0;
			HabitacionesDeLaCategoria[i].Puerta = 0;
			Invalido++;
			if (Invalido == Tam_Hab_Cat)
			{
				printf("SIN RESULTADOS\n");
				Enter();
				return 0;
			}
		}
	}
	printf("-------------------------------------------------------------\n");

	// SCANEAR
	int Coincidencia = 0;
	do
	{
		scan_Habitacion(PtrReserva);

		// Habitacion tiene que ser igual a ALGUNA del vector
		for (int i = 0; i < Tam_Hab_Cat; i++)
		{
			if (HabitacionesDeLaCategoria[i].Piso == PtrReserva->Habitacion.Piso && HabitacionesDeLaCategoria[i].Puerta == PtrReserva->Habitacion.Puerta)
			{
				Coincidencia = 1;
				return 1;
			}
		}
	} while (Coincidencia == 0);

	return Coincidencia;
}

void BuscarHabitacionPorCategoria(int Categoria, hab **PtrVectorResultados, int *Tam)
{
	(*Tam) = 0;
	(*PtrVectorResultados) = (hab *)calloc(1, sizeof(hab));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (Hotel[i][j] == Categoria)
			{
				(*Tam)++;
				hab *aux = (hab *)realloc(*PtrVectorResultados, (*Tam) * sizeof(hab));
				// free((void *)*PtrVectorResultados);
				(*PtrVectorResultados) = aux;

				(*PtrVectorResultados)[(*Tam) - 1].Piso = i + 1;
				(*PtrVectorResultados)[(*Tam) - 1].Puerta = j + 1;
				(*PtrVectorResultados)[(*Tam) - 1].Extra.Categoria = Categoria;
			}
		}
	}
}

void BuscarHabitacionesPorFechas(date Entrada, date Salida)
{
	int HabDisponibles = 0;
	int PrimeraVez = 1;
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 5; j++)
		{
			hab Iterante = {i, j};
			HabDisponibles += ValidarDisponibilidad2(Iterante, Entrada, Salida);

			if (HabDisponibles == 1 && PrimeraVez == 1)
			{
				printf("------------------------------------------------------\n");
				printf("       HABITACIONES DISPONIBLES EN ESE RANGO:         \n");
				printf("------------------------------------------------------\n");
				PrimeraVez = 0;
			}

			if (ValidarDisponibilidad2(Iterante, Entrada, Salida))
			{
				int Categoria = Hotel[Iterante.Piso - 1][Iterante.Puerta - 1];
				printf("---> %i ---> %i -> Categoria: %i.  Precio: $%i\n", Iterante.Piso, Iterante.Puerta, Categoria, Categorias_Precios[Categoria]);
			}
		}
	}

	if (HabDisponibles == 0)
	{
		printf("------------------------------------------------------\n");
		printf("   NO SE ENCONTRARON HABITACIONES EN ESAS FECHAS :(   \n");
		printf("------------------------------------------------------\n");
	}

	Enter();
	Enter();
}

void BuscarFechas(hab Habitacion)
{
	for (int i = 0; i < Tam_RESERVAS; i++)
	{
		if (Habitacion.Piso == RESERVAS[i].Habitacion.Piso && Habitacion.Puerta == RESERVAS[i].Habitacion.Puerta)
		{
			printReserva(&RESERVAS[i]);
		}
	}
}

// Ver habitaciones ocupadas en un rango de fechas
void BuscarReservasRango(date Entrada, date Salida)
{
	printf("Reservas hechas para %i/%i/%i a %i/%i/%i", Entrada.dd, Entrada.mm, Entrada.aa, Salida.dd, Salida.mm, Salida.aa);
	for (int i = 0; i < Tam_RESERVAS; i++)
	{
		if (Las_Fechas_Coinciden(Entrada, Salida, RESERVAS[i].Entrada, RESERVAS[i].Salida))
		{
			printReserva(&RESERVAS[i]);
		}
	}
}

//~ void BuscarReservasCoincidentes(re * PtrReserva)
//~ {
//~ printf("Reservas ya hechas:\n");
//~ (*PtrReserva).Entrada.dd = 0;
//~ (*PtrReserva).Entrada.mm = 0;
//~ (*PtrReserva).Entrada.aa = 0;
//~ (*PtrReserva).Salida.dd = 0;
//~ (*PtrReserva).Salida.mm = 0;
//~ (*PtrReserva).Salida.aa = 0;

//~ int Disponible = 1;
//~ int NoDisponible = 0;
//~ for (int i = 0; i < Tam_RESERVAS-1; i++)
//~ {
//~ if ((*PtrReserva).Habitacion.Piso == RESERVAS[i].Habitacion.Piso && (*PtrReserva).Habitacion.Puerta == RESERVAS[i].Habitacion.Puerta)
//~ {
//~ if(Las_Fechas_Coinciden((*PtrReserva).Entrada, (*PtrReserva).Salida, RESERVAS[i].Entrada, RESERVAS[i].Salida))
//~ {
//~ printReserva(*PtrReserva);
//~ }
//~ }
//~ }
//~ }

//~ BuscarHabitacionesPorCategoria(

// ____________VALIDAR DISPONIBILIDAD___________________

int ValidarDisponibilidad2(hab Habitacion, date Entrada, date Salida)
{
	int Disponible = 1;
	int NoDisponible = 0;
	for (int i = 0; i < Tam_RESERVAS; i++)
	{
		if (Habitacion.Piso == RESERVAS[i].Habitacion.Piso && Habitacion.Puerta == RESERVAS[i].Habitacion.Puerta)
		{
			NoDisponible += Las_Fechas_Coinciden(Entrada, Salida, RESERVAS[i].Entrada, RESERVAS[i].Salida);
		}
	}

	Disponible = !NoDisponible;
	return Disponible;
}

// AQUI IMPRIME________________________________________________________________________________________________________________________________
int ValidarDisponibilidadYPrint(re *PtrReserva)
{
	int Disponible = 1;
	int NoDisponible = 0;
	for (int i = 0; i < Tam_RESERVAS - 1; i++)
	{
		if ((*PtrReserva).Habitacion.Piso == RESERVAS[i].Habitacion.Piso && (*PtrReserva).Habitacion.Puerta == RESERVAS[i].Habitacion.Puerta)
		{
			NoDisponible += Las_Fechas_Coinciden((*PtrReserva).Entrada, (*PtrReserva).Salida, RESERVAS[i].Entrada, RESERVAS[i].Salida);

			if (NoDisponible == 1)
			{
				printf("Ya hay reservas en ese rango:\n");
				LimpiarEntrada();
				Enter();
			}

			if (Las_Fechas_Coinciden((*PtrReserva).Entrada, (*PtrReserva).Salida, RESERVAS[i].Entrada, RESERVAS[i].Salida))
			{
				printReserva(&RESERVAS[i]);
			}

			if (i == Tam_RESERVAS - 2)
			{
				LimpiarEntrada();
				Enter();
			}
		}
	}

	Disponible = !NoDisponible;
	return Disponible;
}

//_____________________FUNCIONES DE FECHA______________

int Las_Fechas_Coinciden(date Entrada1, date Salida1, date Entrada2, date Salida2)
{
	// E2 está entre E1 y F1?    o    F2 está entre E1 y F1?
	return Fecha_En_El_Rango_Abierto(Entrada1, Salida1, Entrada2) || Fecha_En_El_Rango_Abierto(Entrada1, Salida1, Salida2);
}

int Fecha_En_El_Rango_Abierto(date I, date F, date X)
{
	// Significa Inicio -> FechaX -> Final
	// En ese orden
	int X_Esta_En_El_Rango = 0;
	if (Comparar_Fechas(I, F) == 1)
	{
		X_Esta_En_El_Rango = Comparar_Fechas(I, X) == 1 && Comparar_Fechas(X, F) == 1;
	}
	else if (Comparar_Fechas(I, F) == 0)
	{
		X_Esta_En_El_Rango = 0;
	}
	else if (Comparar_Fechas(I, F) == -1)
	{
		X_Esta_En_El_Rango = Fecha_En_El_Rango_Abierto(F, I, X);
	}

	return X_Esta_En_El_Rango;
}

int Restar_Fechas(date I, date F) // F - I
{
	int DiferenciaEnDias = 0;
	int Relacion = Comparar_Fechas(I, F);

	if (Relacion == 1)
	{
		if (I.aa == F.aa)
		{
			DiferenciaEnDias = Dia_Anio(F) - Dia_Anio(I);
		}
		else
		{
			// Los años
			int AniosDePorMedio = F.aa - I.aa - 1;
			int DiasDeAniosDePorMedio = 365 * AniosDePorMedio + Contar_Bisiestos(I.aa + 1, F.aa - 1);

			// Los cachitos
			int CachitoF = Dia_Anio(F);

			int CachitoI = 365 + Es_Bisiesto(I.aa) - Dia_Anio(I);

			DiferenciaEnDias = CachitoI + DiasDeAniosDePorMedio + CachitoF - 1; // Para no contar el propio dia
		}
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

int Contar_Bisiestos(int aaI, int aaF)
{
	int Num;
	if (aaI < aaF)
	{
		Num = Es_Bisiesto(aaI) + Contar_Bisiestos(aaI + 1, aaF);
	}
	else if (aaI == aaF)
	{
		Num = Es_Bisiesto(aaI); // Condicion de parada
	}
	else if (aaI > aaF)
	{
		Num = -Contar_Bisiestos(aaF, aaI);
	}

	return Num;
}

int Comparar_Fechas(date I, date F)
{
	// Voy matando
	if (I.aa > F.aa)
		return -1;
	else if (I.aa == F.aa)
	{
		if (Dia_Anio(I) > Dia_Anio(F))
			return -1;
		else if (Dia_Anio(I) == Dia_Anio(F))
			return 0;
	}
	return 1;
}

int Validar_Fecha(date F)
{
	// VOY TIRANDO ERROR POR CADA FECHA INVALIDA

	if (F.aa < 1800)
		return 0; // AÑO "INVALIDO"
	else
	{
		if (F.mm < 1 || F.mm > 12)
			return -1; // MES INVALIDO
		else
		{
			// Dia invalido
			if (F.dd < 1)
				return -2; // DIA INVALIDO (No es positivo)
			else
			{

				// MESES DE 31 DÍAS
				if (F.mm == 1 || F.mm == 3 || F.mm == 5 || F.mm == 7 || F.mm == 8 || F.mm == 10 || F.mm == 12)
				{
					if (F.dd > 31)
						return -3; // DÍA INVALIDO (muy grande para mes de 31 dias)
				}
				// MESES DE 30 DÍAS
				else if (F.mm == 4 || F.mm == 6 || F.mm == 9 || F.mm == 11)
				{
					if (F.dd > 30)
						return -4; // DÍA INVALIDO (muy grande para mes de 30 dias)
				}
				// FEBRERO
				else if (F.mm == 2)
				{
					if (Es_Bisiesto(F.aa))
					{
						if (F.dd > 29)
							return -5; // DÍA INVALIDO (muy grande para mes de 29 dias)
					}
					else
					{
						if (F.dd > 28)
							return -6; // DÍA INVALIDO (muy grande para mes de 28 dias)
					}
				}
				else
					return -7; // DÍA INVALIDO
			}
		}
	}

	// Si paso TODAS LAS PRUEBAS, la fecha el valida:
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
	int dda; // Dia del año

	if (Validar_Fecha(F) == 1)
	{
		if (Es_Bisiesto(F.aa) == 1)
		{
			// Sumo los dias que ingreso el usuario + los dias que representa el mes en el anio
			dda = F.dd + Dia_Anio_Bisiesto[Indice_Mes - 1];
		}
		else
		{
			dda = F.dd + Dia_Anio_Normal[Indice_Mes - 1];
		}

		return dda;
	}
	else
	{
		return 0;
	}
}

//__________________FUNCIONES PARA VECTORES DE T_RESERVA____________

int Agrandar_RESERVAS()
{
	/*DESCRIPCION: Agranda el VECTOR en 1
	Debes pasarle el int donde estas guardando el tamaño de ese vector*/
	Tam_RESERVAS++;
	printf("Nueva cantidad de elementos: %i\n", Tam_RESERVAS);
	RESERVAS = realloc(RESERVAS, Tam_RESERVAS * sizeof(re));

	// Si hay errores
	if (RESERVAS == NULL)
		return 1;
	else
		return 0;
}

//________________________FUNCIONES PARA ARCHIVOS-VECTORES__________________________
int READ_RESERVAS()
{
	/*DESCRIPCION: Lee la informacion del archivo y la pasa a RESERVAS*/

	FILE *PtrFile = fopen(NombreArchivoRESERVAS, "rb");
	if (PtrFile == NULL)
	{
		return 1;
	}
	else
	{
		// Se va al final, revisa cuanto pesa el archivo
		fseek(PtrFile, 0, SEEK_END); //se mueve 0 posiciones desde el final
		long TamArchivo = ftell(PtrFile); // me dice cuantos elementos hay desde ahi
		// Calcula cuantos elementos tiene: Peso/PesoElemento
		Tam_RESERVAS = TamArchivo / sizeof(re); // me dice el tamaño de cada reserva

		rewind(PtrFile); // Vuelve al inicio

		// Crea un vector: Reserva el espacio en memoria adecuado
		RESERVAS = calloc(Tam_RESERVAS, sizeof(re)); //hace un espacio en memoria , numero de elementos/tamano de elementos

		// Pasa los datos al vector recien creado
		fread(RESERVAS, sizeof(re), Tam_RESERVAS, PtrFile);

		fclose(PtrFile); // Cierra
		return 0;
	}
}

int WRITE_RESERVAS()
{
	/*DESCRIPCION: Hace un archivo nuevo con lo que haya en RESEVAS*/

	FILE *PtrFile = fopen(NombreArchivoRESERVAS, "wb");	 // Crea archivo
	fwrite(RESERVAS, sizeof(re), Tam_RESERVAS, PtrFile); // Escribe los datos
	fclose(PtrFile);									 // Cierra
}

//__________________FUNCIONES TONTAS___________________
int scan_Date(date *PtrFecha)
{
	char aux_dd[3];
	char aux_mm[3];
	char aux_aa[5];

	scanf("%2[^/]", aux_dd);

	if (getchar() == '/')
	{
		aux_dd[2] = '\0';
	}
	scanf("%2[^/]", aux_mm);

	if (getchar() == '/')
	{
		aux_mm[2] = '\0';
	}
	scanf("%4[^/]", aux_aa);

	if (getchar() == '/')
	{
		aux_aa[3] = '\0';
	}

	PtrFecha->dd = atoi(aux_dd);
	PtrFecha->mm = atoi(aux_mm);
	PtrFecha->aa = atoi(aux_aa);

	return Validar_Fecha((*PtrFecha));
}

date get_Date()
{
	date Fecha;
	do
	{
		char aux_dd[3];
		char aux_mm[3];
		char aux_aa[5];

		scanf("%2[^/]", aux_dd);

		if (getchar() == '/')
		{
			aux_dd[2] = '\0';
		}
		scanf("%2[^/]", aux_mm);

		if (getchar() == '/')
		{
			aux_mm[2] = '\0';
		}
		scanf("%4[^/]", aux_aa);

		if (getchar() == '/')
		{
			aux_aa[3] = '\0';
		}

		Fecha.dd = atoi(aux_dd);
		Fecha.mm = atoi(aux_mm);
		Fecha.aa = atoi(aux_aa);

	} while (Validar_Fecha(Fecha) != 1);

	return Fecha;
}

void Enter2(char Ultimo)
{
	if (Ultimo != '\n')
	{
		while (getchar() != '\n')
			;
	}
}

void Enter()
{
	printf("   Introduce Enter para continuar...");
	while (getchar() != '\n')
		;
}

void LimpiarEntrada()
{
	for (char ch; ch != EOF && ch != '\n'; ch = fgetc(stdin))
		;
}

void LimpiarPantalla()
{
	system("clear");
}

int Opcion()
{
	printf("---> ");
	return getInt10();
}

int getInt10()
{
	int Integer;
	char *String;
	long LongAux;
	do
	{
		String = getString10();
		LongAux = atol(String);
	} while (-2147483648 > LongAux || LongAux > 2147483647);
	Integer = (int)LongAux;
	return Integer;
}

char *getString10()
{
	char *String = calloc(10, sizeof(char));
	int FueModificado = 0; // Hasta que no se modifique, no sale del ciclo
	do
	{
		char ch = 0;
		int i = 0;
		do
		{
			scanf("%c", &ch);
			if (ch != '\n')
			{
				FueModificado = 1;
				String[i] = ch;
				i++;
			}
		} while (ch != '\n' && i < 10);

		// Si sobraron caracteres
		if (ch != '\n')
		{
			while (getchar() != '\n')
				;
		}
	} while (FueModificado != 1);

	return String;
}

int Salir()
{

	return 0;
}

void MensajeSalir()
{
	printf("         _.-._\n");
	printf("       _| | | |_\n");
	printf("     .' |     | '.\n");
	printf("    /   '---'   \\\n");
	printf("   |_____________|\n");
	printf("\n");
	printf(" ¡Gracias por Visitarnos!\n");
	printf("\n");
	printf("     Hotel 'El Descanso'\n");
	printf("       Del Páramo\n");
	printf("\n");
}