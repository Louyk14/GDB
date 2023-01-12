#include "IDPool.h"

IDPool::IDPool(bool zs)
{
	idNum = 0;
	maxId = 0;
	zeroStart = zs;
}


bool IDPool::existId(int node)
{
	if (node > maxId || emptyIds.find(node) != emptyIds.end())
		return false;

	return true;
}

int IDPool::nextId()
{
	idNum++;
	if (emptyIds.empty())
	{
		createNew = true;
		maxId = idNum;

		if (zeroStart)
			return idNum - 1;
		else
			return idNum;
	}
	else
	{
		createNew = false;
		int r = *emptyIds.begin();
		emptyIds.erase(emptyIds.begin());
		
		return r;
	}
}

void IDPool::removeId(int id)
{
	emptyIds.insert(id);
	idNum--;
}

void IDPool::set(int mId)
{
	idNum = mId;
	maxId = mId;
}

void IDPool::set(int mId, vector<int>& existIds)
{
	idNum = existIds.size();
	maxId = mId;

	if (existIds[0] == 1)
		zeroStart = true;

	int s = 1;
	if (zeroStart)
		s = 0;

	for (; s <= maxId; ++s)
	{
		if (existIds[s] == 0)
		{
			emptyIds.insert(s);
			if (emptyIds.size() >=  maxId - idNum)
				break;
		}
	}
}


// IDPool Disk version
IDPoolDisk::IDPoolDisk(string sfile, bool overwrite, bool zs)
{
	idNum = 0;
	maxId = 0;
	zeroStart = zs;
	storefile = sfile;
	gIO = new GraphIO(storefile, overwrite);
	readFromFile(gIO->file, 0);
	// delete gIO;
	// gIO = new GraphIO(storefile, true);
}

IDPoolDisk::IDPoolDisk(IDPoolDisk* pool, string myfile) {
	idNum = pool->idNum;
	maxId = pool->maxId;
	zeroStart = pool->zeroStart;
	storefile = myfile;
	gIO = new GraphIO(storefile, true);
	emptyIds = pool->emptyIds;
	// readFromFile(gIO->file, 0);
}

IDPoolDisk::~IDPoolDisk() {
	delete gIO;
	gIO = new GraphIO(storefile, true);

	writeToFile(gIO->file, 0);

	if (gIO)
		delete gIO;
}

bool IDPoolDisk::existId(int node)
{
	if (node > maxId || emptyIds.find(node) != emptyIds.end())
		return false;

	return true;
}

int IDPoolDisk::nextId()
{
	idNum++;
	if (emptyIds.empty())
	{
		createNew = true;
		maxId = idNum;

		if (zeroStart)
			return idNum - 1;
		else
			return idNum;
	}
	else
	{
		createNew = false;
		int r = *emptyIds.begin();
		emptyIds.erase(emptyIds.begin());

		return r;
	}
}

void IDPoolDisk::removeId(int id)
{
	emptyIds.insert(id);
	idNum--;
}

void IDPoolDisk::set(int mId)
{
	idNum = mId;
	maxId = mId;
}

void IDPoolDisk::set(int mId, vector<int>& existIds)
{
	idNum = existIds.size();
	maxId = mId;

	if (existIds[0] == 1)
		zeroStart = true;

	int s = 1;
	if (zeroStart)
		s = 0;

	for (; s <= maxId; ++s)
	{
		if (existIds[s] == 0)
		{
			emptyIds.insert(s);
			if (emptyIds.size() >= maxId - idNum)
				break;
		}
	}
}