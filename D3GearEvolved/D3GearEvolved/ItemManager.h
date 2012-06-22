#pragma once

#include <iostream>
#include <vector>
#include "Item.h"
#include "UserInput.h"

using namespace std;



class ItemManager
{
	private:
		vector<vector<Item>> items;
		vector<char *> filePaths;
		bool checkDirectory(char* directoryPath, int & replayNo, int replayId,char * fileName,char * retDirectoryPath);
		char * getItems (char * directory);
		void clearFileNames()
		{
			for (int i =0;i<filePaths.size();i++)
				delete [] filePaths[i];
			filePaths.clear();
		}
		vector<Item> equipedItems;

		void init()
		{

			getItems("../User/items/*");
			for (int i =0;i<IT_NA;i++)
			{
				items.push_back(vector<Item>());
				equipedItems.push_back(Item());
			}
			for (int i =0;i<filePaths.size();i++)
			{
				Item temp(filePaths[i]);
				bool itemLegal = temp.isLegalItem();
				if (temp.getType()!=WT_NA&& !temp.is2Handed() && itemLegal)
					items[IT_OFFHAND].push_back(temp);
				if (itemLegal)
				{
					if (equipedItems[temp.getItemType()].getItemType() == IT_NA)
						equipedItems[temp.getItemType()]=(temp);
					else if (equipedItems[temp.getItemType()].getItemType() == IT_RING)
						equipedItems[IT_RING2]=(temp);
					else if (equipedItems[temp.getItemType()].getItemType() == IT_WEAPON)
						equipedItems[IT_OFFHAND]=(temp);
					items[temp.getItemType()].push_back(temp);
				}
			}

			clearFileNames();
			getItems("../items/*");
			for (int i =0;i<filePaths.size();i++)
			{
				Item temp(filePaths[i]);
				bool itemLegal = temp.isLegalItem()&&temp.getCost()<2500000 ;
				if (temp.getType()!=WT_NA&& !temp.is2Handed() && itemLegal)
					items[IT_OFFHAND].push_back(temp);
				if (itemLegal)
					items[temp.getItemType()].push_back(temp);
			}
			for (int i =0;i<items.size();i++)
				if (i!= IT_RING2 && items[i].size()==0 && i!= IT_OFFHAND_QUIVER)
				{
					printf("No items listed for %s \n",getNameForItemType((ITEM_TYPE)i));
					system("pause");
					exit(0);
				}

			clearFileNames();
			/*items[IT_HELM].push_back(Item(IT_HELM,"../items/head1.txt"));
			items[IT_SHOULDER].push_back(Item(IT_SHOULDER,"../items/shoulder1.txt"));
			items[IT_AMULET].push_back(Item(IT_AMULET,"../items/amulet1.txt"));
			items[IT_CHEST].push_back(Item(IT_CHEST,"../items/chest1.txt"));
			items[IT_GLOVES].push_back(Item(IT_GLOVES,"../items/gloves1.txt"));
			items[IT_BRACERS].push_back(Item(IT_BRACERS,"../items/bracers1.txt"));
			items[IT_BELT].push_back(Item(IT_BELT,"../items/belt1.txt"));
			items[IT_RING].push_back(Item(IT_RING,"../items/ring1a.txt"));
			items[IT_RING].push_back(Item(IT_RING,"../items/ring1b.txt"));
			items[IT_PANTS].push_back(Item(IT_PANTS,"../items/pants1.txt"));
			items[IT_BOOTS].push_back(Item(IT_BOOTS,"../items/boots1.txt"));
			items[IT_OFFHAND_QUIVER].push_back(Item(IT_OFFHAND,"../items/offhand1.txt"));
			items[IT_OFFHAND].push_back(Item(IT_WEAPON,"../items/handxbow2.txt"));


			items[IT_WEAPON].push_back(Item(IT_WEAPON,"../items/bow1.txt"));
			items[IT_WEAPON].push_back(Item(IT_WEAPON,"../items/handxbow2.txt"));
			items[IT_WEAPON].push_back(Item(IT_WEAPON,"../items/bow3.txt"));*/

		}
		ItemManager()
		{
			init();
		}

		char * getNameForItemType(ITEM_TYPE itemType)
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

		static ItemManager * instance;

	public:
		static ItemManager* getInstance()
		{
			if (instance==0)
				instance = new ItemManager();
			return instance;
		}
		Item * getItem(int type,int id)
		{
			if (type ==IT_RING2)//only pick from the 1 ring list
				type=IT_RING;

			if ((int)type>=items.size())
				return 0;
			if (type ==IT_OFFHAND)//this allows us to make offhand and offhand_quiver act as a single list
				if (id>=items[(int)IT_OFFHAND].size())
					return &items[(int)IT_OFFHAND_QUIVER][id-items[(int)IT_OFFHAND].size()];
			
			if (id >=items[(int)type].size())
				return 0;
			return &items[(int)type][id];
		}
		int size(int type)
		{
			if (type ==IT_RING2)//only pick from the 1 ring list
				type=IT_RING;
			if (type>=items.size())
				return -1;
			if (type ==IT_OFFHAND)
				return items[(int)IT_OFFHAND].size()+items[(int)IT_OFFHAND_QUIVER].size();
			return items[(int)type].size();
		}
		Item * getEquippedItem(int type)
		{
			return &equipedItems[type];
		}
};