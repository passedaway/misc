#include "my_itoa.h"
#include <stdio.h>

/*
*just to the integer
*/
char* myitostr(int idat,char *str)
{
	char *tmp = NULL,*ret = NULL;
	int i = 0;
	char mid;
	
	ret = str;

	if(idat < 0)
	{
		idat = idat - 2 * idat;
		*str++ = '-';//if below zero,add the '-' at the fisrt bit
	}

	tmp = str;
	*tmp++ = '\0'; //already add the end symbol at the string's start position

	while(idat > 0)
	{
		*tmp++ = idat%10 + '0';
		idat /= 10;
		i++;
	}  //converse the get number.ex:number 123,then get it is 321

	tmp--;

	i = i /2;
	while(i >= 0)
	{
		mid = *str;
		*str++ = *tmp;
		*tmp-- = mid;
		i--;
	} //make the 321 to the 123 ,the string type,the middle bit didnot change,the first bit change with the last bit,and go close and next to the middle
	//when the return the first bit is the last bit

	return ret;
}
