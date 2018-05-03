//

#include "stdafx.h"
#include<iostream>

class Date
{
public:
	int nYear, nMonth, nDay;


 
     void Print()
	 {
		 printf("%d:%d:%d", nYear,nMonth,nDay);
	 }

};
 void Date::Next()
{
	 nDay++;
	 if (nDay > 30)
	 {
		 nDay -=30;
		 nMonth++;

	 }
	 if (nMonth > 12)
	 {
		 nMonth = 1;
		 nYear++;
	 }
}



int main()
{
	
	Date d(2016,12,30);
	d.Print();
	printf("\n");
	d.Next();
	d.Print();
    return 0;
}
