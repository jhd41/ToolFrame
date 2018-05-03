#include<iostream>
using namespace std;

double Ave(double a, double b);

int main()

{
	double bk[4];

	printf("请输入数组元素：");

	for (int i = 0; i < 4; i++) {

		scanf("%f", &bk[i]);

	}
	printf("%d",Ave(bk[1], bk[3]));


}
double Ave(double a, double b)
{
	double s;
	s = (a+b)/ 2;
	return s;
}
