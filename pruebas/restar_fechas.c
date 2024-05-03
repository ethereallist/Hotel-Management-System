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


//MAIN
int main()
{
	date Fecha_A = {1,10,2006};
	date Fecha_B = {2,5,2024};
	Restar_Fechas(Fecha_A, Fecha_B);
	return 0;
}


//FUNCIONES
int Dia_Del_Anio(date F)
{
	int Resultado = 0;
	
	int DiasMeses[13] =
	{0, 31,28,31,  30,31,30,  31,31,30,  31,30,31};
	
	if((F.aa % 4 == 0 && F.aa % 100 != 0) || (F.aa % 400 == 0))
	{
		DiasMeses[2]++;
	}
	
	for(int i = 1; i <= F.mm; i)
	{
		Resultado += DiasMeses[i-1];
	}
	
	Resultado += F.dd;
	return Resultado;
}


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







