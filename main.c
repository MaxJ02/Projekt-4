#include "header.h"

/******************************************************************************************
* main.c: Temperaturen skickas till en seriell monitor via USART en gång i minuten eller vid
*       nedtryckning av tryckknappen på PIN 13. Hur ofta temperaturen mäts anpassas efter 
*       hur ofta tryckknappen trycks ned, och genomsnittstemperaturen skrivs ut i samband 
*       med temperaturmätning.
*****************************************************************************************/

int main(void)
{
	setup();
	
	while (1)
	{
		
	}
	return 0;
}
