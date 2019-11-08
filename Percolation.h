#ifndef PERCOLATION_H
#define PERCOLATION_H

#include <QObject>
#include "Union-Find/UnionFindBase.h"

class Percolation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int sitesNumber READ getSitesNumber NOTIFY sitesNumberChanged)
    //add model

public:
    explicit Percolation(int siteNumber, QObject *parent = nullptr);
    ~Percolation();

    Q_INVOKABLE void openSite(int id);

    int getSitesNumber() const
    {
        return m_sitesNumber;
    }

signals:
    void sitesNumberChanged(int sitesNumber);

private:
    void checkNeighborhood(int id);
    void checkFlow();
    void reset();

    UnionFindBase* m_unionFind;
    int m_sitesNumber;
    int* m_model;
    int m_opened;
    int m_blocked;
};

#endif // PERCOLATION_H
