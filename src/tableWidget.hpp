#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QGroupBox>
#include <QLayout>

class TableWidget : public QWidget
{
    Q_OBJECT

public:
    TableWidget(int rows, QWidget *parent = 0);
    ~TableWidget();
public:
    QTableWidget *m_table;
};
