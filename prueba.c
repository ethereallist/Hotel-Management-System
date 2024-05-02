#include <stdio.h>

typedef struct
{
    int dd;
    int mm;
    int aa;
    int dias_del_anio;
} T_Fecha;

void LimpiarEntrada()
{
	for(char ch; ch != EOF && ch != '\n'; ch = fgetc(stdin));
}

void Mensaje_Error_Fecha_Bisiesto(T_Fecha F)
{
    printf("Hay un error, la fecha es invalida. \nEse año es bisiesto. Introduzca la fecha de nuevo.\n");
    printf("Introduzca la fecha de entrada (DD/MM/AAAA):");
    scanf("%i/%i/%i", &F.dd, &F.mm, &F.aa);
}

int Validar_Fecha(T_Fecha F)
{
    // Excluir fechas invalidas

    // BUGS: al introducir un caracter se rompe. Al introducir mes 04,06,09 con el 0 no entra en la condicion.

    if (F.dd > 31 || F.dd < 1)
    {
        printf("Introduce un dia valido para reservar: \n");
        LimpiarEntrada();
        return 1;
        
    }

    // Excluir los dias 31 de los meses abril, junio, septiembre y noviembre.

    else if (F.mm == 4 || F.mm == 6 || F.mm == 9 || F.mm == 11)
    {
        if (F.dd > 30)
        {
            printf("Este mes solo tiene 30 dias, escoja otro dia: ");
            LimpiarEntrada();
            return 1;
            
        }
        else
        {
            return 1;
        }
    }
    else if (F.mm > 12 || F.mm < 1)
    {
        printf("Introduce un mes valido para reservar: \n");
        return 1;
    }
     else if (F.aa < 2000)
    {
        printf("Introduce un año valido para reservar: \n");
        return 1;
    }
}

int esBisiesto(T_Fecha F)
{
    // Verificar las condiciones para determinar si es bisiesto

    if ((F.aa % 4 == 0 && F.aa % 100 != 0) || (F.aa % 400 == 0))
    {
        // Si estoy en el mes de febrero
        if (F.mm == 2 && !(F.dd >= 1) || !(F.dd <= 29))
        {
            // Los dias deben estar (como es bisiesto) entre 1 y 29
            return 1; // El año es bisiesto
        }
        
    }
    else if (F.mm == 2 && (F.dd > 28))
    {
            // Los dias deben estar (como es bisiesto) entre 1 y 29
            return 1;
    }
}

int anio(T_Fecha F)
{
    F.dias_del_anio = 365;
    if (esBisiesto(F) == 1)
    {
        F.dias_del_anio = 366;
    }
    else
    {
        F.dias_del_anio = 365;
    }
}

int contar_dias(T_Fecha F)
{
}

int main()
{
    T_Fecha F;

    int Fecha_Es_Valida = 0;
    do
    {
        printf("Introduzca la fecha de entrada (DD/MM/AAAA): ");
        scanf("%i/%i/%i", &F.dd, &F.mm, &F.aa);
        LimpiarEntrada();
        
    } while (Validar_Fecha(F) == 1 || esBisiesto(F) == 1);

    contar_dias(F);
    anio(F);
}