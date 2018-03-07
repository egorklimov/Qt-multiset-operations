#include "tableWidget.hpp"
#include "options.hpp"
#include "table.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Table T;
    return a.exec();
}

