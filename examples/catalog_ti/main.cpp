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
 * - added the variable resolution support for splash screen
 */

#include <QtGui>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fb.h>


#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    
    QFile f(":/catalog.css");
    if (f.open(QIODevice::ReadOnly)) {
        app.setStyleSheet(f.readAll());
        f.close();
    }

	QSize *fbDisplaySize = new QSize(640, 480); 

	int fbHandle = open("/dev/fb0", O_RDWR);
	if (fbHandle >= 0){
		struct fb_var_screeninfo var;
		int ret = ioctl(fbHandle, FBIOGET_VSCREENINFO, &var);
		if(ret < 0) {
			qDebug() << "Cannot get variable screen information";
			qDebug() << "Splash Screen will be of the default size: 640x480";
			close(fbHandle);
		} else {
			fbDisplaySize->setWidth(var.xres);
			fbDisplaySize->setHeight(var.yres); 

			for (int i = 0; i < argc; ++i) {
				if (QString(argv[i]) == QString("-r") ||
					QString(argv[i]) == QString("-R")) {
					fbDisplaySize->setWidth(var.yres);
            		fbDisplaySize->setHeight(var.xres);
				}
			}	

	//		qDebug() << "w" << fbDisplaySize->width() << "h" << fbDisplaySize->height();
			close(fbHandle);
		}
	} else {
		qDebug() << "Error Querying in the size of the framebuffer";
		qDebug() << "Splash Screen will be of the default size: 640x480";
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
		qDebug() << " -r : rotates the splash screen - Use with -display Transformed:rot90|270";

            return 0;
        }
    }

    QPixmap pixmap(":/QtEmbeddedSplash.png");
    QPixmap spixmap = pixmap.scaled(fbDisplaySize->width(), fbDisplaySize->height(), Qt::IgnoreAspectRatio, Qt::FastTransformation);
    QSplashScreen splash(spixmap);
    splash.show();
	sleep(1);
    MainWindow* mainWindow = new MainWindow();
    mainWindow->show();
	splash.finish(mainWindow);
    return app.exec();
}
