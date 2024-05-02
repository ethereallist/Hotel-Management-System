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

void LimpiarEntrada()
{
	for(char ch; ch != EOF && ch != '\n'; ch = fgetc(stdin));
}

void Mensaje_Error_Fecha_Bisiesto(date F)
{
    printf("Hay un error, la fecha es invalida. \nEse año es bisiesto. Introduzca la fecha de nuevo.\n");
    printf("Introduzca la fecha de entrada (DD/MM/AAAA):");
    scanf("%i/%i/%i", &F.dd, &F.mm, &F.aa);
}

int Validar_Fecha(date F)
{
    // VOY TIRANDO ERROR POR CADA FECHA INVALIDA

    // BUGS: al introducir un caracter se rompe. Al introducir mes 04,06,09 con el 0 no entra en la condicion.
    // Mes invalido
	if ( F.mm < 1 || F.mm > 12) return 0; 
	
	//Dia invalido
    else if (F.dd < 1 || F.dd > 31) return 0; 
    
    // Excluir los dias 31 de los meses abril, junio, septiembre y noviembre.
    else if (F.mm == 4 || F.mm == 6 || F.mm == 9 || F.mm == 11) 
    {
        if (F.dd > 30) return 0; //Mes de 30 dias
    }
    
    //Excluir el los dias de febrero dependiendo de si es bisiesto o no
    // Verificar las condiciones para determinar si es bisiesto

    if ((F.aa % 4 == 0 && F.aa % 100 != 0) || (F.aa % 400 == 0)) //PARA VER SI SÍ ES BISIESTO
    {
        // Si estoy en el mes de febrero
        if (F.mm == 2 && !(F.dd >= 1) || !(F.dd <= 29))
        {
            // Los dias deben estar (como es bisiesto) entre 1 y 29
            return 0; // El año es bisiesto
        }
        
    }
    else if (F.mm == 2 && (F.dd > 28)) 
    {
            // Los dias deben estar (como es bisiesto) entre 1 y 29
            return 0;
    }
    
    
    
    //Si paso TODAS LAS PRUEBAS, la fecha el valida:
    return 1;
}

void convertidor_a_dias_del_anio(re * Entrada, Fecha_Es_Valida)
{
    // Dias de cada mes en un anio normal

    int enero = 0, 
    febrero = 31, 
    marzo = 59, 
    abril = 90, 
    mayo = 120, 
    junio = 151, 
    julio = 181, 
    agosto = 212, 
    septiembre = 243, 
    octubre = 273, 
    noviembre = 304, 
    diciembre = 334;

   int dias_del_anio_normal[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
   int dias_del_anio_bisiesto[12] = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};

   



    // Dias de cada mes en un anio bisiesto
}

int main()
{
    date F;
    int Fecha_Es_Valida = 0;
    do
    {
        printf("Introduzca una fecha (DD/MM/AAAA): ");
        scanf("%i/%i/%i", &F.dd, &F.mm, &F.aa);
        LimpiarEntrada();
        
    } while (Validar_Fecha(F) == 0);
    
    printf("\nBonita Fecha ;)\n");

    convertidor_a_dias_del_anio(re , Validar_Fecha(F));
}
