#pragma once
#include "UnionFindBase.h"

class QuickFind : public UnionFindBase
{
public:
	QuickFind(int N);

	void connect(int p, int q);
	bool isConnected(int p, int q);
};

