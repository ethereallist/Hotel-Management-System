#include <stdio.h>

typedef struct
{
    short Es_Bisiesto;
    short dd_Anio;
} date_extra;

typedef struct
{
    int dd;
    int mm;
    int aa;
    date_extra Extra;
} date;






typedef struct
{
    short Catregoria_Hab;
    float Precio_Total;
} re_extra;

typedef struct
{
    char Nombre[50];
    char Apellido[50];
    int Numero_Id;
    int Personas_Totales;
    date Entrada;
    date Salida;
    re_extra Extra;
} re;


void LimpiarEntrada();
int Validar_Fecha(date F);
int esBisiesto(date F);
int convertidor_a_dias_del_anio(date F);




























int main()
{
    re Reserva;
    date F;
    int Anio_Bisiesto = 0;

    do
    {
        printf("Introduzca una fecha (DD/MM/AAAA): ");
        scanf("%i/%i/%i", &F.dd, &F.mm, &F.aa);
        printf("Retorno: %i", Validar_Fecha(F));
    } while (Validar_Fecha(F) != 1);
    
    int dias_anio = convertidor_a_dias_del_anio(F);

    printf("El dia ese es el %i", dias_anio);

    printf("\nBonita Fecha ;)\n");
}




































void LimpiarEntrada()
{
    for (char ch; ch != EOF && ch != '\n'; ch = fgetc(stdin));
}

int Validar_Fecha(date F) //30/11/2020
{
    // VOY TIRANDO ERROR POR CADA FECHA INVALIDA

    //Año invalido
    if (F.aa < 1800) return 0; //No se ponga a inventar, en el año ese se saltaron varios dias del calendario
    //Acotacion: No voy a poner año invalido, PERO: para años muy anteriores, la fecha va a ser incorrecta, especialmente del 1583 para atras, pero esto puede incluso variar segun el país
    
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
        F.Extra.Es_Bisiesto = 1;
        return 1;
    }
    else
    {
        F.Extra.Es_Bisiesto = 0;
        return 0;
    }
}

int convertidor_a_dias_del_anio(date F)
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