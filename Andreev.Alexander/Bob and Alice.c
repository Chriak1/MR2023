#include <stdio.h>
#include <math.h>

// ���������� ����������
typedef long long int Money;  // ��� ������

const int MONTH = 240;  // ���������� �������
const int MONTH_OF_PURCHASE = 108; // ����� ������� ������
const int MONTH_OF_DEATH = 120; // ������ ������
const double CREDIT_PERCENT = 0.07;  // ������� �� �������
const double M_KOEF = 0.07 / 12;  // ����������� ������� �������
const double DEPOSIT = 0.09;  // ������� �� ������ 

Money CREDIT = 19 * 1000 * 1000 * 100;  // ����� �������
Money CREDIT_PAYMENT;  // ������ �� �������
Money FLAT = 20 * 1000 * 1000 * 100;  // ��������� ��������
Money MEDICAL_EXAMINATION = 30 * 1000 * 100; // ��������� ������������ ������������
Money COST_OF_A_HAMSTER = 10 * 1000 * 100; // ��������� ������
Money HAMSTER_FUNERAL = 10 * 1000 * 100; // ��������� ������� ������

struct person
{
    Money balance;
    Money bank;
    Money total;
    Money salary;
    Money rent;
};

struct person Alice = { .balance = 0, .bank = 1 * 1000 * 100 * 100, .total = 0, .salary = 200 * 1000 * 100, .rent =  30 * 1000 * 100 };
struct person Bob = { .balance = 0, .bank = 0, .total = 0, .salary = 200 * 1000 * 100, .rent = 0 };


Money credit_pay()  // ������ ������� �� �������
{
    int result;
    result = CREDIT * ((M_KOEF * pow(1 + M_KOEF, MONTH)) / (pow(1 + M_KOEF, MONTH) - 1));  // ������ �� �������
    return result;
}


Money count_Bob()
{
    CREDIT_PAYMENT = credit_pay();
    Bob.balance = Bob.salary - CREDIT_PAYMENT;

    for (int k = 0; k <= MONTH; ++k) {
        Bob.bank += Bob.bank * (DEPOSIT / 12);
        Bob.bank -= Bob.bank * (CREDIT_PERCENT / 12);
        Bob.bank += Bob.balance;

        if (k == MONTH_OF_PURCHASE) {
            Bob.bank -= COST_OF_A_HAMSTER;
        }

        if (k == MONTH_OF_DEATH) {
            Bob.bank -= HAMSTER_FUNERAL;
        }
    }
    return Bob.bank;
}


Money count_Alice()  // ������ ������� �����
{
    Alice.balance = Alice.salary - Alice.rent; // ����������� ������� �����

    for (int k = 0; k <= MONTH; ++k) {
        Alice.bank += Alice.bank * (DEPOSIT / 12);
        Alice.bank -= Alice.bank * (CREDIT_PERCENT / 12);
        Alice.bank += Alice.balance;

        if (k % 12 == 0) {
            Alice.bank -= MEDICAL_EXAMINATION;
        }
    }
    return Alice.bank;
}


Money count_FLAT()  // ������ ��������� ��������
{
    for (int k = 0; k <= MONTH; ++k)
    {
        FLAT += FLAT * (0.01 / 12);
    }
    return FLAT;
}


int main()
{
    Alice.total = count_Alice() / 100;
    Bob.total = (count_Bob() + count_FLAT()) / 100;
    printf("%lld   %lld", Alice.total, Bob.total);
    return 0;
}
