#include <QDebug>
#include <math.h>
#include <algorithm>

#include "Percolation.h"
#include "Union-Find/WeightedQuickUnion.h"
#include "Union-Find/QuickUnion.h"
#include "Union-Find/QuickFind.h"

const QString BLOCKED = "black";
const QString OPENED = "white";

Percolation::Percolation(int siteNumber, QObject *parent) :
    QObject(parent),
    m_sitesNumber(siteNumber),
    m_randomTable(),
    m_opened(0),
    m_finished(false),
    m_sum(0.0),
    m_count(0),
    m_qmlModel()
{
    m_unionFind = new QuickFind(siteNumber);
    //m_unionFind = new QuickUnion(siteNumber);
    //m_unionFind = new WeightedQuickUnion(siteNumber);
    reset();
}

Percolation::~Percolation()
{
    delete m_unionFind;
}

void Percolation::openNextRandomSite()
{
    int id = m_randomTable.back();
    if ((id >= 0) && (id < m_qmlModel.size()))
    {
        m_randomTable.pop_back();
        openSite(id);
    }
}

void Percolation::openSite(int id)
{
    if (m_finished)
    {
        reset();
    }
    else if (BLOCKED == m_qmlModel[id])
    {
        m_qmlModel[id] = OPENED;
        emit stateChange(id, OPENED);
        m_opened++;
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

    if ((right >= 0) && (right < m_sitesNumber) && (m_qmlModel[right] == OPENED))
    {
        m_unionFind->connect(id, right);
    }
    if ((left >= 0) && (left < m_sitesNumber) && (m_qmlModel[left] == OPENED))
    {
        m_unionFind->connect(id, left);
    }
    if ((up >= 0) && (up < m_sitesNumber) && (m_qmlModel[up] == OPENED))
    {
        m_unionFind->connect(id, up);
    }
    if ((down >= 0) && (down < m_sitesNumber) && (m_qmlModel[down] == OPENED))
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

    if (result)
    {
        double threshold = ((double)m_opened/(double)m_sitesNumber);
        m_sum += threshold;
        m_count++;
        double average = (m_sum/m_count);
        m_finished = true;
        qDebug() << "****************************************";
        qDebug() << "Percolation threshold is" << m_opened << "/" << m_sitesNumber << "=" << threshold;
        qDebug() << "Average from" << m_count << "is" << average << "(" << (average*m_sitesNumber) << ")";
    }
}

void Percolation::reset()
{
    m_randomTable.clear();
    m_qmlModel.clear();
    emit qmlModelChanged(m_qmlModel);
    for (int i = 0; i < m_sitesNumber; ++i)
    {
        m_qmlModel.push_back(BLOCKED);
        m_randomTable.push_back(i);
    }
    std::srand(time(0));
    std::random_shuffle(m_randomTable.begin(), m_randomTable.end());
    emit qmlModelChanged(m_qmlModel);
    m_unionFind->reset();
    m_opened = 0;
    m_finished = false;
    emit getFinishedChanged(m_finished);
}
