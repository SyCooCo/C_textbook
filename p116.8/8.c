#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

int input(int n);                                                           //一个简易验证正整数输入函数
void check_I(char* string, int* y, int* m, int* d);                        //获取日期并严格检验日期输入的函数
int leap_year(int y);                                                   //判断是否为闰年的函数
int day_in_month(int y, int m);                                                    //用于获取月份天数的函数
int check_date(int by, int bm, int bd, int ey, int em, int ed);                  //检查起始日期是否小于终止日期的函数
int calculate(int by, int bm, int bd, int ey, int em, int ed);                  //计算相隔天数的函数

int main()
{
	int by, bm, bd, ey, em, ed, days;                             //起始年，起始月，起始日，终止年，终止月，终止日，总天数
	by = bm = bd = ey = em = ed = days = 0;
	
	check_I("Beginning", &by, &bm, &bd);
	printf("\n");
	check_I("Ending", &ey, &em, &ed);
	while (check_date(by, bm, bd, ey, em, ed))                       //直到起始年小于终止年前，获取用户输入
	{
		printf("\nThe beginning date is greater than or equal to the ending date\n");
		printf("Please try again.\n\n");
		check_I("Beginning", &by, &bm, &bd);
		printf("\n");
		check_I("Ending", &ey, &em, &ed);
	}

	days = calculate(by, bm, bd, ey, em, ed);
	printf("\nThere %s %d %s from %04d.%d.%d to %04d.%d.%d.\n",                     //够严谨就判断单复数！
		days == 1 ? "is" : "are", days, days == 1 ? "day" : "days", by, bm, bd, ey, em, ed);

	return 0;
}

int input(int n)                                                          //一个简易验证正整数输入函数
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

void check_I(char * string, int * y, int *  m, int * d)                  //获取日期并严格检验日期输入
{
	printf("%s year: ", string);                                           //获取年份（支持任意正整数作为年份，因此不检验）
	*y = input(*y);

	printf("%s month: ", string);                                          //获取月份
	*m = input(*m);
	while (*m > 12 || *m < 1)                                             //检查月份是否有效
	{
		printf("Please input a significant month: ");
		*m = input(*m);
	}

	printf("%s day: ", string);                                        //获取日期
	*d = input(*d);
	while (*d > day_in_month(*y, *m))                                   //检查日期是否有效
	{
		printf("Please input a significant day: ");
		*d = input(*d);
	}
}

int leap_year(int y)                                                   //判断是否为闰年,成立时返回1
{
	int i;
	if (!(y % 400) || (!(y % 4) && (y % 100)))
		i = 1;
	else
		i = 0;
	return i;
}

int day_in_month(int y, int m)                                                    //用于获取月份天数的函数
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

int check_date(int by, int bm, int bd, int ey, int em, int ed)              //检查起始日期是否小于终止日期，当成立时返回值为0
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

int calculate(int by, int bm, int bd, int ey, int em, int ed)                  //计算相隔天数
{
	int days, i, j, k;
	days = 0;

	for (i = by; i < ey; i++)                                                 //以年为单位计算天数（左闭右开）
	{
		if (leap_year(i))
			days += 366;
		else
			days += 365;
	}

	for (j = 1; j < bm; j++)                                                 //减去起始年未开始的天数
	{
		days -= day_in_month(by, j);
	}
	days -= bd;

	for (k = 1; k < em; k++)                                                 //加上终止年未结束的天数
	{
		days += day_in_month(ey, k);
	}
	days += ed;

	return days;
}
