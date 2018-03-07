#include "tableWidget.hpp"
#include <QApplication>
#include <QLineEdit>
#include <QValidator>
#include <QLayout>
#include <QPushButton>
#include <QDebug>
#include <QDesktopWidget>
#include <QLabel>
#include <QHeaderView>
#include <QTableWidget>
#include <QRadioButton>

TableWidget::TableWidget(int rows, QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Gray code");
    m_table = new QTableWidget(this);
    m_table->setColumnCount(5);
    m_table->setColumnWidth(1, 200);
    m_table->setRowCount(rows);

    QStringList m_TableHeader;
    m_TableHeader << "Universum" << "Occurrence in Universum" <<  "Set A" << "Set B" << "Result";
    m_table->setHorizontalHeaderLabels(m_TableHeader);

    m_table->verticalHeader()->setVisible(false);
    m_table->setShowGrid(false);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->setFixedHeight(800);
    m_table->setFixedWidth(m_table->columnWidth(0)*4 + 205);
}

TableWidget::~TableWidget()
{
    delete m_table;
}
