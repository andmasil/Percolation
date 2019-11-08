#pragma once
class UnionFindBase
{
public:
	UnionFindBase(int N);
    virtual ~UnionFindBase();

    virtual void connect(int p, int q) = 0;
    virtual bool isConnected(int p, int q) = 0;

protected:
	int count();
	void printArray(int* array, int size, bool visible = true);
	int m_count;
	int* m_idArray;
};

