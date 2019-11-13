#include "QuickUnion.h"
#include <iostream>

using namespace std;

const bool PRINT = false;

QuickUnion::QuickUnion(int N) : UnionFindBase(N)
{
	cout << "QuickUnion " << N << endl << endl;
}

void QuickUnion::connect(int p, int q)
{
	if (!isConnected(p, q))
	{
		int pRoot = getRoot(p);
		int qRoot = getRoot(q);

		if ((p < m_count) && (q < m_count))
		{
			m_idArray[pRoot] = m_idArray[qRoot];
		}
		printArray(m_idArray, m_count, PRINT);
	}
}

bool QuickUnion::isConnected(int p, int q)
{
	bool result = false;

	if ((p < m_count) && (q < m_count) && (getRoot(p) == getRoot(q)))
	{
		result = true;
	}
    return result;
}


int QuickUnion::getRoot(int i)
{
	while (m_idArray[i] != i)
	{
		i = m_idArray[i];
	}

	return i;
}

/* EXAMPLE
10
4 3
3 8
6 5
9 4
2 1
5 0
7 2
6 1
7 3

ID - 1 8 1 8 3 0 5 1 8 8
*/
