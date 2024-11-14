#include <QtCore>
#include <QtGui>
#include <QtLogging>
#include <QApplication>

#include "mainwindow.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow main;
    main.show();
    return app.exec();
}