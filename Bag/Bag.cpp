#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

//best == theta(n)
//worst == theta(n^2)
//average == theta(n) under SUH
void Bag::resize()
{
	Bag* newBag = new Bag{unsigned int (capacity * 1.01 + 1) };
	for (int i = 0; i < capacity; i++)
		newBag->add(table[i]);
	*this = (Bag&&)(*newBag);
}

//best == worst == average == theta(n)
Bag::Bag()
	:capacity{ 17 }, s{ 0 }, table {new Element[capacity]}
{
	for (int i = 0; i < capacity; i++)
		table[i].value = table[i].next = -111111;
}

//best == worst == average == theta(n)
Bag::Bag(unsigned int cap)
	:capacity{ cap }, s{ 0 }, table{ new Element[cap] }
{
	for (int i = 0; i < capacity; i++)
		table[i].value = table[i].frequency = table[i].next = -111111;
}

//best == theta(1)
//worst == theta(n)
//average == theta(1) under SUH
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

//best == theta(1)
//worst == theta(n)
//average == theta(1) under SUH
void Bag::add(Element element)
{
	element.next = -111111;
	if (firstEmpty == capacity)
		resize();
	int index = h(element.value);
	if (table[index].value == -111111)
	{
		table[index] = element;
	}
	else
	{
		int current = index;
		while (table[current].next != -111111)
			current = table[current].next;
		table[firstEmpty] = element;
		table[current].next = firstEmpty;
	}
	if (table[firstEmpty].value != -111111)
		for (firstEmpty; firstEmpty < capacity and table[firstEmpty].value != -111111; firstEmpty++);
	s += element.frequency;
}

//best == theta(1)
//worst == theta(n)
//average == theta(1) under SUH
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


//best == theta(1)
//worst == theta(n)
//average == theta(1) under SUH
bool Bag::search(TElem element) const
{
	for (int i = h(element); i != -111111; i = table[i].next)
		if (table[i].value == element)
			return true;
	return false;
}

//best == theta(1)
//worst == theta(n)
//average == theta(1) under SUH
int Bag::nrOccurrences(TElem element) const
{
	for (int i = h(element); i != -111111; i = table[i].next)
		if (table[i].value == element)
			return table[i].frequency;
	return 0;
}

//best == worst == average == theta(1)
int Bag::size() const
{
	return s;
}

//best == worst == average == theta(1)
bool Bag::isEmpty() const
{
	return (s == 0);
}

//best == worst == average == theta(1)
BagIterator Bag::iterator() const
{
	return BagIterator(*this);
}

//best == worst == average == theta(1)
Bag::~Bag()
{
	delete[] table;
}

//best == worst == average == theta(1)
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

