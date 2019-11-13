#pragma once
#include "UnionFindBase.h"

class WeightedQuickUnion : public UnionFindBase
{
public:
	WeightedQuickUnion(int N);

    void connect(int p, int q);
	bool isConnected(int p, int q);
    void reset();

private:
	int getRoot(int i);
	int* m_countArray;
};

