#include <QApplication>
#include <QLineEdit>
#include <QValidator>
#include <QLayout>
#include <QPushButton>
#include <QDebug>
#include <QLabel>

#include "options.hpp"

Options::Options(QWidget *parent): QWidget(parent)
{
    setWindowTitle("Gray code");
    setFixedHeight(150);
    setFixedWidth(350);

    QLabel *cardinalityLabel = new QLabel("Cardinality:", this);
    cardinalityLabel->setFont(QFont("Arial", 14));
    cardinalityEdit = new QLineEdit(this);
    cardinalityEdit->setFont(QFont("Arial", 10));
    cardinalityEdit->setValidator(new QRegExpValidator( QRegExp( "[0-8]" ) ));

    QLabel *occurrenceLabel = new QLabel("Occurrence:", this);
    occurrenceEdit = new QLineEdit(this);
    occurrenceEdit->setValidator(new QRegExpValidator( QRegExp( "[0-9]|([1-9][0-9]{1,8})" ) ));
    occurrenceEdit->setFont(QFont("Arial", 10));
    occurrenceLabel->setFont(QFont("Arial", 14));

    acceptButton = new QPushButton("Accept", this);
    acceptButton->setFont(QFont("Arial", 12, QFont::Bold));

    acceptButton->show();

    if (occurrenceEdit->text() == "" && cardinalityEdit->text() == "")
    {
        acceptButton->setEnabled(false);
    }

    connect(occurrenceEdit, SIGNAL(textChanged(QString)), this, SLOT(acceptButtonStatus()));
    connect(cardinalityEdit, SIGNAL(textChanged(QString)), this, SLOT(acceptButtonStatus()));
    connect(occurrenceEdit, SIGNAL(textEdited(QString)), this, SLOT(acceptButtonStatus()));
    connect(cardinalityEdit, SIGNAL(textEdited(QString)), this, SLOT(acceptButtonStatus()));

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addWidget(cardinalityLabel, 0, 0);
    gridLayout->addWidget(cardinalityEdit, 0, 1);
    gridLayout->addWidget(occurrenceLabel, 1, 0);
    gridLayout->addWidget(occurrenceEdit, 1,1);
    gridLayout->addWidget(acceptButton, 2, 1);
    gridLayout->setColumnStretch(1, 10);
    setLayout(gridLayout);
}

void Options::acceptButtonStatus()
{
    if (occurrenceEdit->text() == "" || cardinalityEdit->text() == "")
    {
        acceptButton->setEnabled(false);
    }
    else
    {
        acceptButton->setEnabled(true);
    }
}

Options::~Options()
{
    delete cardinalityEdit;
    delete occurrenceEdit;
    delete acceptButton;
}
