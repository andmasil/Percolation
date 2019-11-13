#include "QuickFind.h"
#include <iostream>

using namespace std;

const bool PRINT = false;

QuickFind::QuickFind(int N) : UnionFindBase(N)
{
	cout << "QuickFindUF " << N << endl << endl;
}

void QuickFind::connect(int p, int q)
{
	if (!isConnected(p, q) && (p < m_count) && (q < m_count))
	{
		int pid = m_idArray[p];
		int qid = m_idArray[q];

		//change all entries whose ID is equal to the first ID to the second one
		for (int i = 0; i < m_count; ++i)
		{
			if (m_idArray[i] == pid)
			{
				m_idArray[i] = qid;
			}
		}
	}
	printArray(m_idArray, m_count, PRINT);
}

bool QuickFind::isConnected(int p, int q)
{
	bool result = false;

	if ((p < m_count) && (q < m_count) && (m_idArray[p] == m_idArray[q]))
	{
		result = true;
	}
    return result;
}

/* EXAMPLE
10
3 4
3 8
6 5
9 4
2 1
8 9
5 0
7 2
6 1

ID - 1 1 1 8 8 1 1 1 8 8
*/
