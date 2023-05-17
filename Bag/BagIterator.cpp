#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->first();
}

void BagIterator::first()
{
	index = 0;
	while (index <= bag.capacity and bag.table[index].value == -111111)
		index++;
	frequency = 0;
}


void BagIterator::next()
{
	if (!valid())
		throw exception("Invalid iterator");
	frequency++;
	if (frequency == bag.table[index].frequency)
	{
		index++;
		while (index <= bag.capacity and bag.table[index].value == -111111)
			index++;
		frequency = 0;
	}
}


bool BagIterator::valid() const
{
	return (index < bag.capacity);
}



TElem BagIterator::getCurrent() const
{
	if (!valid())
		throw exception("Invalid iterator");
	return bag.table[index].value;
}
