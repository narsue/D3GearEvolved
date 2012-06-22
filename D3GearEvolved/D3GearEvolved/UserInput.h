#pragma once
#include <iostream>
using namespace std;
enum CLASS_TYPE
{
	CT_MONK,
	CT_DEMON_HUNTER,
	CT_WIZARD,
	CT_BARBARIAN,
	CT_WITCH_DOCTOR,
	CT_UNKNOWN
};
class UserInput
{
	private:
		static UserInput * instance;
		CLASS_TYPE classType;
		bool archery,steadyAim,conviction,breathOfHeaven,blind,seizeTheInitative,oneWithEverything,mantraOfEvasion,mantraOfEvasionHardTarget,keenEye;
		UserInput()
		{
			classType = CT_UNKNOWN;
			archery=steadyAim=conviction=breathOfHeaven=blind= seizeTheInitative=oneWithEverything=mantraOfEvasionHardTarget=mantraOfEvasion=keenEye=false;
			FILE* fp = fopen("../User/char.txt","r");
			if (fp==0)
			{
				printf("Failed to open ../User/char.txt pleae create this file");
				system("pause");
				exit(0);
			}
			while (!feof(fp))
			{
				char tempRead[255];
				fscanf(fp,"%s",tempRead);
				readClass(fp,tempRead);
				readAttribute(fp,tempRead,"archery",archery);
				readAttribute(fp,tempRead,"steadyAim",steadyAim);
				readAttribute(fp,tempRead,"conviction",conviction);
				readAttribute(fp,tempRead,"breathOfHeaven",breathOfHeaven);
				readAttribute(fp,tempRead,"blind",blind);
				readAttribute(fp,tempRead,"seizeTheInitative",seizeTheInitative);
				readAttribute(fp,tempRead,"oneWithEverything",oneWithEverything);
				readAttribute(fp,tempRead,"mantraOfEvasionHardTarget",mantraOfEvasionHardTarget);	
				readAttribute(fp,tempRead,"mantraOfEvasion",mantraOfEvasion);	
				readAttribute(fp,tempRead,"keenEye",keenEye);	

				
				
			}

			if (classType==CLASS_TYPE::CT_UNKNOWN)
			{
				printf("Please insert a class into ../user/char.txt \n eg:class Monk\n");
				fclose(fp);

				system("pause");
				exit(0);
			}
			fclose(fp);

		}
		void readClass(FILE* fp,char * tempRead)
		{
			if (strcmp("class",tempRead)==0)
			{
				fscanf(fp,"%s",tempRead);
				char classT = tempRead[0]&0xDF;
				if (classT=='M')
					classType= CT_MONK;
				else if (classT=='D')
					classType= CT_DEMON_HUNTER;
				else if (classT=='W')
					classType= CT_WITCH_DOCTOR;
				else if (classT=='B')
					classType= CT_BARBARIAN;
				else if (classT=='W')
					classType= CT_WIZARD;
				else 
					classType = CLASS_TYPE::CT_UNKNOWN;
			}


		}
		void readAttribute(FILE* fp,char * tempRead,char* attributeName,bool & attribute)
		{
				if (strcmp(attributeName,tempRead)==0)
				{
					fscanf(fp,"%s",tempRead);
					if (tempRead[0]=='F'||tempRead[0]=='f')
						attribute=false;
					else
						attribute=true;
				}
		}
	public:
		static UserInput * getInstance()
		{
			if (instance==0)
				instance = new UserInput();
			return instance;
		}
		CLASS_TYPE getClassType()
		{
			return classType;
		}

		bool getArchery()
		{
			return archery;
		}
		bool getSteadyAim()
		{
			return steadyAim;
		}
		bool getConviction()
		{
			return conviction;
		}
		bool getBreathOfHeaven()
		{
			return breathOfHeaven;
		}
		bool getBlind()
		{
			return blind;
		}
		bool getSeizeTheInitative()
		{
			return seizeTheInitative;
		}
		bool getOneWithEverything()
		{
			return oneWithEverything;
		}
		bool getMantraOfEvasionHardTarget()
		{
			return mantraOfEvasionHardTarget;
		}
		bool getMantraOfEvasion()
		{
			return mantraOfEvasion;
		}
		bool getKeenEye()
		{
			return keenEye;
		}
};