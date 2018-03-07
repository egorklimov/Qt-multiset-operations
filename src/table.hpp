#pragma once

#include <QWidget>

#include "element.hpp"
#include "options.hpp"
#include "tableWidget.hpp"

class Table : public QWidget
{
    Q_OBJECT

public:
    Table(QWidget *parent = 0);
    ~Table();
private slots:
    void makeSet();
    void makeTable();

    void makeSetA();
    void makeSetB();
    void setResult();

    void intersection();
    void union_();
    void sum();
    void differenceAB();
    void differenceBA();
    void notA();
    void notB();
    void symmetricDifference();

    void resetSet();
    void randomSet();

    void setCardinality();
    void setOccurrenceNo();
private:
    QGroupBox *m_operations;
    QGroupBox *createOperationGroup();
    int *m_setA;
    int *m_setB;
    int *m_result;
    int m_cardinality;
    int m_occurrenceNo;
    MultisetElement *m_set;
    Options *m_optionsWidget;
    TableWidget *m_tableWidget;
};
