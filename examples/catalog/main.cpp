/*
 Embedded Widgets Demo
 Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).*
 Contact:  Qt Software Information (qt-info@nokia.com)**
 This file may be used under the terms of the Embedded Widgets Demo License
 Agreement.
*/

#include <QtGui>

#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    
    QFile f(":/catalog.css");
    if (f.open(QIODevice::ReadOnly)) {
        app.setStyleSheet(f.readAll());
        f.close();
    }
       
    for (int i = 0; i < argc; ++i) {
        if (QString(argv[i]) == QString("-h") ||
            QString(argv[i]) == QString("--help") ||
            QString(argv[i]) == QString("-help")) {

            qDebug() << "Usage:";
            qDebug() << " -embedded : show in fullscreen mode";
            qDebug() << " -no-embedded : show in desktop mode";
            qDebug() << " -white : Set every background to white for screenshots. ";

            return 0;
        }
    }

    MainWindow* mainWindow = new MainWindow();
    mainWindow->show();
    return app.exec();
}
