#include <QDebug>
#include <math.h>

#include "Percolation.h"
#include "Union-Find/WeightedQuickUnion.h"

const int BLOCKED = 0;
const int OPENED = 1;

Percolation::Percolation(int siteNumber, QObject *parent) :
    QObject(parent),
    m_sitesNumber(siteNumber),
    m_opened(0),
    m_blocked(siteNumber)
{
    m_unionFind = new WeightedQuickUnion(siteNumber);
    m_model = new int[siteNumber];
    reset();
}

Percolation::~Percolation()
{
    delete m_unionFind;
    delete m_model;
}

void Percolation::openSite(int id)
{
    if (BLOCKED == m_model[id])
    {
        m_model[id] = OPENED;
        m_opened++;
        m_blocked--;
        checkNeighborhood(id);
        checkFlow();
    }
}

void Percolation::checkNeighborhood(int id)
{
    int inRow = sqrt(m_sitesNumber);
    int right = id + 1;
    int left = id - 1;
    int up = id - inRow;
    int down = id + inRow;

    if ((right >= 0) && (right < m_sitesNumber) && (m_model[right] == OPENED))
    {
        m_unionFind->connect(id, right);
    }
    if ((left >= 0) && (left < m_sitesNumber) && (m_model[left] == OPENED))
    {
        m_unionFind->connect(id, left);
    }
    if ((up >= 0) && (up < m_sitesNumber) && (m_model[up] == OPENED))
    {
        m_unionFind->connect(id, up);
    }
    if ((down >= 0) && (down < m_sitesNumber) && (m_model[down] == OPENED))
    {
        m_unionFind->connect(id, down);
    }
}

void Percolation::checkFlow()
{
    bool result = false;
    int columns = sqrt(m_sitesNumber);

    for (int i = 0; i < columns; ++i)
    {
        for (int j = (m_sitesNumber-columns); j < m_sitesNumber; ++j)
        {
            result =  m_unionFind->isConnected(i,j);
            if (result) break;
        }
        if (result) break;
    }
    qDebug() << "checkFlow" << result;
    if (result)
    {
        double threshold = ((double)m_opened/(double)m_sitesNumber);
        qDebug() << "percolation threshold is" << m_opened << "/" << m_sitesNumber << "=" << threshold;
    }
}

void Percolation::reset()
{
    m_opened = 0;
    m_blocked = m_sitesNumber;
    for (int i = 0; i < m_sitesNumber; ++i)
    {
        m_model[i] = BLOCKED;
    }
}
