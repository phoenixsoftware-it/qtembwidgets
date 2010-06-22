/*
 Embedded Widgets Demo
 Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).*
 Contact:  Qt Software Information (qt-info@nokia.com)**
 This file may be used under the terms of the Embedded Widgets Demo License
 Agreement.
*/

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtGui>

class QtBasicGraph;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow();
    virtual ~MainWindow();

private slots:
    void showGraph(int index);
    void toggleShowOverlay(bool);
    void generatorTick();

protected:
    QWidget *createGauges(bool with_overlay = true);
    QWidget *createButtons();
    QWidget *createSliders();
    QWidget *createAdvanced();
    QWidget *createGraphs();

    void fillStaticGraph(QtBasicGraph *graph);
    
    void keyPressEvent(QKeyEvent *e);
    void contextMenuEvent(QContextMenuEvent *e);

private:
    bool m_embedded;
    QPushButton *m_overlay_button;
    QtBasicGraph *m_graph;
    int m_graph_type;
    QTimer *m_graph_timer;
    int m_graph_tick;
};

#endif // MAIN_WINDOW_H
