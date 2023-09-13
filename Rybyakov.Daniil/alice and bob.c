#include <stdio.h>
#include <math.h>


//����������
typedef long long int Money; //�������

int time = 240; // ������
double creditpercent = 0.07; // ������� �� �������
double m = 0.07 / 12; // ����� ������� �������
double deposit = 0.09; //�������� � �����

Money salary = 200 * 1000 * 100; 
Money rent = 30 * 1000 * 100; //������� ��������
Money credit = 19 * 1000 * 1000 * 100; // ����� �������
Money creditpayment; //������ �� �������
Money flat = 20 * 1000 * 1000 * 100; //��������� ��������

struct Person {
	Money balance;
	Money bank;
	Money total;
};

struct Person Alice = {.bank = 1 * 1000 * 1000 * 100, .balance = 0.0};
struct Person Bob = {.bank = 0.0, .balance = 0.0 };

main() {
	Alice.balance = salary - rent; // ����������� ������� �����
	creditpayment = credit * ((m * pow(1 + m, time)) / (pow(1 + m, time) - 1)); //������ �� �������
	Bob.balance = salary - creditpayment; //����������� ������� �����
	Bob.bank = Bob.balance;

	for (int i = 1; i <= time; ++i) {
		Alice.bank += (Alice.bank * (deposit / 12));
		Bob.bank += (Bob.bank * (deposit / 12));
		Alice.bank -= Alice.bank * (0.07 / 12);
		Bob.bank -= Bob.bank * (0.07 / 12);
		Alice.bank += Alice.balance;
		Bob.bank += Bob.balance;
		flat += flat * (0.01 / 12);
	}

	Alice.total = (Alice.bank) / 100;
	Bob.total = (Bob.total + flat) / 100;

	printf("%d   %d", Alice.total, Bob.total);

}