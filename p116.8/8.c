#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int input(int n);                                                           //һ��������֤���������뺯��
void check_I(char* string, int* y, int* m, int* d);                        //��ȡ���ڲ��ϸ������������ĺ���
int leap_year(int y);                                                   //�ж��Ƿ�Ϊ����ĺ���
int day_in_month(int y, int m);                                                    //���ڻ�ȡ�·������ĺ���
int check_date(int by, int bm, int bd, int ey, int em, int ed);                  //�����ʼ�����Ƿ�С����ֹ���ڵĺ���
int calculate(int by, int bm, int bd, int ey, int em, int ed);                  //������������ĺ���

int main()
{
	int by, bm, bd, ey, em, ed, days;                             //��ʼ�꣬��ʼ�£���ʼ�գ���ֹ�꣬��ֹ�£���ֹ�գ�������
	by = bm = bd = ey = em = ed = days = 0;                                   //��ʼ��
	
	check_I("Beginning", &by, &bm, &bd);
	printf("\n");
	check_I("Ending", &ey, &em, &ed);
	while (check_date(by, bm, bd, ey, em, ed))                       //ֱ����ʼ��С����ֹ��ǰ����ȡ�û�����
	{
		printf("\nThe beginning date is greater than or equal to the ending date\n");
		printf("Please try again.\n\n");
		check_I("Beginning", &by, &bm, &bd);
		printf("\n");
		check_I("Ending", &ey, &em, &ed);
	}

	days = calculate(by, bm, bd, ey, em, ed);
	printf("\nThere %s %d %s from %04d.%d.%d to %04d.%d.%d.\n",                     //���Ͻ����жϵ�������
		days == 1 ? "is" : "are", days, days == 1 ? "day" : "days", by, bm, bd, ey, em, ed);

	return 0;
}

int input(int n)                                                          //һ��������֤���������뺯��
{
	char ch[32];
	while (scanf("%d", &n) != 1)
	{
		scanf("%s", ch);
		printf("%s is not a significant number\n", ch);
		printf("Please try again: ");
		while (getchar() != '\n')
			continue;
	}
	while (getchar() != '\n')
		continue;
	return n;
}

void check_I(char * string, int * y, int *  m, int * d)                  //��ȡ���ڲ��ϸ������������
{
	printf("%s year: ", string);                                           //��ȡ��ݣ�֧��������������Ϊ��ݣ���˲����飩
	*y = input(*y);

	printf("%s month: ", string);                                          //��ȡ�·�
	*m = input(*m);
	while (*m > 12 || *m < 1)                                             //����·��Ƿ���Ч
	{
		printf("Please input a significant month: ");
		*m = input(*m);
	}

	printf("%s day: ", string);                                        //��ȡ����
	*d = input(*d);
	while (*d > day_in_month(*y, *m))                                   //��������Ƿ���Ч
	{
		printf("Please input a significant day: ");
		*d = input(*d);
	}
}

int leap_year(int y)                                                   //�ж��Ƿ�Ϊ����,����ʱ����1
{
	int i;
	if (!(y % 400) || (!(y % 4) && (y % 100)))
		i = 1;
	else
		i = 0;
	return i;
}

int day_in_month(int y, int m)                                                    //���ڻ�ȡ�·������ĺ���
{
	int d;
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
		d = 31;
	else if (m == 4 || m == 6 || m == 9 || m == 11)
		d = 30;
	else
	{
		if (leap_year(y))
			d = 29;
		else
			d = 28;
	}
	return d;
}

int check_date(int by, int bm, int bd, int ey, int em, int ed)              //�����ʼ�����Ƿ�С����ֹ���ڣ�������ʱ����ֵΪ0
{
	int i;
	if (by < ey)
		i = 0;
	else if (by == ey && bm < em)
		i = 0;
	else if (by == ey && bm==em && bd < ed)
		i = 0;
	else
		i = 1;
	return i;
}

int calculate(int by, int bm, int bd, int ey, int em, int ed)                  //�����������
{
	int days, i, j, k;
	days = 0;

	for (i = by; i < ey; i++)                                                 //����Ϊ��λ��������������ҿ���
	{
		if (leap_year(i))
			days += 366;
		else
			days += 365;
	}

	for (j = 1; j < bm; j++)                                                 //��ȥ��ʼ��δ��ʼ������
	{
		days -= day_in_month(by, j);
	}
	days -= bd;

	for (k = 1; k < em; k++)                                                 //������ֹ��δ����������
	{
		days += day_in_month(ey, k);
	}
	days += ed;

	return days;
}