#include "list.h"


int main()
{
	queue* Time;
	Input(&Time);
	int len = 0;
	int num = 0;
	printf("Input the Line: int char/int/int ...\n");
	char* InputLine = inputKeyBoard(Time, &len, &num);
	printf("Queue of history\n");
	printq(Time, 0);
	bubbleSort(Time, len);
	printf("Sorted queue of history\n");
	printq(Time, 0);
	Airport* mass;
	InputAirport(&mass, num);
	mass = individualTask(Time, mass, num, len);
	freequeue(Time);
	freeAirport(mass, num);
	free(InputLine);
	return 0;
	
}
