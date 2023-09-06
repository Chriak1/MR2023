#include <stdio.h>
#include <math.h>
#include <locale.h>

/*
��������� ������� �����.

�� ������ � �� 1 ��� ������, �������� 200 ��� ������,
� ��� ������� �������� �� 30 ��� ������. ���������
��������� ������� ��������� �� � 30 ��� ������.

������ ����� �� ����������� �������� � ����� �� ������� �� �����.
����� ������ ����� ��� ����� ����� ����� � ���� - ������� �����
������� ������ - ��� 9% �������. 

����� 20 ��� ����� ��������, ��� ��-�� �������� ���� �� �������� �����
��������� ��������, ��� ��� ��� �� ������ � ���� ���������. 
*/
double computeAliceBank() {
    double bank = 1000000;
    float salary = 200000;
    float arendPrice = 30000;
    float life = 30000;


    for (int i = 0; i < 240; i++) {
        bank *= 1 + 9/1200;
        bank += salary - arendPrice - life;
    }

    return bank;
}


/*
��������� ������� ����.

�� ������ � ���� ������ ����, ��� ��� 1 ��� ��� �������������� �������, 
�������� 200 ��� ������. ���������
��������� ������� ��������� ��� � 30 ��� ������.

��� ����������� ������� ������������ ���������,
�������� ������� ��������. ��, ��� � ���� �������,
��� ����� �� ���� ��� 9% �������.

����� 20 ��� ��� ��������� ����������� ������, ����� ���� 
������ �������� � ����������� � ������, ����� ������� �����
�������������� � �� � ��� �� ������.
*/
double computeBobBank() {
    double bank = 0;
    int salary = 200000;
    int life = 30000;
    int percent = 7;
    float monthlyPayment = 147306.8;

    for (int i = 0; i < 240; i++) {
        bank *= 1 + 9 / 1200;
        bank += salary - monthlyPayment - life;
    }

    bank *= 1 + 9 / 1200;
    bank += salary - 142021.9;
    bank += 20000000 * pow(1.07, 20);

    return bank;
}

int main() {
    setlocale(LC_NUMERIC, "");

    double aliceBank = computeAliceBank();
    double bobBank = computeBobBank();

    printf("%i - Alice Bank after 20 years\n", (int)aliceBank);
    printf("%i - Bob Bank after 20 years\n", (int)bobBank);
    printf("Bob is richer than Alice by %i rubles", (int)(bobBank - aliceBank));

    return 0;
}