#include "UnionFindBase.h"
#include <iostream>

using namespace std;

UnionFindBase::UnionFindBase(int N)
{
	m_count = N;
	m_idArray = new int[m_count];
	for (int i = 0; i < m_count; ++i)
	{
		m_idArray[i] = i;
	}
}

UnionFindBase::~UnionFindBase()
{
    delete[] m_idArray;
}

void UnionFindBase::reset()
{
    for (int i = 0; i < m_count; ++i)
    {
        m_idArray[i] = i;
    }
}

int UnionFindBase::count()
{
	return m_count;
}

void UnionFindBase::printArray(int* array, int size, bool visible)
{
	if (visible)
	{
		string header = "", ids = "";

		header.append("Header |");
		ids.append("Value  |");
		for (int i = 0; i < size; ++i)
		{
			header.append(to_string(i) + "|");
			ids.append(to_string(array[i]) + "|");
		}

		cout << header << endl << ids << endl << endl;
	}
}

