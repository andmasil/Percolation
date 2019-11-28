#ifndef PERCOLATION_H
#define PERCOLATION_H

#include <QObject>
#include <vector>
#include "Union-Find/UnionFindBase.h"

class Percolation : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool finished READ getFinished NOTIFY getFinishedChanged)
    Q_PROPERTY(QStringList qmlModel READ getQmlModel NOTIFY qmlModelChanged)

public:
    explicit Percolation(int siteNumber, QObject *parent = nullptr);
    ~Percolation();

    bool getFinished() const {return m_finished;}
    QStringList getQmlModel() const{ return m_qmlModel;}
    Q_INVOKABLE void openNextRandomSite();

signals:
    void getFinishedChanged(bool finished);
    void qmlModelChanged(QStringList qmlModel);
    void stateChange(int id, QString color);

private:
    void openSite(int id);
    void checkNeighborhood(int id);
    void checkFlow();
    void reset();
    int getRandomId();
    bool sameRow(int id1, int id2, int inRow);

    UnionFindBase* m_unionFind;
    int m_sitesNumber;
    std::vector<int> m_randomTable;
    int m_opened;
    bool m_finished;
    double m_sum;
    int m_count;
    QStringList m_qmlModel;
};

#endif // PERCOLATION_H
