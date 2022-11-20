#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#define LEN 10

void q_sort(double* arr, int first, int last);
void exchange(double* x, double* y);

int main()
{
	double arr[LEN];
	int i;
	for (i = 0; i < LEN; i++)
		scanf("%lf", &arr[i]);
	q_sort(arr, 0, LEN-1);
	for (i = 0; i < LEN; i++)
		printf("%g ", arr[i]);
	printf("\ndone");
	return 0;
}

void q_sort(double* arr, int first, int last)
{
	double pivot = arr[first];
	int left = first, right = last;
	if (left >= right)
		return;
	while (left < right)
	{
		while (arr[right] >= pivot && left < right)
			right--;
		while (arr[left] <= pivot && left < right)
			left++;
		if (left < right)
			exchange(&arr[left], &arr[right]);
	}
	exchange(&arr[first], &arr[left]);
	q_sort(arr, first, left - 1);
	q_sort(arr, right + 1, last);
}

void exchange(double* x, double* y)
{
	double temp;
	temp = *x;
	*x = *y;
	*y = temp;
}