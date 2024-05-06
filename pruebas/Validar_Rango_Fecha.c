#include <stdio.h>

typedef struct
{
    int dd;
    int mm;
    int aa;
} date;

typedef struct
{
    char Nombre[50];
    char Apellido[50];
    int Numero_Id;
    int Personas_Totales;
    date Entrada;
    date Salida;
    float Precio_Total;
} re;

// FUNCIONES
int Dia_Anio(date F);
int Restar_Fechas(date A, date B);
int Validar_Fecha(date F);
int Es_Bisiesto(int F);
int Fecha_En_El_Rango_Abierto(date I, date F, date X);
int Las_Fechas_Coinciden(date Entrada1, date Salida1, date Entrada2, date Salida2);

// MAIN
int main()
{
    //~ date Fecha_A = {1, 10, 2006};
    //~ date Fecha_B = {1, 10, 2016};
    //~ int dias = Restar_Fechas(Fecha_A, Fecha_B);
    //~ printf("%i", dias);

	

    // Fechas de la habitacion reservacion recien hecha
    date Entrada1 = {31, 1, 2023};
    date Salida1 = {10, 12, 2024};

    // Fechas de una reservacion pasada "n"
    date Entrada2 = {1, 1, 2024};
    date Salida2 = {5, 2, 2024};
	//~ if (Fecha_En_El_Rango_Abierto(Entrada1, Salida1, Entrada2))
    if(Las_Fechas_Coinciden(Entrada1, Salida1, Entrada2, Salida2))
    {
		printf("Tu ta loco");
	}
	else
	{
		printf("Fino, pasa");
	}

    return 0;
}

// FUNCIONES


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


int Contar_Bisiestos(int aaI, int aaF)
{
	int Num;
	if(aaI < aaF)
	{
		Num = Es_Bisiesto(aaI) + Contar_Bisiestos(aaI+1, aaF);
	}
	else if (aaI == aaF)
	{
		Num = Es_Bisiesto(aaI);			//Condicion de parada
	}
	else if (aaI > aaF)
	{
		Num = -Contar_Bisiestos(aaF, aaI);
	}
	
	return Num;
}


int Comparar_Fechas(date I, date F)
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
	int Relacion = Comparar_Fechas(I, F);
	
	if (Relacion == 1)
	{
		//Los años
		int AniosDePorMedio = F.aa - I.aa - 1;
		int DiasDeAniosDePorMedio = 365*AniosDePorMedio   + Contar_Bisiestos(I.aa + 1, F.aa - 1);
		
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

int Validar_Rango_Fecha(date EntradaUno, date SalidaUno, date EntradaDos, date SalidaDos)
{

    int Entrada_uno = Dia_Anio(EntradaUno);
    int Salida_uno = Dia_Anio(SalidaUno);
    int Entrada_dos = Dia_Anio(EntradaDos);
    int Salida_dos = Dia_Anio(SalidaDos);

    printf("\nEntrada uno vale: %i", Entrada_uno);
    printf("\nSalida uno vale: %i", Salida_uno);
    printf("\nEntrada dos vale: %i", Entrada_dos);
    printf("\nSalida dos vale: %i", Salida_dos);
    // Comprueba que las fechas no coincidan entre si, comparando la fecha de entrada y la de salida (1) con la fecha de entrada (2) de otra reserva
    // Y tambien compara la fecha de entrada y la de salida (1) con la fecha de salida (2) de otra reserva

    // if (Entrada_uno <= Entrada_dos && Salida_uno >= Entrada_dos && Entrada_uno <= Salida_dos && Salida_uno >= Salida_dos || Salida_uno < Salida_dos)
    // {
    //     printf("\nLas fechas coinciden, esta habitacion no está disponible en esa fecha. Buscaremos otra.");
    //     return 1;
    // }
    // else
    // {
    //     printf("Nada.");
    //     return 0;
    // }
	
	RelacionE2_S1 = Comparar_Fechas(EntradaDos, SalidaUno);
	RelacionE1_S2 = Comparar_Fechas(EntradaDos, SalidaUno);
	
     if (RelacionE2_S1 == 1 || Comparar_Fechas(EntradaUno, EntradaDos) == 0 && Comparar_Fechas(SalidaUno, SalidaDos) == 0)
    {
        printf("\nLas fechas coinciden, esta habitacion no está disponible en esa fecha. Buscaremos otra.");
        return 1;
    }
    else
    {
        printf("\nLa habitacion esta disponible.");
        return 0;
    }

    //Falta verificar que es el mismo anio
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


int Las_Fechas_Coinciden(date Entrada1, date Salida1, date Entrada2, date Salida2)
{
	// E2 está entre E1 y F1?    o    F2 está entre E1 y F1? 
	return Fecha_En_El_Rango_Abierto(Entrada1, Salida1, Entrada2) || Fecha_En_El_Rango_Abierto(Entrada1, Salida1, Salida2);
}
