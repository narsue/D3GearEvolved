#pragma once
#include "ItemManager.h"

#include <vector>
using namespace std;

#include "Gene.h"
#define CROSS_OVER_PROB 20
#define MUTATION_PROB 10
#define NO_ELITES 6
#include "UserInput.h"
class Phenotype
{
	private:
		float dps,hitPoints,armour,resisAll,critChance,cost,critDamage,avgCrit,effectiveHealth,strength,dexterity,intelligence,vitality, modifiedAttackSpeed,lifeOnHit;
		int poisonResis,fireResis,arcaneResis,physicalResis,coldResis,lightningResis;
		void evaluate()
		{
			fit=0;
			dps=1;
			hitPoints=0;
			armour=0;
			resisAll=0;
			critChance=5;
			
			critDamage=50;
			modifiedAttackSpeed=1;
			avgCrit=0;
			cost=0;
			lifeOnHit=0;
			calcDPS();
			calcHealth();
			//fit = dps*0.0001;
			//fit = (effectiveHealth*0.000001 + dps*0.0001*1.8);
			fit = (min(effectiveHealth/7000000.0f,1.0f)*min(effectiveHealth/7000000.0f,1.0f)+min(dps/21000.0f,1.0f)*min (dps/21000.0f,1.0f))/2.0f ;
		}
		void calcDPS()
		{
			int totalDex =187;
			effectiveHealth= 1;
			CLASS_TYPE ct = UserInput::getInstance()->getClassType();

			for (unsigned int i =0;i<genes.size();i++)
				if (genes[i].item)
				{
					

					if (ct == CLASS_TYPE::CT_MONK || ct == CLASS_TYPE::CT_DEMON_HUNTER)
						totalDex +=genes[i].item->getDex();
					else if (ct == CLASS_TYPE::CT_WIZARD || ct == CLASS_TYPE::CT_WITCH_DOCTOR)
						totalDex +=genes[i].item->getInt();
					else if (ct == CLASS_TYPE::CT_BARBARIAN)
						totalDex +=genes[i].item->getStrength();

					cost+=genes[i].item->getCost();
				}

			dps					= 1;
			float minDamage		= 0;
			float maxDamage		= 0;
			critChance	= 5;
			critDamage	= 50;
			float attackSpeed	= 0;
			int	  weaponCount	= 0;
			for (unsigned int i =0;i<genes.size();i++)
				if (genes[i].item)
				{
					if (genes[i].item->getItemType()!=IT_WEAPON)
					{
						minDamage+=genes[i].item->getMinDamage();
						maxDamage+=genes[i].item->getMaxDamage();
					}
					else 
						weaponCount  ++;

				}

			if (weaponCount==1)
			{
				minDamage+=genes[IT_WEAPON].item->getMinDamage();
				maxDamage+=genes[IT_WEAPON].item->getMaxDamage();
			}else if (weaponCount==2)
			{
				minDamage+=(genes[IT_WEAPON].item->getMinDamage()+genes[IT_OFFHAND].item->getMinDamage())*0.5f;
				maxDamage+=(genes[IT_WEAPON].item->getMaxDamage()+genes[IT_OFFHAND].item->getMaxDamage())*0.5f;
			}
			minDamage=minDamage==0?1:minDamage;
			maxDamage=maxDamage==0?1:maxDamage;

			for (unsigned int i =0;i<genes.size();i++)
				if (genes[i].item)
				{
					if (genes[i].item->getItemType()!= IT_WEAPON)
					{
						attackSpeed+=genes[i].item->getAttackSpeed();
					}
					critChance+=genes[i].item->getCritChance();
					critDamage+=genes[i].item->getCritDamage();

				}
			modifiedAttackSpeed = 0;
			if (genes[IT_WEAPON].item)
			{
				Item* weapon = genes[IT_WEAPON].item;
				Item* offhandWeapon = genes[IT_OFFHAND].item;

				
				if (weaponCount==1)
					modifiedAttackSpeed=weapon->getAttackSpeed()*(1.0f+attackSpeed*0.01);
				else if (weaponCount==2)
					modifiedAttackSpeed=(weapon->getAttackSpeed()+offhandWeapon->getAttackSpeed())*0.5f*(1.0f+attackSpeed*0.01);
				dps=(minDamage+maxDamage)*0.5f;
				dps *=modifiedAttackSpeed;
			}
			dps *= (1+totalDex*0.01);
			if (genes[IT_WEAPON].item)
			{
				float modifier=1.0f;

				if (ct == CLASS_TYPE::CT_DEMON_HUNTER)
				{
					if (UserInput::getInstance()->getSteadyAim())
						modifier+=0.2;
					if (UserInput::getInstance()->getArchery())
						if (genes[IT_WEAPON].item->getType()==WT_2HBOW)
						{
							modifier+=0.15;
						}
						else if (genes[IT_WEAPON].item->getType()==WT_1HXBOW)
						{
							critChance+=10;
						}
						else if (genes[IT_WEAPON].item->getType()==WT_2HXBOW)
						{
							critDamage+=50;
						}
				}else if (ct == CLASS_TYPE::CT_MONK)
				{
					if (UserInput::getInstance()->getConviction())
						modifier+=0.24;
					if (UserInput::getInstance()->getBreathOfHeaven())
						modifier+=0.15;
					if (UserInput::getInstance()->getBlind())
						modifier+=0.3;
				}
				if (weaponCount==2)
					modifier+=0.15;
				dps*=modifier;
				avgCrit=(minDamage+maxDamage)*0.5f*(1+totalDex*0.01)*modifier*(critDamage*0.01f+1);

			}
			
			dps *= (critChance*0.01f*critDamage*0.01f+1);
		}
		void setMaxResis(int &maxResis,int &resisVal,int *resisType)
		{
			if (maxResis<resisVal)
			{
				maxResis=resisVal;
				resisType=&resisVal;
			}
		}
		void calcHealth()
		{
			float resis,life,blockAmountMin,blockAmountMax,blockChance;
			float charLevel = 60;
			float mobLevel = 60;
			vitality=127;//base vitality
			strength = 67;
			dexterity = 67;
			intelligence = 67;
			resis=life=lifeOnHit=0;
			blockAmountMin=blockAmountMax=blockChance=0;
			float baseReduction = .2;
			CLASS_TYPE ct = UserInput::getInstance()->getClassType();

			if (ct == CLASS_TYPE::CT_MONK || ct == CLASS_TYPE::CT_DEMON_HUNTER)
				dexterity=187;
			else if (ct == CLASS_TYPE::CT_WIZARD || ct == CLASS_TYPE::CT_WIZARD)
				intelligence =187;
			else if (ct == CLASS_TYPE::CT_BARBARIAN)
				strength =187;

			if (ct == CLASS_TYPE::CT_MONK || ct == CLASS_TYPE::CT_BARBARIAN)
				baseReduction=.3;

			poisonResis=fireResis=arcaneResis=physicalResis=coldResis=lightningResis=0;
			for (unsigned int i =0;i<genes.size();i++)
				if (genes[i].item)
				{
					vitality+=genes[i].item->getVitality();
					armour+=genes[i].item->getArmour();
					resis+=genes[i].item->getResisAll();
					strength+=genes[i].item->getStrength();
					dexterity+=genes[i].item->getDex();
					intelligence+=genes[i].item->getInt();
					life+= genes[i].item->getLife();
					blockChance+= genes[i].item->getBlockChance();
					blockAmountMax+= genes[i].item->getMaxBlock();
					blockAmountMin+= genes[i].item->getMinBlock();
					poisonResis+=genes[i].item->getPoisonResis();
					fireResis+=genes[i].item->getFireResis();
					arcaneResis+=genes[i].item->getArcaneResis();
					physicalResis+=genes[i].item->getPhysicalResis();
					coldResis+=genes[i].item->getColdResis();
					lightningResis+=genes[i].item->getLightningResis();
					lifeOnHit+=genes[i].item->getLifeOnHit();
				}


			resis+=intelligence/10.0f;
			hitPoints= ((charLevel-25)*vitality+276)*(1+life);
			armour+=strength;
			if (ct == CLASS_TYPE::CT_MONK)
			{
				armour+=UserInput::getInstance()->getSeizeTheInitative()?dexterity:0;//adds dexterity onto the armour
				if (UserInput::getInstance()->getOneWithEverything())
				{
					int maxResis=0;
					int *resisT= 0;
					setMaxResis(maxResis,poisonResis,resisT);
					setMaxResis(maxResis,fireResis,resisT);
					setMaxResis(maxResis,arcaneResis,resisT);
					setMaxResis(maxResis,physicalResis,resisT);
					setMaxResis(maxResis,coldResis,resisT);
					setMaxResis(maxResis,lightningResis,resisT);
					
					resis+=maxResis;

				}
			}
			float dodgeChance = calcDodgeChance(dexterity);

			if (ct == CLASS_TYPE::CT_MONK)
			{
				if (UserInput::getInstance()->getMantraOfEvasionHardTarget())
				{
					armour*=1.2;
					dodgeChance+= (1.0f-dodgeChance)*0.15;
					dodgeChance+= (1.0f-dodgeChance)*0.15;
				}
				if (UserInput::getInstance()->getMantraOfEvasion())
				{
					dodgeChance+= (1.0f-dodgeChance)*0.15;
					dodgeChance+= (1.0f-dodgeChance)*0.15;
				}
				if (UserInput::getInstance()->getKeenEye())
					armour*=1.5;
			}
			float armourAR = armour/(armour+50*mobLevel);
			float resisAR = resis/(resis+5*mobLevel);
			float dodgeAR = 1;
			float DR= hitPoints/((1-armourAR)*(1-resisAR)*baseReduction);
			float DRA= 1.0f/((1-armourAR)*(1-resisAR)*baseReduction);

			resisAll = resis;
			double dodgeIncreasedHealth =0;
			for (int i =0;i<1000;i++)
				dodgeIncreasedHealth+=simulateEncounter(DR,dodgeChance,blockChance,blockAmountMin*DRA,blockAmountMax*DRA,lifeOnHit*modifiedAttackSpeed*DRA);
			dodgeIncreasedHealth/=1000.0;
			float ratioIncrease = (dodgeIncreasedHealth+DR)/DR;
			effectiveHealth = dodgeIncreasedHealth+DR;
		}
		float simulateEncounter(float DR,float dodgeChance,float blockChance,float blockAmountMin,float blockAmountMax,int lifeOnHitI)
		{
			float hitDamage = 600000;
			float evadedHealth = 0;
			while (DR>0)
			{
				DR+=lifeOnHitI;
				evadedHealth+=lifeOnHitI;
				float roll =(rand()%10000)*0.0001;
				if (roll<dodgeChance)
					evadedHealth+=hitDamage;
				else
				{
					roll =(rand()%10000)*0.0001;
					if (roll<blockChance)
					{
						roll =(rand()%10000)*0.0001;
						float blockAmount= blockAmountMin+(blockAmountMax-blockAmountMin)*roll;
						DR-= hitDamage-blockAmount;
						evadedHealth+=blockAmount;

					}
					else
						DR-=hitDamage;

				}
			}
			return evadedHealth;
		}
		float calcDodgeChance(int dexterity)
		{
			if (dexterity>=0&&dexterity<=100)
				return dexterity*.001;
			if (dexterity>100&&dexterity<=500)
				return .1+(dexterity-100)*.00025;
			if (dexterity>500&&dexterity<=1000)
				return .2+(dexterity-500)*.00025;
			return .3+(dexterity-1000)*.0001;
		}
	public:
		vector<Gene> genes;
		float fit;
		Phenotype()
		{
			init();
			evaluate();
		}

		Phenotype(Phenotype &lhs,Phenotype &rhs)
		{

			unsigned int crossOverPoint = rand()%lhs.genes.size();
			unsigned int crossOverProb = rand()%100;

			if (crossOverProb>100-CROSS_OVER_PROB)
			{
				for (unsigned int i =0;i<lhs.genes.size();i++)
				{
					if (i<crossOverPoint)
						genes.push_back(lhs.genes[i]);
					else
						genes.push_back(rhs.genes[i]);
				}
			}
			else
			{
				Phenotype* best=0;
				if (lhs.fitness()>rhs.fitness())
					best=&lhs;
				else
					best = &rhs;
				for (unsigned int i =0;i<best->genes.size();i++)
					genes.push_back(best->genes[i]);
			}
			unsigned int mutationProb = rand()%100;
			unsigned int mutationPoint = rand()%lhs.genes.size();

			if (mutationProb>100-MUTATION_PROB)
			{
				genes[mutationPoint].mutate();
			}

			//In the case of mutations/crossover the main weapon can switch from a 2 handed weapon to a 1 handed and vise versa
			//We then have to reset the offhand gene to compensate for a legal slot
			if ( genes[IT_WEAPON].item->is2Handed() && genes[IT_OFFHAND].item->getType()!= IT_OFFHAND_QUIVER)
				genes[IT_OFFHAND].reset(IT_OFFHAND_QUIVER);
			else if (!genes[IT_WEAPON].item->is2Handed() && genes[IT_OFFHAND].item->getType()!= IT_OFFHAND)
				genes[IT_OFFHAND].reset(IT_OFFHAND);
			evaluate();

		}
		void init()
		{
			
			for (int i =0;i<13;i++)
			{
				int pushId=i;
				if (i==IT_OFFHAND && genes[(int)IT_WEAPON].item)
					if (genes[(int)IT_WEAPON].item->is2Handed())
						pushId=IT_OFFHAND_QUIVER;

				genes.push_back(Gene(pushId));

			}
		}
		float fitness()
		{	
			return fit;
		}
		float getArmour()
		{
			return armour;
		}
		float getDps()
		{
			return dps;
		}
		float getResistAll()
		{
			return resisAll;
		}
		float getHitPoints()
		{
			return hitPoints;
		}
		float behaviourDistance(Phenotype * lhs)
		{
			float dist = abs(getDps()-lhs->getDps())*0.0001;
			dist += abs(getArmour()-lhs->getArmour())*0.0001;
			dist += abs(getResistAll()-lhs->getResistAll())*0.001;
			dist += abs(getHitPoints()-lhs->getHitPoints())*0.001;
			return dist;
		}

		char *getClassName()
		{
			CLASS_TYPE ct = UserInput::getInstance()->getClassType();
			if (ct == CT_MONK)
				return "Monk";
			if (ct == CT_DEMON_HUNTER)
				return "Demon Hunter";
			if (ct == CT_WITCH_DOCTOR)
				return "Witch Doctor";
			if (ct == CT_BARBARIAN)
				return "Barbarian";
			if (ct == CT_WIZARD)
				return "Wizard";
		}
		void printInfo(bool printItems=true)
		{
			printf("\n\nClass: %s\n",getClassName());
			printf("Phenotype information Dps:%4.2f CC:%4.1f CD:%4.0f AvgCrit:%4.0f AS:%4.1f\n",getDps(),critChance,critDamage,avgCrit,modifiedAttackSpeed);
			printf("Str:%4.0f Dex:%4.0f Int:%4.0f Vit:%4.0f LOH:%4.0f LOH-PS:%4.0f\n",strength,dexterity,intelligence,vitality,lifeOnHit,lifeOnHit*modifiedAttackSpeed);
			printf("HitPoints:%4.0f Armour:%4.0f ResisAll:%4.0f effectiveHealth:%4.0f\n",getHitPoints(),getArmour(),getResistAll(),effectiveHealth);
			printf("Cost:%4.0f gold\n",cost);
			printf("--------------------------------------------------------------------------\n");
			if (printItems)
				for (int i =0;i<13;i++)
				{
					genes[i].item->printData();
				}
			printf("--------------------------------------------------------------------------\n");
		}
		void setCurrentlyEquipped()
		{
			for (int i =0;i<IT_OFFHAND_QUIVER;i++)
				genes[i].item= ItemManager::getInstance()->getEquippedItem(i);
			evaluate();
		}

};