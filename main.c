#include "main.h"

void main(void)
{
	Init_Fun();
	while(1)
	{
		Error_Check();
		Analysis_Request();
		Key_Process();
	}
}