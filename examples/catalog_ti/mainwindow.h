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
 * - added private slots: SliderxUpdate, toggleShowOverlayx, SliderxUpdate, mainTimerControl
 * - added protected methods: createTachmeter, createThermometer, createAmperemeter
 * - added needed variables & arrays
 * 2010/06/29 - v1.2
 * - added the Exit Button and its handling code
 */

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtGui>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QtWidgets>
#endif

#define TACHOMETER 0
#define THERMOMETER 1
#define AMPEREMETER 2
#define GRAPHS 3
#define EXIT 4
#define TIMEOUT 30

class QtBasicGraph;

enum FLAG {
UP,
DOWN,
STAY
};

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();
    virtual ~MainWindow();

private slots:
    void showGraph(int index);
    void toggleShowOverlay1(bool);
    void toggleShowOverlay2(bool);
    void toggleShowOverlay3(bool);
    void generatorTick();
    void slider1Update();
    void slider2Update();
    void slider3Update();
    void toggleTimerControl1(bool);
    void toggleTimerControl2(bool);
    void toggleTimerControl3(bool);
    void mainTimerControl(int);

protected:
    QWidget *createTachometer(bool with_overlay = true);
    QWidget *createThermometer(bool with_overlay = true);
    QWidget *createAmperemeter(bool with_overlay = true);
    QWidget *createGraphs();
    QWidget *createExit();

    void fillStaticGraph(QtBasicGraph *graph);
    
    void keyPressEvent(QKeyEvent *e);
    void contextMenuEvent(QContextMenuEvent *e);
    void mainTimerControlAccessory(int, bool);

private:
    bool m_embedded;
    QPushButton *m_overlay_button1, *m_overlay_button2, *m_overlay_button3;
    QPushButton *m_timer_control1, *m_timer_control2, *m_timer_control3;
    QtBasicGraph *m_graph;
    int m_graph_type;
    QTimer *m_graph_timer, *timer1, *timer2, *timer3;
    int m_graph_tick, currentActiveIndex;
    QSlider *slider1, *slider2, *slider3;
};


const int randVal[] = {5, 10, 15, 20, 24, 29, 33, 37, 42, 46, 50, 54, 58, 62, 65, 69, 73, 76, 80, 83, 86, 89, 93, 96, 99, 102, 105, 108, 111, 113, 116, 119, 121, 124, 126, 129, 131, 134, 136, 138, 140, 143, 145, 147, 149, 151, 153, 155, 157, 159, 160, 162, 164, 166, 167, 169, 171, 172, 174, 175, 177, 178, 180, 181, 182, 184, 185, 186, 188, 189, 190, 191, 192, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 207, 208, 209, 210, 211, 212, 212, 213, 214, 215, 215, 216, 217, 217, 218, 219, 219, 220, 220, 221, 222, 222, 223, 223, 224, 224, 225, 225, 226, 226, 227, 227, 228, 228, 229, 229, 230, 230, 230, 231, 231, 232, 232, 232, 233, 233, 233, 234, 234, 234, 235, 235, 235, 236, 236, 236, 236, 237, 237, 237, 238, 238, 238, 238, 239, 239, 239, 239, 239, 240, 240, 240, 240, 241, 241, 241, 241, 241, 241, 242, 242, 242, 242, 242, 242, 243, 243, 243, 243, 243, 243, 244, 244, 244, 244, 244, 244, 244, 244, 245, 245, 245, 245, 245, 245, 245, 245, 245, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 246, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 247, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 248, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249, 249};

const unsigned int thermVal[] = {3, 6, 9, 12, 15, 17, 20, 23, 25, 28, 30, 33, 35, 37, 39, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 61, 63, 65, 67, 68, 70, 71, 73, 75, 76, 77, 79, 80, 82, 83, 84, 86, 87, 88, 90, 91, 92, 93, 94, 95, 96, 97, 99, 100, 101, 102, 103, 103, 104, 105, 106, 107, 108, 109, 110, 110, 111, 112, 113, 114, 114, 115, 116, 116, 117, 118, 118, 119, 120, 124, 129, 133, 137, 142, 144, 148, 150, 153, 154, 156, 157, 158, 158, 159, 158, 158, 157, 156, 155, 153, 152, 150, 148, 147, 144, 142, 140, 138, 136, 134, 132, 131, 129, 127, 125, 124, 123, 122, 122, 121, 120, 120, 121, 121, 121, 121, 122, 123, 124, 124, 126, 127, 128, 130, 131, 133, 135, 136, 137, 138, 141, 142, 143, 144, 145, 146, 148, 149, 150, 150, 151, 151, 151, 152, 153, 153, 152, 152, 152, 152, 152, 152, 151, 151, 150, 149, 149, 148, 147, 147, 147, 146, 146, 145, 144, 144, 143, 143, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 142, 143, 143, 143, 144, 145, 145, 145, 146, 146, 147, 147, 147, 148, 148, 148, 149, 149, 149, 149, 150, 150, 150, 150, 151, 151, 151, 151, 151, 151, 151, 151, 151, 151, 150, 150, 150, 150, 150, 149, 149, 149, 149, 149, 148, 148, 148, 148, 148, 148, 148, 147, 147, 147, 147, 147, 147, 147, 147, 148, 148, 148, 148, 148, 148, 148, 149, 149, 149, 149, 149, 149, 149, 149, 149, 149, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 149, 149};

#endif // MAIN_WINDOW_H
