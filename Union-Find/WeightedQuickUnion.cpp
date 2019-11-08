#include "WeightedQuickUnion.h"
#include <iostream>

using namespace std;

const bool PRINT = false;

WeightedQuickUnion::WeightedQuickUnion(int N) : UnionFindBase(N)
{
	cout << "WeightedQuickUnion " << N << endl << endl;
	m_countArray = new int[N];
	for (int i = 0; i < N; ++i)
	{
		m_countArray[i] = 1;
	}
}

void WeightedQuickUnion::connect(int p, int q)
{
    //cout << "WeightedQuickUnion connect " << p << " - " << q << endl;

	if (!isConnected(p, q) && (p < m_count) && (q < m_count))
	{
		int pRoot = getRoot(p);
		int qRoot = getRoot(q);

		if (pRoot == qRoot) return;

		if (m_countArray[pRoot] < m_countArray[qRoot])
		{
			m_idArray[pRoot] = m_idArray[qRoot];
			m_countArray[qRoot] += m_countArray[pRoot];
		}
		else
		{
			m_idArray[qRoot] = m_idArray[pRoot];
			m_countArray[pRoot] += m_countArray[qRoot];
		}
		printArray(m_idArray, m_count, PRINT);
		printArray(m_countArray, m_count, PRINT);
	}
}

bool WeightedQuickUnion::isConnected(int p, int q)
{
	bool result = false;

	if ((p < m_count) && (q < m_count) && (getRoot(p) == getRoot(q)))
	{
		result = true;
	}

    //cout << "WeightedQuickUnion isConnected (" << p << " - " << q << ") = " << boolalpha << result << endl;
	return result;
}

int WeightedQuickUnion::getRoot(int i)
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

ID - 6 2 6 4 6 6 6 2 4 4
*/

/* EXAMPLE
10
3 4
4 9
8 0
2 3
5 6
5 9
7 3
4 8
6 1

ID - 8 3 3 3 3 3 5 3 3 3
*/
