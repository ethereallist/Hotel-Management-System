#include <stdio.h>

typedef struct
{
    int dd;
    int mm;
    int aa;
} date;

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

    //Año invalido
    //Acotacion: No voy a poner año invalido, PERO: para años muy anteriores, la fecha va a ser incorrecta, especialmente del 1583 para atras, pero esto puede incluso variar segun el país
    
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

int main()
{
    date F;
    int Fecha_Es_Valida = 0;
    do
    {
        printf("Introduzca una fecha (DD/MM/AAAA): ");
        scanf("%i/%i/%i", &F.dd, &F.mm, &F.aa);
        LimpiarEntrada();
        
    } while (Validar_Fecha(F) == 0); //Si no es valida, repita
    
    printf("\nBonita Fecha ;)\n");
}
