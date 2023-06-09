#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

//best == theta(1)
//worst == theta(n)
//average == theta(n)
BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->first();
}

//best == theta(1)
//worst == theta(n)
//average == theta(n)
void BagIterator::first()
{
	index = 0;
	while (index <= bag.capacity and bag.table[index].value == -111111)
		index++;
	frequency = 0;
}


//best == theta(1)
//worst == theta(n)
//average == theta(n)
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

//best == worst == average == theta(1)
bool BagIterator::valid() const
{
	return (index < bag.capacity);
}


//best == worst == average == theta(1)
TElem BagIterator::getCurrent() const
{
	if (!valid())
		throw exception("Invalid iterator");
	return bag.table[index].value;
}
