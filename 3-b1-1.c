#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int a, b;
    double d = 3.14159;

    printf("������뾶�͸߶�\n");
    scanf("%d %d", &a, &b); // ע�� scanf �Ĳ������ַ�����Ӧ�ý� &a �� &b ����˫������

    printf("Բ�ܳ�     ��%.2lf\n", a * 2 * d); // ���������ʽ���Ʒ� %.2lf
    printf("Բ���     ��%.2lf\n", a * a * d); // ���������ʽ���Ʒ� %.2lf
    printf("Բ������ ��%.2lf\n", 4 * d * a * a); // ���������ʽ���Ʒ� %.2lf
    printf("Բ�����   : %.2lf\n", 4 * d * a * a * a / 3); // ���������ʽ���Ʒ� %.2lf
    printf("Բ�����   ��%.2lf\n", d * a * a * b); // ���������ʽ���Ʒ� %.2lf

    return 0;
}