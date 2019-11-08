#pragma once
#include "UnionFindBase.h"

class QuickUnion : public UnionFindBase
{
public:
	QuickUnion(int N);

	void connect(int p, int q);
	bool isConnected(int p, int q);

private:
	int getRoot(int i);
};

