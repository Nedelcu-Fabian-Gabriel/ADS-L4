#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111;
typedef int TElem;
class BagIterator;

#include <iostream>
class Bag
{
	//DO NOT CHANGE THIS PART
	friend class BagIterator;

private:
	struct Element
	{
		TElem value;
		int frequency;
		int next;
	};
	unsigned int capacity, s; 
	Element* table;
	unsigned int firstEmpty = 0;

	unsigned int h(TElem elem) const
	{
		if (elem < 0)
			elem = -elem;
		return elem % capacity;
	}

	void resize();

public:
	//constructor
	Bag();
	Bag(unsigned int cap);

	//adds an element to the bag
	void add(TElem e);

	void add(Element element);

	//removes one occurrence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//destructor
	~Bag();

	Bag& operator=(Bag&& other) noexcept;

	friend std::ostream& operator<< (std::ostream& os, Bag& b)
	{
		for (int i = 0; i < b.capacity; i++)
			if (b.table[i].frequency != -111111)
				os << b.table[i].frequency << ' ';
			else os << '-' << ' ';
		os << '\n';
		for (int i = 0; i < b.capacity; i++)			
			if (b.table[i].value != -111111)
				os << b.table[i].value << ' ';			
			else os << '-' << ' ';
		os << '\n';
		for (int i = 0; i < b.capacity; i++)			
			if (b.table[i].next != -111111)
				os << b.table[i].next << ' ';			
			else os << '-' << ' ';
		os << '\n';
		return os;
	}
};