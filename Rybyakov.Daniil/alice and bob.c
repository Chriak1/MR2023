#include <stdio.h>
#include <math.h>


//����������
typedef long long int Money;  //�������

int MONTH = 240;  // ������
double CREDITPERCENT = 0.07;  // ������� �� �������
double m_koef = 0.07 / 12;  // ����� ������� �������
double DEPOSIT = 0.09;  //�������� � �����

Money CREDIT = 19 * 1000 * 1000 * 100;  // ����� �������
Money CREDITPAYMENT;  //������ �� �������
Money FLAT = 20 * 1000 * 1000 * 100;  //��������� ��������


struct Person 
{
	Money balance;
	Money bank;
	Money total;
	Money salary;
	Money rent;
};

struct Person Alice = { 0.0,  1 * 1000 * 1000 * 100,  0.0,  200 * 1000 * 100,  30 * 1000 * 100};
struct Person Bob = {0.0,  0.0,  0.0,  200 * 1000 * 100,  0.0};


Money creditpay(int credit, double m, int time) 
{
	int result;
	result = credit * ((m * pow(1 + m, time)) / (pow(1 + m, time) - 1));  //������ �� �������
	return result;
}


main()
{
	CREDITPAYMENT = creditpay(CREDIT, m_koef, MONTH);

	Alice.balance = Alice.salary - Alice.rent;  // ����������� ������� �����
	Bob.balance = Bob.salary - CREDITPAYMENT;  //����������� ������� �����
	Bob.bank = Bob.balance;

		for (int i = 1; i <= MONTH; ++i)
		{
			Alice.bank += (Alice.bank * (DEPOSIT / 12));
			Bob.bank += (Bob.bank * (DEPOSIT / 12));
			Alice.bank -= Alice.bank * (0.07 / 12);
			Bob.bank -= Bob.bank * (0.07 / 12);
			Alice.bank += Alice.balance;
			Bob.bank += Bob.balance;
			FLAT += FLAT * (0.01 / 12);
		}

	Alice.total = Alice.bank / 100;
	Bob.total = (Bob.bank + FLAT) / 100;

	printf("%d   %d", Alice.total, Bob.total);
}