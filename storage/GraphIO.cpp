#include "GraphIO.h"

GraphIO::GraphIO(string fn, bool overwrite, bool bin)
{
	filename = fn;
	if (bin) {
		if (overwrite)
			file.open(fn, ios::in | ios::out | ios::binary | ios_base::trunc);
		else
			file.open(fn, ios::in | ios::out | ios::binary);
	}
	else {
		if (overwrite)
			file.open(fn, ios::in | ios::out | ios_base::trunc);
		else
			file.open(fn, ios::in | ios::out);
	}
}

GraphIO::~GraphIO()
{
	if (file) {
		file.close();
	}
}

void GraphIO::open(bool overwrite)
{
	if (file)
		close();
	if (overwrite)
		file.open(filename, ios::in | ios::out | ios::binary | ios_base::trunc);
	else 
		file.open(filename, ios::in | ios::out | ios::binary);
}

void GraphIO::close()
{
	file.clear();
	file.close();
}

bool GraphIO::isOpen()
{
	if (file)
		return true;
	else
		return false;
}