#include <stdio.h>

typedef struct
{
    int dd;
    int mm;
    int aa;
} date;


//FUNCIONES
int Dia_Del_Anio(date F);
int Restar_Fechas(date A, date B);
int Validar_Fecha(date F);
int esBisiesto(date F);


//MAIN
int main()
{
	date Fecha_A = {1,10,2006};
	date Fecha_B = {2,5,2024};
	int dias = Restar_Fechas(Fecha_A, Fecha_B);
	printf("%i", dias);
	return 0;
}


//FUNCIONES


int Restar_Fechas(date A, date B)
{
	//Calcular el dia del año
	int Da_A = Dia_Del_Anio(A);
	int Da_B = Dia_Del_Anio(B);
	
	
	int Anios = A.aa - B.aa;
	int Dias = Da_A - Da_B;
	
	
	//Hay que sumarle los dias extra
	int DiasExtra = 0;
	
	//Calculamos los que hay en ese intervalo
	//Se calcularon viendo si este
	
	
	//Si el primero es el mayor
	for(int aa_Revisar = A.aa; aa_Revisar < B.aa; aa_Revisar ++)
	{
		if((aa_Revisar % 4 == 0 && aa_Revisar % 100 != 0) || (aa_Revisar % 400 == 0))
		{
			if(aa_Revisar == A.aa && Da_A != 366)
			{
				DiasExtra++; //Siempre qu hay un año bisiesto, hay un dia extra, puesto que hablamos de DÍAS DEL AÑO, no de fehca especifica, es decir, no es del (2020-mar-05) al (2021-mar-05) sino (2020-mar-05 al (2021-mar-06), puesto que estos últimos SÍ representan el mismo dia del año.
			}
		}
	}
	
	
	//Si el segundo es mayor
	for(int aa_Revisar = B.aa - 1; A.aa <=  aa_Revisar ; aa_Revisar--)
	{
		if((aa_Revisar % 4 == 0 && aa_Revisar % 100 != 0) || (aa_Revisar % 400 == 0))
		{
			if(aa_Revisar == A.aa && Da_A != 366)
			{
				DiasExtra--; //Siempre qu hay un año bisiesto, hay un dia extra, puesto que hablamos de DÍAS DEL AÑO, no de fehca especifica, es decir, no es del (2020-mar-05) al (2021-mar-05) sino (2020-mar-05 al (2021-mar-06), puesto que estos últimos SÍ representan el mismo dia del año.
			}
		}
	}
	
	
	int Resultado = Anios + Dias + DiasExtra;
	
}




//_____________________FUNCIONES DE FECHA______________

int Validar_Fecha(date F)
{
    // VOY TIRANDO ERROR POR CADA FECHA INVALIDA

    //Año invalido
    if (F.aa < 1800) return 0; //No se ponga a inventar
	
    // Mes invalido
	else if ( F.mm < 1 || F.mm > 12) return -1; 
	
	//Dia invalido
    else if (F.dd < 1 || F.dd > 31) return -2; 
    
    // Excluir los dias 31 de los meses abril, junio, septiembre y noviembre.
    else if (F.mm == 4 || F.mm == 6 || F.mm == 9 || F.mm == 11) 
    {
        if (F.dd > 30) return -3; //Mes de 30 dias
    }
    
    //Excluir el los dias de febrero dependiendo de si es bisiesto o no
    else if (F.mm == 2 && esBisiesto(F) == 1 ) //PARA VER SI SÍ ES BISIESTO
    {
        if (F.dd > 29)
        {
            // Los dias deben estar (como es bisiesto) entre 1 y 29
            return -4; // El año es bisiesto
        }
        
        
    }
    else if (F.dd > 28) 
    {
            // Los dias deben estar (como es bisiesto) entre 1 y 29
            return -5;
    }
    
    
    
    //Si paso TODAS LAS PRUEBAS, la fecha el valida:
    return 1;
}



int esBisiesto(date F)
{
    // Verificar las condiciones para determinar si es bisiesto

    if ((F.aa % 4 == 0 && F.aa % 100 != 0) || (F.aa % 400 == 0)) // PARA VER SI SÍ ES BISIESTO
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int Dia_Del_Anio(date F)
{
    // Cada indice es un mes del anio y la cantidad de dias que equivalen en cada tipo de anio

    int Dias_Del_Anio_Normal[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    
    // Dias de cada mes en un anio bisiesto
    int Dias_Del_Anio_Bisiesto[12] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
    int Dias_Totales_Estadia = 0, Indice_Mes = F.mm;
    int Dias_Del_Anio;
    
    if (Validar_Fecha(F) == 1)
    {
        if(esBisiesto(F) == 1)
        {
            // Sumo los dias que ingreso el usuario + los dias que representa el mes en el anio
            Dias_Del_Anio = F.dd + Dias_Del_Anio_Bisiesto[Indice_Mes-1];
        }
        else
        {
            Dias_Del_Anio = F.dd + Dias_Del_Anio_Normal[Indice_Mes-1];
        }
        
        return Dias_Del_Anio;
    }
    else 
    {
        return 0;
    }
    
}






