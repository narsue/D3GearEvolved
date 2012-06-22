#pragma once

#include "Phenotype.h"
#include <vector>
using namespace std;
class BehaviourArchive
{
	private:
		static BehaviourArchive* instance;
		vector<Phenotype> archive;
		Phenotype bestPheno;
		BehaviourArchive()
		{
		}
	public:
		static BehaviourArchive * getInstance()
		{
			if (instance ==0)
				instance = new BehaviourArchive();
			return instance;
		}
		void printCurrentEquipped()
		{
			Phenotype currentEquipped;
			currentEquipped.setCurrentlyEquipped();
			currentEquipped.printInfo();
		}
		void printBestPhenotype()
		{
			bestPheno.printInfo();

		}
		float addPhenotype(Phenotype * pheno)
		{
			/*float minDist=0;
			if (archive.size()==0)
				minDist = 9999999;
			else
				minDist = archive[0].behaviourDistance(pheno);
			for (int i =1;i<archive.size();i++)
			{
				minDist = minDist<archive[i].behaviourDistance(pheno)?minDist:archive[i].behaviourDistance(pheno);
			}
			if (minDist>0.03)
			{
				archive.push_back(*pheno);
			}*/
			if (bestPheno.fitness()<pheno->fitness())
				bestPheno=*pheno;
			return 0;
		}

};