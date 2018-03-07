#include <QApplication>
#include <QLineEdit>
#include <QValidator>
#include <QLayout>
#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include <QSpinBox>
#include <QRadioButton>

#include <algorithm>
#include <math.h>
#include <string>
#include <iostream>

#include "element.hpp"
#include "table.hpp"

Table::Table(QWidget *parent): QWidget(parent)
{
    m_optionsWidget = new Options();
    m_tableWidget = nullptr;
    m_optionsWidget->show();
    m_set = nullptr;
    m_cardinality = 0;
    m_occurrenceNo = 0;
    connect(m_optionsWidget->acceptButton, SIGNAL(clicked()), this, SLOT(setCardinality()));
    connect(m_optionsWidget->acceptButton, SIGNAL(clicked()), this, SLOT(setOccurrenceNo()));
    connect(m_optionsWidget->acceptButton, SIGNAL(clicked()), this, SLOT(makeSet()));
    connect(m_optionsWidget->acceptButton, SIGNAL(clicked()), m_optionsWidget, SLOT(close()));
    connect(m_optionsWidget->acceptButton, SIGNAL(clicked()), this, SLOT(makeTable()));
    connect(m_optionsWidget->acceptButton, SIGNAL(clicked()), m_tableWidget, SLOT(show()));
}

void Table::makeSet()
{
    if ((m_cardinality!=0))
    {
        size_t size = static_cast<int>(pow(2, m_cardinality));

        m_set = new MultisetElement[size];
        grayCodeGeneration(m_cardinality, m_set, 0, m_occurrenceNo);
        std::sort(m_set, m_set + size);

        m_setA = new int[size];
        m_setB = new int[size];
        m_result = new int[size];

        for (size_t i = 0; i < size; ++i)
        {
            m_setA[i] = 0;
            m_setB[i] = 0;
            m_result[i] = 0;
        }
    }
}

void Table::makeTable()
{
    size_t size = static_cast<size_t>(pow(2, m_cardinality));
    m_tableWidget = new TableWidget(size);
    m_tableWidget->show();

    if (size != 1)
    {
        // Universum
        for (size_t i = 0; i < size; ++i)
        {
            char p[m_cardinality + 1];
            int z = 0;
            for (int j = m_cardinality - 1; j >= 0; j--)
            {
                char a;
                itoa(m_set[i][j], &a, 10);
                p[z] = a;
                z++;
            }
            m_tableWidget->m_table->setItem(i, 0, new QTableWidgetItem(p));
        }
        // Occurence
        for (size_t i = 0; i < size; ++i)
        {
            char p[m_cardinality + 1];
            itoa(m_set[i].getOccurrenceNo(), p, 10);
            m_tableWidget->m_table->setItem(i, 1, new QTableWidgetItem(p));
        }
        // SetA
        for (size_t i = 0; i < size; ++i)
        {
            QSpinBox *box = new QSpinBox(m_tableWidget->m_table);
            box->setRange(0, m_occurrenceNo);
            m_tableWidget->m_table->setCellWidget(i, 2, box);
        }
        // SetB
        for (size_t i = 0; i < size; ++i)
        {
            QSpinBox *box = new QSpinBox(m_tableWidget->m_table);
            box->setRange(0, m_occurrenceNo);
            m_tableWidget->m_table->setCellWidget(i, 3, box);
        }
    }
    else
    {
        //Universum
        char p[m_cardinality];
        p[0]='\0';

        m_tableWidget->m_table->setItem(0, 0, new QTableWidgetItem(p));
        m_tableWidget->m_table->setItem(0, 1, new QTableWidgetItem(p));
        QSpinBox *box = new QSpinBox(m_tableWidget->m_table);
        box->setRange(0, 0);
        m_tableWidget->m_table->setCellWidget(0, 2, box);
        QSpinBox *box2 = new QSpinBox(m_tableWidget->m_table);
        box2->setRange(0, 0);
        m_tableWidget->m_table->setCellWidget(0, 3, box2);
    }

    QGridLayout *grid = new QGridLayout(m_tableWidget);
    grid->addWidget(m_tableWidget->m_table, 0, 0);
    grid->addWidget(createOperationGroup(), 0, 1);
    m_tableWidget->setLayout(grid);
}

QGroupBox *Table::createOperationGroup()
{
      setResult();

      m_operations = new QGroupBox(tr("Operation:"), m_tableWidget->m_table);
      m_operations->setFont(QFont("Arial", 10));

      QRadioButton *radio1 = new QRadioButton(tr("A \u222A B"),m_operations); // union
      QRadioButton *radio2 = new QRadioButton(tr("A \u228E B"), m_operations); // multiset union
      QRadioButton *radio3 = new QRadioButton(tr("A \u2229 B"), m_operations);
      QRadioButton *radio4 = new QRadioButton(tr("A \\ B"), m_operations); // intersection
      QRadioButton *radio5 = new QRadioButton(tr("B \\ A"), m_operations);
      QRadioButton *radio6 = new QRadioButton(tr("A'"), m_operations);
      QRadioButton *radio7 = new QRadioButton(tr("B'"), m_operations);
      QRadioButton *radio8 = new QRadioButton(tr("A \u2206 B"), m_operations); // symmetric difference

      QPushButton *randomButton = new QPushButton("Make Sets", m_operations);
      randomButton->setFont(QFont("Arial", 10));
      randomButton->setFixedWidth(200);

      QPushButton *computeButton = new QPushButton("Compute", m_operations);
      computeButton->setFont(QFont("Arial", 10));
      computeButton->setFixedWidth(200);

      QPushButton *resetButton = new QPushButton("Reset", m_operations);
      resetButton->setFont(QFont("Arial", 10));
      resetButton->setFixedWidth(200);

      if (m_cardinality != 0)
      {
          connect(resetButton, SIGNAL(clicked(bool)), this, SLOT(resetSet()));
          connect(randomButton, SIGNAL(clicked(bool)), this, SLOT(randomSet()));
          connect(randomButton, SIGNAL(clicked(bool)), this, SLOT(makeSetA()));
          connect(randomButton, SIGNAL(clicked(bool)), this, SLOT(makeSetB()));
          connect(computeButton, SIGNAL(clicked(bool)), this, SLOT(makeSetA()));
          connect(computeButton, SIGNAL(clicked(bool)), this, SLOT(makeSetB()));
          connect(radio1, SIGNAL(clicked(bool)), this, SLOT(union_()));
          connect(radio2, SIGNAL(clicked(bool)), this, SLOT(sum()));
          connect(radio3, SIGNAL(clicked(bool)), this, SLOT(intersection()));
          connect(radio4, SIGNAL(clicked(bool)), this, SLOT(differenceAB()));
          connect(radio5, SIGNAL(clicked(bool)), this, SLOT(differenceBA()));
          connect(radio6, SIGNAL(clicked(bool)), this, SLOT(notA()));
          connect(radio7, SIGNAL(clicked(bool)), this, SLOT(notB()));
          connect(radio8, SIGNAL(clicked(bool)), this, SLOT(symmetricDifference()));

          connect(computeButton, SIGNAL(clicked(bool)), this, SLOT(setResult()));
      }

      QVBoxLayout *box = new QVBoxLayout(m_operations);
      box->addWidget(radio1);
      box->addWidget(radio2);
      box->addWidget(radio3);
      box->addWidget(radio4);
      box->addWidget(radio5);
      box->addWidget(radio6);
      box->addWidget(radio7);
      box->addWidget(radio8);
      box->addWidget(computeButton);
      box->addWidget(randomButton);
      box->addWidget(resetButton);
      box->addStretch(1);
      m_operations->setLayout(box);

      return m_operations;
}

void Table::randomSet()
{
    size_t size = static_cast<size_t>(pow(2, m_cardinality));

    //SetA
    for (size_t i = 0; i < size; ++i)
    {
        QSpinBox *box = static_cast<QSpinBox *>(m_tableWidget->m_table->cellWidget(i, 2));
        box->setValue(rand() % (m_occurrenceNo + 1));
    }

    //SetB
    for (size_t i = 0; i < size; ++i)
    {
        QSpinBox *box = static_cast<QSpinBox *>(m_tableWidget->m_table->cellWidget(i, 3));
        box->setValue(rand() % (m_occurrenceNo + 1));
    }
}

void Table::resetSet()
{
    size_t size = static_cast<size_t>(pow(2, m_cardinality));

    //SetA
    for (size_t i = 0; i < size; ++i)
    {
        QSpinBox *box = static_cast<QSpinBox *>(m_tableWidget->m_table->cellWidget(i, 2));
        box->setValue(0);
    }

    //SetB
    for (size_t i = 0; i < size; ++i)
    {
        QSpinBox *box = static_cast<QSpinBox *>(m_tableWidget->m_table->cellWidget(i, 3));
        box->setValue(0);
    }
}

void Table::setResult()
{
    size_t size = static_cast<size_t>(pow(2, m_cardinality));

    for (size_t i = 0; i < size; ++i)
    {
        if (size == 1)
        {
            char p[m_cardinality];
            p[0]='\0';
            m_tableWidget->m_table->setItem(0, 4, new QTableWidgetItem(p));
            return;
        }

        char p[m_cardinality + 1];
        itoa(m_result[i], p, 10);
        m_tableWidget->m_table->setItem(i, 4, new QTableWidgetItem(p));
    }
}

void Table::makeSetA()
{
    size_t size = static_cast<size_t>(pow(2, m_cardinality));

    for (size_t i = 0; i < size; ++i)
    {
        QSpinBox *box = static_cast<QSpinBox *>(m_tableWidget->m_table->cellWidget(i, 2));
        m_setA[i] = box->value();
    }
}

void Table::makeSetB()
{
    size_t size = static_cast<size_t>(pow(2, m_cardinality));

    for (size_t i = 0; i < size; ++i)
    {
        QSpinBox *box = static_cast<QSpinBox *>(m_tableWidget->m_table->cellWidget(i, 3));
        m_setB[i] = box->value();
    }
}

void Table::intersection()
{
    size_t size = static_cast<size_t>(pow(2, m_cardinality));

    for (size_t i = 0; i < size; ++i)
    {
        m_result[i] = std::min(m_setA[i], m_setB[i]);
    }
}

void Table::union_()
{
    size_t size = static_cast<size_t>(pow(2, m_cardinality));

    for (size_t i = 0; i < size; ++i)
    {
        m_result[i] = std::max(m_setA[i], m_setB[i]);
    }
}

void Table::sum()
{
    size_t size = static_cast<size_t>(pow(2, m_cardinality));

    for (size_t i = 0; i < size; ++i)
    {
        int N = m_setA[i] + m_setB[i];
        m_result[i] = (N < m_occurrenceNo)? N : m_occurrenceNo;
    }
}

void Table::differenceAB(){
    size_t size = static_cast<size_t>(pow(2, m_cardinality));

    for (size_t i = 0; i < size; ++i)
    {
        m_result[i] = (m_setA[i] - m_setB[i]) > 0 ? m_setA[i] - m_setB[i] : 0;
    }
}

void Table::differenceBA()
{
    size_t size = static_cast<size_t>(pow(2, m_cardinality));

    for (size_t i = 0; i < size; ++i)
    {
        m_result[i] = (m_setB[i] - m_setA[i]) > 0 ? abs(m_setB[i] - m_setA[i]) : 0;
    }

}

void Table::notA()
{
    size_t size = static_cast<size_t>(pow(2, m_cardinality));

    for (size_t i = 0; i < size; ++i)
    {
        m_result[i] = m_occurrenceNo - m_setA[i];
    }
}

void Table::notB()
{
    size_t size = static_cast<size_t>(pow(2, m_cardinality));

    for (size_t i = 0; i < size; ++i)
    {
        m_result[i] = m_occurrenceNo - m_setB[i];
    }
}

void Table::symmetricDifference()
{
    size_t size = static_cast<size_t>(pow(2, m_cardinality));

    for (size_t i = 0; i < size; ++i)
    {
        m_result[i] = abs(m_setA[i] - m_setB[i]);
    }
}

void Table::setCardinality()
{
    m_cardinality = m_optionsWidget->cardinalityEdit->text().toInt();
}

void Table::setOccurrenceNo()
{
    m_occurrenceNo = m_optionsWidget->occurrenceEdit->text().toInt();
}

Table::~Table()
{
    delete [] m_set;
    delete [] m_setA;
    delete [] m_setB;
    delete [] m_result;
    delete m_tableWidget;
    delete m_optionsWidget;
}
