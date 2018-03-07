#pragma once

#include <QLineEdit>
#include <QWidget>
#include <QPushButton>

#include "element.hpp"

class Options : public QWidget
{
    Q_OBJECT

public:
    Options(QWidget *parent = 0);
    ~Options();
private slots:
    void acceptButtonStatus();
public:
    QLineEdit* cardinalityEdit;
    QLineEdit* occurrenceEdit;
    QPushButton *acceptButton;
};
