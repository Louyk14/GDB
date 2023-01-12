#include "IdAlloter.h"


/*template<class ID_TYPE>
void IdAlloter::set(int n, vector<int>& existIds)
{
	n2oMapper = vector<int>(n + 1, 0);
	if (existIds[0] == 1)
		pool->zeroStart = true;
	
	int s = 1;
	if (pool->zeroStart)
		s = 0;
	
	pool->idNum = existIds.size();
	pool->maxId = n;

	for (; s <= n; ++s)
	{
		if (existIds[s] == 0)
		{
			n2oMapper[s] = -1;
			pool->emptyIds.insert(s);
			if (pool->emptyIds.size() >= pool->idNum)
				break;
		}
	}
}*/


/*template<class ID_TYPE>
bool IdAlloter::isOuterId(int id)
{
	if (n2oMapper[id] != -1 && n2oMapper[id] != 0)
		return true;
	return false;
}

template<class ID_TYPE>
bool IdAlloter::isInnerId(int id)
{
	return n2oMapper[id] == 0;
}*/
