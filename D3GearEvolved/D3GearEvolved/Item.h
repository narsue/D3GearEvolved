#pragma once
#include "UserInput.h"
enum WEAPON_TYPE
{
	WT_BOWS,
	WT_2HBOW,
	WT_1HXBOW,
	WT_2HXBOW,
	WT_MELEE_WEAPONS,
	WT_1H_MELEE,
	WT_2H_MELEE,
	WT_WAND,
	WT_NA
};

enum ITEM_TYPE
{
	IT_HELM,
	IT_SHOULDER,
	IT_AMULET,
	IT_CHEST,
	IT_GLOVES,
	IT_BRACERS,
	IT_BELT,
	IT_RING,
	IT_RING2,
	IT_PANTS,
	IT_BOOTS,

	IT_WEAPON,
	IT_OFFHAND,
	IT_OFFHAND_QUIVER,
	IT_NA
} ;
enum SUB_TYPE
{
	ST_SHIELD,
	ST_MONK,
	ST_MONK_HELM,
	ST_MONK_FIST_WEAPON,
	ST_DEMON_HUNTER,
	ST_QUIVER,
	ST_WIZARD,
	ST_BARBARIAN,
	ST_WITCH_DOCTOR,
	ST_NA
};
enum ITEM_SET
{
	IS_SAGES_WISDOM,
	IS_NA,
};
class Item
{
	private:
		//D3 stats
		ITEM_TYPE	itemType;
		SUB_TYPE	subType;
		ITEM_SET	itemSet;
		int		dexterity;
		int		intelligence;
		int		strength;
		int		vitality;
		float	critChance;
		int		critDamage;
		int		resisAll;
		int		poisonResist,fireResis,coldResis,arcaneResis,physicalResis,lightningResis;
		int		lifeOnHit,lifeOnKill;
		float	lifeSteal;
		int		armour;
		int		goldCost;
		float	attackSpeed;
		int		moveSpeed;
		char	name[255];
		int		lifePerSecond;
		int		magicFind;
		int		goldFind;
		int		pickupRadius;
		int		minDamage;
		int		maxDamage;
		int		socket;
		char	type;
		float	hatredRegen;
		int		meleeHit;
		int		life;
		int		minBlock,maxBlock,blockChance;
		bool	indestructible;
		int		healthGlobes;
		int		meleeReduce;
		float	spiritRegen;
		char * getNameForItemType()
		{
			if (IT_HELM == itemType)
				return "Helm";
			if (IT_SHOULDER == itemType)
				return "Shoulder";
			if (IT_AMULET == itemType)
				return "Amulet";
			if (IT_CHEST == itemType)
				return "Chest";
			if (IT_GLOVES == itemType)
				return "Gloves";
			if (IT_BRACERS == itemType)
				return "Bracers";
			if (IT_BELT == itemType)
				return "Belt";
			if (IT_RING == itemType)
				return "Ring";
			if (IT_PANTS == itemType)
				return "Pants";
			if (IT_BOOTS == itemType)
				return "Boots";
			if (IT_WEAPON == itemType)
				return "Weapon";
			if (IT_OFFHAND == itemType)
				return "Offhand";
			if (IT_OFFHAND_QUIVER == itemType)
				return "Offhand Quiver";
			return "Unknown Type";
		}

		ITEM_TYPE getItemTypeName(char * name)
		{
			if (strcmp(name,"IT_HELM")==0)
				return IT_HELM;
			if (strcmp(name,"IT_SHOULDER")==0)
				return IT_SHOULDER;
			if (strcmp(name,"IT_AMULET")==0)
				return IT_AMULET;
			if (strcmp(name,"IT_CHEST")==0)
				return IT_CHEST;
			if (strcmp(name,"IT_GLOVES")==0)
				return IT_GLOVES;
			if (strcmp(name,"IT_BRACERS")==0)
				return IT_BRACERS;
			if (strcmp(name,"IT_BELT")==0)
				return IT_BELT;
			if (strcmp(name,"IT_RING")==0)
				return IT_RING;
			if (strcmp(name,"IT_RING2")==0)
				return IT_RING2;
			if (strcmp(name,"IT_PANTS")==0)
				return IT_PANTS;
			if (strcmp(name,"IT_BOOTS")==0)
				return IT_BOOTS;
			if (strcmp(name,"IT_WEAPON")==0)
				return IT_WEAPON;
			if (strcmp(name,"IT_OFFHAND")==0)
				return IT_OFFHAND;
			if (strcmp(name,"IT_OFFHAND_QUIVER")==0)
				return IT_OFFHAND_QUIVER;
			return IT_NA;
		}
		SUB_TYPE getItemSubTypeName(char * name)
		{
			if (strcmp(name,"ST_MONK_FIST_WEAPON")==0)
				return SUB_TYPE::ST_MONK_FIST_WEAPON;
			if (strcmp(name,"ST_QUIVER")==0)
				return SUB_TYPE::ST_QUIVER;
			if (strcmp(name,"ST_SHIELD")==0)
				return SUB_TYPE::ST_SHIELD;
			return ST_NA;
		}
		void init()
		{
				itemType	=	IT_NA;
				dexterity	=	0;
				intelligence=	0;
				strength	=	0;
				vitality	=	0;
				critChance	=	0;
				critDamage	=	0;
				resisAll	=	0;
				lifeOnHit	=	0;
				lifeSteal	=	0;
				armour		=	0;
				goldCost	=	0;
				attackSpeed	=	0;
				moveSpeed	=	0;
				poisonResist=	0;
				lifePerSecond=	0;
				magicFind	=	0;
				goldFind	=	0;
				pickupRadius=	0;
				minDamage	=	0;
				maxDamage	=	0;
				socket		=	0;
				type		=	0;
				hatredRegen	=	0;
				life		=	0;
				meleeHit	=	0;
				lifeOnKill	=	0;
				meleeReduce	=	0;
				spiritRegen =	0;
				itemSet		=	IS_NA;
				poisonResist=fireResis=coldResis=arcaneResis=physicalResis=lightningResis=0;
				indestructible= false;
				minBlock=maxBlock=blockChance=0;
				subType = SUB_TYPE::ST_NA;

		}
		void readFileVal(FILE* fp, char* keyword,char* fileName)
		{
			if (strcmp(keyword,"strength")==0)
				fscanf(fp,"%d",&strength);
			else if (strcmp(keyword,"dexterity")==0)
				fscanf(fp,"%d",&dexterity);
			else if (strcmp(keyword,"vitality")==0)
				fscanf(fp,"%d",&vitality);
			else if (strcmp(keyword,"critChance")==0)
				fscanf(fp,"%f",&critChance);
			else if (strcmp(keyword,"critDamage")==0)
				fscanf(fp,"%d",&critDamage);
			else if (strcmp(keyword,"resisAll")==0)
				fscanf(fp,"%d",&resisAll);
			else if (strcmp(keyword,"allResis")==0)
				fscanf(fp,"%d",&resisAll);
			else if (strcmp(keyword,"lifeOnHit")==0)
				fscanf(fp,"%d",&lifeOnHit);
			else if (strcmp(keyword,"lifeSteal")==0)
				fscanf(fp,"%d",&lifeSteal);
			else if (strcmp(keyword,"armour")==0)
				fscanf(fp,"%d",&armour);
			else if (strcmp(keyword,"cost")==0)
				fscanf(fp,"%d",&goldCost);
			else if (strcmp(keyword,"intelligence")==0)
				fscanf(fp,"%d",&intelligence);
			else if (strcmp(keyword,"poisonResis")==0 || strcmp(keyword,"poisonResist")==0)
				fscanf(fp,"%d",&poisonResist);
			else if (strcmp(keyword,"arcaneResis")==0 || strcmp(keyword,"arcaneResist")==0)
				fscanf(fp,"%d",&arcaneResis);
			else if (strcmp(keyword,"coldResis")==0 || strcmp(keyword,"coldResis")==0)
				fscanf(fp,"%d",&coldResis);
			else if (strcmp(keyword,"physicalResis")==0 || strcmp(keyword,"physicalResist")==0)
				fscanf(fp,"%d",&coldResis);
			else if (strcmp(keyword,"fireResis")==0 || strcmp(keyword,"fireResist")==0)
				fscanf(fp,"%d",&fireResis);
			else if (strcmp(keyword,"lightningResis")==0 || strcmp(keyword,"lightningResist")==0)
				fscanf(fp,"%d",&lightningResis);
			else if (strcmp(keyword,"meleeHit")==0)
				fscanf(fp,"%d",&meleeHit);
			else if (strcmp(keyword,"meleeReduce")==0)
				fscanf(fp,"%d",&meleeReduce);
			else if (strcmp(keyword,"spiritRegen")==0)
				fscanf(fp,"%f",&spiritRegen);
			
			else if (strcmp(keyword,"attackSpeed")==0)
				fscanf(fp,"%f",&attackSpeed);
			else if (strcmp(keyword,"moveSpeed")==0)
				fscanf(fp,"%d",&moveSpeed);
			else if (strcmp(keyword,"lifePerSecond")==0)
				fscanf(fp,"%d",&lifePerSecond);
			else if (strcmp(keyword,"lifePerSec")==0)
				fscanf(fp,"%d",&lifePerSecond);
			else if (strcmp(keyword,"magicFind")==0)
				fscanf(fp,"%d",&magicFind);
			else if (strcmp(keyword,"goldFind")==0)
				fscanf(fp,"%d",&goldFind);
			else if (strcmp(keyword,"pickupRadius")==0)
				fscanf(fp,"%d",&pickupRadius);
			else if (strcmp(keyword,"pickupRange")==0)
				fscanf(fp,"%d",&pickupRadius);
			else if (strcmp(keyword,"minDamage")==0)
				fscanf(fp,"%d",&minDamage);
			else if (strcmp(keyword,"maxDamage")==0)
				fscanf(fp,"%d",&maxDamage);
			else if (strcmp(keyword,"socket")==0)
				fscanf(fp,"%d",&socket);
			else if (strcmp(keyword,"life")==0)
				fscanf(fp,"%d",&life);
			else if (strcmp(keyword,"minBlock")==0)
				fscanf(fp,"%d",&minBlock);
			else if (strcmp(keyword,"maxBlock")==0)
				fscanf(fp,"%d",&maxBlock);
			else if (strcmp(keyword,"blockChance")==0)
				fscanf(fp,"%d",&blockChance);
			else if (strcmp(keyword,"lifeOnKill")==0 || strcmp(keyword,"lifeAfterKill")==0)
				fscanf(fp,"%d",&lifeOnKill);
			else if (strcmp(keyword,"indestructible")==0)
				indestructible=true;
			else if (strcmp(keyword,"healthGlobes")==0 || strcmp(keyword,"healthGlobe")==0)
				fscanf(fp,"%d",&healthGlobes);
			else if (strcmp(keyword,"set")==0)
			{
				char typeName[255];
				fscanf(fp,"%s",typeName);//process set info here
				
			}
			else if (strcmp(keyword,"ItemType")==0)
			{
				char typeName[255];
				fscanf(fp,"%s",typeName);
				itemType = getItemTypeName(typeName);
			}
			else if (strcmp(keyword,"SubType")==0)
			{
				char typeName[255];
				fscanf(fp,"%s",typeName);
				subType = getItemSubTypeName(typeName);
			}
			else if (strcmp(keyword,"hatredRegen")==0)
				fscanf(fp,"%f",&hatredRegen);
			else if (strcmp(keyword,"type")==0)
			{
				char temp[15];
				fscanf(fp,"%s",temp);
				type=temp[0]&0xDF;//Converts the letter to a capital
			}
			else if (strcmp(keyword,"name")==0)
				fscanf(fp,"%s",name);
			else
			{
				printf("Unrecognised element:%s in file: %s\n",keyword,fileName);
				system("pause");
				exit(0);
			}
		}
		void initSockets()
		{

			if (socket>0)
			{
				CLASS_TYPE ct = UserInput::getInstance()->getClassType();
				if (itemType==IT_WEAPON)
				{
					if (ct == CLASS_TYPE::CT_MONK || ct == CLASS_TYPE::CT_BARBARIAN)
						lifeOnHit+= 500;
					else
						critDamage+=socket*100;
				}
				else if (itemType==IT_HELM)
					life+=14;
				else
				{
					if (ct == CLASS_TYPE::CT_MONK || ct == CLASS_TYPE::CT_DEMON_HUNTER)
						dexterity+=42*socket;
					else if (ct == CLASS_TYPE::CT_WIZARD || ct == CLASS_TYPE::CT_WIZARD)
						intelligence+=42*socket;
					else if (ct == CLASS_TYPE::CT_BARBARIAN)
						strength+=42*socket;
				}
			}
		}
	public:
		Item()
		{
			itemType = IT_NA;
		}

		Item(char * fileName)
		{
			init();
			FILE* fp = fopen(fileName,"r");
			if (fp==0)
				printf("Failed to open file %s\n",fileName);
			else
			{
				while (!feof(fp))
				{
					char keyword[255];
					fscanf(fp,"%s",keyword);
					readFileVal(fp,keyword,fileName);
				}
			}
			initSockets();

			fclose(fp);
		}
		int getDex()
		{
			return dexterity;
		}
		int getInt()
		{
			return intelligence;
		}
		float getLife()
		{
			return life*0.01f;
		};
		int getStrength()
		{
			return strength;
		}
		
		int getMinDamage()
		{
			return minDamage;
		}
		int getMaxDamage()
		{
			return maxDamage;
		}
		float getAttackSpeed()
		{
			return attackSpeed;
		}
		int getCost()
		{
			return goldCost;
		}
		int getMinBlock()
		{
			return minBlock;
		}
		int getMaxBlock()
		{
			return maxBlock;
		}
		float getBlockChance()
		{
			return blockChance*0.01;
		}

		WEAPON_TYPE getType()
		{
			if (type == 'B')
				return WT_2HBOW;
			if (type == 'H')
				return WT_1HXBOW;
			if (type == 'X')
				return WT_2HXBOW;
			if (type == 'M')
				return WT_1H_MELEE;
			return WT_NA;
		}
		bool is2Handed()
		{
			if (getType()==WT_2HBOW|| getType()== WT_2HXBOW || getType() == WT_2H_MELEE )
				return true;
			return false;
		}
		ITEM_TYPE getItemType()
		{
			return itemType;
		}
		float getCritChance()
		{
			return critChance;
		}
		float getCritDamage()
		{
			return critDamage;
		}
		float getVitality()
		{
			return vitality;
		}
		float getArmour()
		{
			return armour;
		}
		float getResisAll()
		{
			return resisAll;
		}

		void printData()
		{

			printf("%s (%s)\n",getNameForItemType(),name);
			if (minDamage)
				printf("minDamage:%d ",minDamage);
			if (maxDamage)
				printf("maxDamage:%d ",maxDamage);
			if (strength)
				printf("Str:%d ",strength);
			if (dexterity)
				printf("Dex:%d ",dexterity);
			if (intelligence)
				printf("Int:%d ",intelligence);
			if (vitality)
				printf("Vit:%d ",vitality);
			if (resisAll)
				printf("resAll:%d ",resisAll);
			if (poisonResist)
				printf("poisonResist:%d ",poisonResist);
			if (arcaneResis)
				printf("arcaneResist:%d ",arcaneResis);
			if (coldResis)
				printf("coldResist:%d ",coldResis);
			if (physicalResis)
				printf("physicalResist:%d ",physicalResis);
			if (fireResis)
				printf("fireResist:%d ",fireResis);
			if (armour)
				printf("armour:%d ",armour);
			if (socket)
				printf("sockets:%d ",socket);
			if (attackSpeed)
				printf("attackSpeed:%4.1f ",attackSpeed);
			if (critChance)
				printf("critChance:%4.1f%% ",critChance);
			if (critDamage)
				printf("critDamage:%d%% ",critDamage);
			if (magicFind)
				printf("magicFind:%d%% ",magicFind);
			if (goldFind)
				printf("goldFind:%d%% ",goldFind);
			if (life)
				printf("life:%d%% ",life);
			if (lifeOnHit)
				printf("lifeOnHit:%d%% ",lifeOnHit);
			if (minBlock)
			{
				printf("Block C:%d%% (%d-%d) ",blockChance,minBlock,maxBlock);
			}

			if (goldCost)
			{
				printf("cost:%4.0fk ",goldCost*0.001);
			}
			printf("\n\n");
		}

		float getPoisonResis()
		{
			return poisonResist;
		}
		float getFireResis()
		{
			return fireResis;
		}
		float getArcaneResis()
		{
			return arcaneResis;
		}
		float getPhysicalResis()
		{
			return physicalResis;
		}
		float getColdResis()
		{
			return coldResis;
		}
		float getLightningResis()
		{
			return lightningResis;
		}
		float getMeleeReduce()
		{
			return meleeReduce;
		}
		
		float getLifeOnHit()
		{
			return lifeOnHit;
		}

		bool isLegalItem()
		{
			if (subType== ST_SHIELD)
				return true;
			if (subType != ST_NA) //check if the item is a class specific item like the fist weapon for the monk
				if (subType>ST_MONK && subType< ST_DEMON_HUNTER && UserInput::getInstance()->getClassType()== CLASS_TYPE::CT_MONK)
					return true;
				else if (subType>ST_DEMON_HUNTER && subType< ST_WIZARD && UserInput::getInstance()->getClassType()== CLASS_TYPE::CT_DEMON_HUNTER)
					return true;
				else if (subType>ST_WIZARD && subType< CT_BARBARIAN && UserInput::getInstance()->getClassType()== CLASS_TYPE::CT_WIZARD)
					return true;
				else if (subType>CT_BARBARIAN && subType< CT_WITCH_DOCTOR && UserInput::getInstance()->getClassType()== CLASS_TYPE::CT_BARBARIAN)
					return true;
				else if (subType>CT_WITCH_DOCTOR && subType< ST_NA && UserInput::getInstance()->getClassType()== CLASS_TYPE::CT_WITCH_DOCTOR)
					return true;
				else
					return false;
			
			//check if the item is a general type allowed like focus on all melee weapons for the monk
			if (UserInput::getInstance()->getClassType()== CT_MONK)
			{
				if (getType()!=WT_NA)
					if (getType()>WT_MELEE_WEAPONS&&getType()< WT_WAND)
						return true;
					else
						return false;
			}
			if (UserInput::getInstance()->getClassType()== CT_DEMON_HUNTER)
			{
				if (getType()!=WT_NA)
					if (getType()>WT_BOWS && getType()< WT_MELEE_WEAPONS)
						return true;
					else
						return false;
			}
			return true;
		}
};