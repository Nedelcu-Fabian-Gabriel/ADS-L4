#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


void Bag::resize()
{
	Bag* newBag = new Bag{unsigned int (capacity * 2) };
	for (int i = 0; i < capacity; i++)
	{
		for (int j = 0; j < table[i].frequency; j++)
			newBag->add(table[i].value);
		//newBag->add(table[i]);
	}
	*this = (Bag&&)(*newBag);
}

Bag::Bag()
	:capacity{ 15 }, s{ 0 }, table {new Element[capacity]}
{
	for (int i = 0; i < capacity; i++)
		table[i].value = table[i].next = -111111;
}

Bag::Bag(unsigned int cap)
	:capacity{ cap }, s{ 0 }, table{ new Element[cap] }
{
	for (int i = 0; i < capacity; i++)
		table[i].value = table[i].frequency = table[i].next = -111111;
}

void Bag::add(TElem element)
{
	if (firstEmpty == capacity)
		resize();
	int index = h(element);
	if (table[index].value == -111111)
	{
		table[index].value = element;
		table[index].frequency = 1;
	}
	else if (table[index].value == element)
		table[index].frequency++;
	else
	{
		int current = index;
		while (table[current].next != -111111)
		{
			current = table[current].next;
			if (table[current].value == element)
			{
				table[current].frequency++;
				s++;
				return;
			}
		}
		table[firstEmpty].value = element;
		table[firstEmpty].frequency = 1;
		table[current].next = firstEmpty;
	}
	if (table[firstEmpty].value != -111111)
		for (firstEmpty; firstEmpty < capacity and table[firstEmpty].value != -111111; firstEmpty++);
	s++;
}

 //void Bag::add(Element element)
//{
//	if (firstEmpty == capacity)
//		resize();
//	s += element.frequency;
//	if (table[h(element.value)].value == -111111)
//	{
//		table[h(element.value)].value = element.value;
//		table[h(element.value)].frequency = element.frequency;
//	}
//	else if (table[h(element.value)].value == element.value)
//		table[h(element.value)].frequency++;
//	else
//	{
//		int i;
//		for (i = h(element.value); table[i].next != -111111; i = table[i].next)
//			if (table[table[i].next].value == element.value)
//			{
//				table[i].frequency += element.frequency;
//				break;
//			}
//		if (table[i].next == -111111)
//		{
//			table[firstEmpty].value = element.value;
//			table[firstEmpty].frequency = element.frequency;
//			table[i].next = firstEmpty;
//		}
//	}
//	if (table[firstEmpty].value != -111111)
//		for (firstEmpty; firstEmpty < capacity and table[firstEmpty].value != -111111; firstEmpty++);
//}


bool Bag::remove(TElem element)
{
	int i = h(element);
	int j = -111111;
	while (i != -111111 and table[i].value != element)
	{
		j = i;
		i = table[i].next;
	}
	if (i == -111111)
		return false;
	else
	{
		table[i].frequency--;
		if (table[i].frequency > 0)
		{
			s--;
			return true;
		}

		bool over = false;
		do
		{
			int p = table[i].next;
			int q = i;
			while (p != -111111 and h(table[p].value) != i)
			{
				q = p;
				p = table[p].next;
			}
			if (p == -111111)
				over = true;
			else
			{
				table[i].value = table[p].value;
				table[i].frequency = table[p].frequency;
				table[i].next = table[p].next;
				i = p;
				j = q;
			}
		} while (over == false);

		if (j == -111111)
		{
			int k = 0;
			while (k < capacity and table[k].next != i)
				k++;
			if (k < capacity)
				j = k;
		}
		if (j != -111111)
			table[j].next = table[i].next;
		table[i].value = table[i].frequency = table[i].next = -111111;
		if (i < firstEmpty)
			firstEmpty = i;
		s--;
		return true;
	}
}


bool Bag::search(TElem element) const
{
	for (int i = h(element); i != -111111; i = table[i].next)
		if (table[i].value == element)
			return true;
	return false;
}

int Bag::nrOccurrences(TElem element) const
{
	for (int i = h(element); i != -111111; i = table[i].next)
		if (table[i].value == element)
			return table[i].frequency;
	return 0;
}


int Bag::size() const
{
	return s;
}


bool Bag::isEmpty() const
{
	return (s == 0);
}

BagIterator Bag::iterator() const
{
	return BagIterator(*this);
}


Bag::~Bag()
{
	delete[] table;
}

Bag& Bag::operator=(Bag&& other) noexcept
{
	if (this != &other)
	{
		capacity = other.capacity; 
		s = other.s;
		table = other.table; other.table = nullptr;
		firstEmpty = other.firstEmpty;
	}
	return *this;
}

