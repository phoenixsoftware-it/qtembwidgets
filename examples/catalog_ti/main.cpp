/*
 Embedded Widgets Demo
 Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).*
 Contact:  Qt Software Information (qt-info@nokia.com)**
 This file may be used under the terms of the Embedded Widgets Demo License
 Agreement.
*/

/****************************************************************************
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
 *
 * The following changes were made by Texas Instruments Incorporated
 *
 * ChangeLog
 *
 * 2010/05/20 - v1.0
 * - added mouse support/command line application argument
 * - added tab focus command line application argument
 * 2010/06/29 - v1.2
 * - added the splash screen 
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
		qDebug() << " -tachometer : shows Tachometer (default)";
		qDebug() << " -thermometer : shows Thermometer";
		qDebug() << " -amperemeter : shows Amperemeter";
		qDebug() << " -graphs : shows Graphs";
		qDebug() << " -no-mouse : hides the mouse";

            return 0;
        }
    }

    QPixmap pixmap(":/QtEmbeddedSplash.png");
    QPixmap spixmap = pixmap.scaled(640, 480, Qt::KeepAspectRatio, Qt::FastTransformation);
    QSplashScreen splash(spixmap);
    splash.show();
    sleep(2);

    MainWindow* mainWindow = new MainWindow();
    mainWindow->show();
    return app.exec();
}
