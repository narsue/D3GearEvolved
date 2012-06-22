#include <iostream>
using namespace std;
#include "Population.h"
#include <Windows.h>
#pragma comment(lib,"winmm.lib")
int main()
{
	printf("Currently Equipped\n");
	BehaviourArchive::getInstance()->printCurrentEquipped();

	srand(timeGetTime());
	Population pop(1000);

	for (int i =0;i<100;i++)
	{
		printf("Gen:%d:Fitness Highest:%4.2f Lowest:%4.2f Average:%4.2f\n",i,pop.getHighestFitness(),pop.getLowestFitness(),pop.getAverageFitness());
		pop.update();
	}

	printf("Best solution -\n");
	BehaviourArchive::getInstance()->printBestPhenotype();
	system("pause");
	return 0;
}