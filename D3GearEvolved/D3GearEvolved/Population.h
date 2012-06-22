#pragma once



#include "Phenotype.h"
#include "BehaviourArchive.h"
#include <vector>
using namespace std;
class Population
{
	private:
		vector<Phenotype> pop;
		void sortPop()
		{
			for (unsigned int i =0;i<pop.size();i++)
				for (unsigned int ii =i+1;ii<pop.size();ii++)
					if (pop[i].fitness()<pop[ii].fitness())
					{
						Phenotype temp= pop[i];
						pop[i]= pop[ii];
						pop[ii] = temp;
					}
		}
		int getParentId(float totalFitness,int lhsId)
		{
			float randPoint = rand()%((int)totalFitness);
			for (unsigned int i =0;i<pop.size();i++)
			{
				randPoint-=pop[i].fitness();
				if (randPoint<=0)
					if (lhsId==i)
						return getParentId(totalFitness,lhsId);
					else
						return i;
			}
			
		}
	public:
		Population(unsigned int size)
		{
			for (unsigned int i =0;i<size;i++)
			{
				pop.push_back(Phenotype());
				//pop[0].printInfo();
			}
		}
		float getHighestFitness()
		{
			float maxFitness=0;
			for (unsigned int i =0;i<pop.size();i++)
				maxFitness = maxFitness>pop[i].fitness()?maxFitness:pop[i].fitness();
			return maxFitness;
		}
		float getLowestFitness()
		{
			float minFitness=999999999;
			for (unsigned int i =0;i<pop.size();i++)
				minFitness = minFitness<pop[i].fitness()?minFitness:pop[i].fitness();
			return minFitness;
		}
		float getAverageFitness()
		{
			float avgFitness=0;
			for (unsigned int i =0;i<pop.size();i++)
				avgFitness +=pop[i].fitness();
			return avgFitness/(float)pop.size();
		}
		
		void update()
		{
			vector<Phenotype> pop2;
			sortPop();
			float totalFitness=0;
			for (unsigned int i =0;i<pop.size();i++)
			{
				totalFitness+= pop[i].fitness();
				BehaviourArchive::getInstance()->addPhenotype(&pop[i]);
				//printf(",%d",i);
			}

			
			for (unsigned int i =0;i<NO_ELITES;i++)
				pop2.push_back(Phenotype(pop[i]));


			for (unsigned int i =NO_ELITES;i<pop.size();i++)
			{
				int lhsId =getParentId(totalFitness,-1);
				int rhsId =getParentId(totalFitness,lhsId);

				
				pop2.push_back(Phenotype(pop[lhsId],pop[rhsId]));
			}
			pop=pop2;
		}
};