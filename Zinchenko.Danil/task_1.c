#include <stdio.h>
#include <math.h>


const float INFL = 0.07;
const float ZP = 200000;

float cap_bob(float traty, float proc_mes, float remont) // функция(траты боба в мес,ставка по ипотеке годовых, стоимость ремонта в мес)
{
	float zp;
	proc_mes = proc_mes / 12;
	float cap = 0;
	float dolg_proc = 19000000 * (proc_mes * (powf(1 + proc_mes, 360)) / (powf(1 + proc_mes, 360) - 1));
	for (int i = 1; i < 360; i++)
	{
		zp = ZP * powf(1 + INFL, i  / 12);
		cap += zp;
		if (i >= 60)
		{
			remont = 0;
		}
		cap = (cap - dolg_proc - ((traty + remont) * powf(1 + (INFL / 12), i))) * (1 + (0.11 / 12));

	}
	cap = cap + 20000000*(powf(1 + INFL, 30));
	printf("\nBob's capital: ");
	printf("%f", cap);
	return cap;
};


float cap_alice(float traty, float arenda) //функция (траты элис, аренда в месяц)
{
	float zp;
	float cap = 1000000;
	for (int i = 1; i < 360; i++)
	{
		zp = ZP * powf(1 + INFL, i / 12);
		cap += zp;
		cap = (cap - ((traty + arenda) * powf(1 + (INFL / 12), i))) * (1 + (0.11 / 12));

	}
	printf("\nAlice's capital: ");
	printf("%f", cap);
	return cap;
};


int main()
{
	cap_bob(50000, 0.07, 10000);
	cap_alice(50000,30000);	
	return 0;
}
