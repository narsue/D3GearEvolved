#include "ItemManager.h"

class Gene
{
	private:
	public:
		int		range;
		int		id;		
		Item*	item;
		Gene(int _id)
		{
			reset(_id);

		}

		void mutate()
		{
			int size = ItemManager::getInstance()->size(id);
			range= size>0?rand()%size:size;
			item=ItemManager::getInstance()->getItem(id,range);
		}
		void reset(int _id)
		{
			id = _id;
			int size = ItemManager::getInstance()->size(_id);
			range= size>0?rand()%size:size;
			item=ItemManager::getInstance()->getItem(_id,range);
		}
};