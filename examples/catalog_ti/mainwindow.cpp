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
 * - increased the size of gauge
 * - only one gauge in one tab
 * - removed buttons, slider, advanced tabs
 * - added damping motion to tachometer, thermometer and amperemeter
 * - modification to automate the size of gauge widgets in the embedded/non-embedded mode
 * - added the Start/Stop Automation Button & functionality
 * - changed the layout to suit the small lcd screen of TI EVM
 * 2010/06/29 - v1.2
 * - Added the Exit Button and its handling functions
 *  
 */

#include "mainwindow.h"

#include <QtGui>

#include <QtBasicDialGauge>
#include <QtBasicGraph>
#include <QtSvgDialGauge>

#include <math.h>

#ifndef TRUE
#define TRUE true
#endif

#ifndef FALSE
#define FALSE false
#endif

int guageWidgetSize;

class HackTabWidget : public QTabWidget {
public:
    using QTabWidget::tabBar;
};

/*!
    \class MainWindow
    \brief Fill the graphical user interface with the controls
*/
MainWindow::MainWindow()
    : QWidget(), m_graph_type(0) 
{
    if (QApplication::arguments().contains("-no-embedded"))
        m_embedded = false;
    else
    	m_embedded = true;

    setWindowTitle(tr("Embedded Widget Catalog"));
    setWindowIcon(QIcon(":/qtlogo-16.png")); 

    QSize fsize;

    if (m_embedded) {
    
	setWindowState(Qt::WindowFullScreen);
    }

    fsize = frameSize();       
    guageWidgetSize = 450;

    qDebug() << "Starting the Embedded Widget Catalog Demo by TI:";
//    qDebug() << "FrameBuffer Size:";
//    qDebug() << "width:" << fsize.width() <<"height:" << fsize.height();

    m_graph_timer = new QTimer(this);
    connect(m_graph_timer, SIGNAL(timeout()), this, SLOT(generatorTick()));

    QTabWidget *tw = new QTabWidget(this);
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    tw->setStyle(new QWindowsStyle());
#endif
    static_cast<HackTabWidget *>(tw)->tabBar()->setFocusPolicy(Qt::NoFocus);
    QBoxLayout *lay = new QVBoxLayout(this);
    int t;
    lay->getContentsMargins(0, &t, 0, 0);
    lay->setContentsMargins(0, t, 0, 0);
    lay->addWidget(tw);

    tw->addTab(createTachometer(), tr("Tachometer"));
    tw->addTab(createThermometer(), tr("Thermometer"));
    tw->addTab(createAmperemeter(), tr("Amperemeter"));
    tw->addTab(createGraphs(), tr("Graphs"));
    tw->addTab(createExit(), tr(" Exit "));

    connect(tw, SIGNAL(currentChanged(int)), this, SLOT(mainTimerControl(int)));

    if (!m_embedded) {
        resize(fsize.width()/2, fsize.height()/2);
    } else {
	if (QApplication::arguments().contains("-no-mouse"))
        	qApp->setOverrideCursor(Qt::BlankCursor);
    }
	if (QApplication::arguments().contains("-thermometer")){
		currentActiveIndex = THERMOMETER;
		tw->setCurrentIndex(THERMOMETER);
		toggleTimerControl2(TRUE);
	} else if (QApplication::arguments().contains("-amperemeter")){
		currentActiveIndex = AMPEREMETER;
		tw->setCurrentIndex(AMPEREMETER);
		toggleTimerControl3(TRUE);
	} else if (QApplication::arguments().contains("-graphs")){
		currentActiveIndex = GRAPHS; 
		tw->setCurrentIndex(GRAPHS);
	} else {
		currentActiveIndex = TACHOMETER;
		tw->setCurrentIndex(TACHOMETER);
		toggleTimerControl1(TRUE);
	}
}


MainWindow::~MainWindow()
{
    // no need to delete the user interface, Qt does it for us
}

/*!
    Create Tachometer on tab page
*/
QWidget *MainWindow::createTachometer(bool with_overlay)
{
    QWidget *page = new QWidget();
    QVBoxLayout *toplay = new QVBoxLayout(page);

    QWidget *group = new QGroupBox(tr("Gauges"), page);
    QGridLayout *grid = new QGridLayout(group);
    QGridLayout *boxgrid = new QGridLayout(group);

    toplay->addWidget(group);

    // Tachometer
    QtSvgDialGauge *gauge = new QtSvgDialGauge(group);
    gauge->setSkin("Tachometer");
    gauge->setNeedleOrigin(0.486, 0.466);
    gauge->setMinimum(0);
    gauge->setMaximum(360);
    gauge->setStartAngle(-130);
    gauge->setEndAngle(133);
    gauge->setValue(0);
    gauge->setMaximumSize(guageWidgetSize, guageWidgetSize);

    slider1 = new QSlider(Qt::Horizontal, group);
    slider1->setRange(0, 360);
    slider1->setValue(0);
    slider1->setProperty("isEmbedded", m_embedded);
    connect(slider1, SIGNAL(valueChanged(int)), gauge, SLOT(setValue(int)));
    
    grid->addWidget(gauge, 0, 1, Qt::AlignHCenter);
    boxgrid->addWidget(slider1, 0, 0);
        
    m_overlay_button1 = new QPushButton(tr("Show Overlays"), group);
    m_overlay_button1->setObjectName("ToggleOverlay");
    m_overlay_button1->setCheckable(true);
    m_overlay_button1->setChecked(true);
    connect(m_overlay_button1, SIGNAL(toggled(bool)), this, SLOT(toggleShowOverlay1(bool)));
    
    m_timer_control1 = new QPushButton(tr("Stop Automation"), group);
    m_timer_control1->setObjectName("ToggleTimer");
    m_timer_control1->setCheckable(true);
    m_timer_control1->setChecked(true);
    connect(m_timer_control1, SIGNAL(toggled(bool)), this, SLOT(toggleTimerControl1(bool)));
    
    boxgrid->addWidget(m_overlay_button1, 1, 0);
    boxgrid->addWidget(m_timer_control1, 2, 0);

    grid->addLayout(boxgrid, 0, 0, Qt::AlignCenter);

    toggleShowOverlay1(with_overlay);

    timer1 = new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(slider1Update()));

    return page;
}

/*!
    Create Thermometer on tab page
*/

QWidget *MainWindow::createThermometer(bool with_overlay)
{
    QWidget *page = new QWidget();
    QVBoxLayout *toplay = new QVBoxLayout(page);

    QWidget *group = new QGroupBox(tr("Gauges"), page);
    QGridLayout *grid = new QGridLayout(group);
    QGridLayout *boxgrid = new QGridLayout(group);

    toplay->addWidget(group);

    // Thermometer
    QtSvgDialGauge *gauge = new QtSvgDialGauge(group);
    gauge->setSkin("Thermometer");
    gauge->setNeedleOrigin(0.456, 0.459);
    gauge->setMinimum(0);
    gauge->setMaximum(360);
    gauge->setStartAngle(-90);
    gauge->setEndAngle(150);
    gauge->setValue(0);
    gauge->setMaximumSize(guageWidgetSize, guageWidgetSize);

    slider2 = new QSlider(Qt::Horizontal, group);
    slider2->setRange(0, 360);
    slider2->setValue(0);
    slider2->setProperty("isEmbedded", m_embedded);
    connect(slider2, SIGNAL(valueChanged(int)), gauge, SLOT(setValue(int)));

    grid->addWidget(gauge, 0, 1, Qt::AlignHCenter);
    boxgrid->addWidget(slider2, 0, 0);

    m_overlay_button2 = new QPushButton(tr("Show Overlays"), group);
    m_overlay_button2->setObjectName("ToggleOverlay");
    m_overlay_button2->setCheckable(true);
    m_overlay_button2->setChecked(true);
    connect(m_overlay_button2, SIGNAL(toggled(bool)), this, SLOT(toggleShowOverlay2(bool)));

    m_timer_control2 = new QPushButton(tr("Stop Automation"), group);
    m_timer_control2->setObjectName("ToggleTimer");
    m_timer_control2->setCheckable(true);
    m_timer_control2->setChecked(true);
    connect(m_timer_control2, SIGNAL(toggled(bool)), this, SLOT(toggleTimerControl2(bool)));

    boxgrid->addWidget(m_overlay_button2, 1, 0);
    boxgrid->addWidget(m_timer_control2, 2, 0);
    grid->addLayout(boxgrid, 0, 0, Qt::AlignCenter);

    toggleShowOverlay2(with_overlay);

    timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(slider2Update()));

    return page;
}

/*!
    Create Amperemeter on tab page
*/

QWidget *MainWindow::createAmperemeter(bool with_overlay)
{
    QWidget *page = new QWidget();
    QVBoxLayout *toplay = new QVBoxLayout(page);

    QWidget *group = new QGroupBox(tr("Different Gauges"), page);
    QGridLayout *grid = new QGridLayout(group);
    QGridLayout *boxgrid = new QGridLayout(group);

    toplay->addWidget(group);
    
    // Amperemeter
    QtSvgDialGauge *gauge = new QtSvgDialGauge(group);
    gauge->setSkin("Amperemeter");
    gauge->setNeedleOrigin(0.5, .83596590);
    gauge->setMinimum(0);
    gauge->setMaximum(360);
    gauge->setStartAngle(-42);
    gauge->setEndAngle(42);
    gauge->setValue(0);
    gauge->setMaximumSize(guageWidgetSize, guageWidgetSize);

    slider3 = new QSlider(Qt::Horizontal, group);
    slider3->setRange(0, 360);
    slider3->setValue(0);
    slider3->setProperty("isEmbedded", m_embedded);
    connect(slider3, SIGNAL(valueChanged(int)), gauge, SLOT(setValue(int)));

    grid->addWidget(gauge, 0, 1, Qt::AlignHCenter);
    boxgrid->addWidget(slider3, 0, 0);

    m_overlay_button3 = new QPushButton(tr("Show Overlays"), group);
    m_overlay_button3->setObjectName("ToggleOverlay");
    m_overlay_button3->setCheckable(true);
    m_overlay_button3->setChecked(true);
    connect(m_overlay_button3, SIGNAL(toggled(bool)), this, SLOT(toggleShowOverlay3(bool)));

    m_timer_control3 = new QPushButton(tr("Stop Automation"), group);
    m_timer_control3->setObjectName("ToggleTimer");
    m_timer_control3->setCheckable(true);
    m_timer_control3->setChecked(true);
    connect(m_timer_control3, SIGNAL(toggled(bool)), this, SLOT(toggleTimerControl3(bool)));

    boxgrid->addWidget(m_overlay_button3, 1, 0);
    boxgrid->addWidget(m_timer_control3, 2, 0);
    grid->addLayout(boxgrid, 0, 0, Qt::AlignCenter);

    toggleShowOverlay3(with_overlay);

    timer3 = new QTimer(this);
    connect(timer3, SIGNAL(timeout()), this, SLOT(slider3Update()));

    return page;
}

void MainWindow::toggleTimerControl1(bool b)
{
    m_timer_control1->setText(b ? tr("Stop Automation") : tr("Start Automation"));
    switch (b)
    {
    case TRUE:
        timer1->start(TIMEOUT);
        break;
    case FALSE:
        timer1->stop();
    }
}

void MainWindow::toggleTimerControl2(bool b)
{
    m_timer_control2->setText(b ? tr("Stop Automation") : tr("Start Automation"));
    switch (b)
    {
    case TRUE:
        timer2->start(TIMEOUT);
        break;
    case FALSE:
        timer2->stop();
    }
}

void MainWindow::toggleTimerControl3(bool b)
{
    m_timer_control3->setText(b ? tr("Stop Automation") : tr("Start Automation"));
    switch (b)
    {
    case TRUE: 
	timer3->start(TIMEOUT);
	break;
    case FALSE:
	timer3->stop();
    }
}

void MainWindow::toggleShowOverlay1(bool b)
{
    m_overlay_button1->setText(b ? tr("Hide Overlays") : tr("Show Overlays"));

    foreach (QtSvgDialGauge *gauge, m_overlay_button1->parentWidget()->findChildren<QtSvgDialGauge *>())
		gauge->setShowOverlay(b);
}

void MainWindow::toggleShowOverlay2(bool b)
{
    m_overlay_button2->setText(b ? tr("Hide Overlays") : tr("Show Overlays"));

    foreach (QtSvgDialGauge *gauge, m_overlay_button2->parentWidget()->findChildren<QtSvgDialGauge *>())
                gauge->setShowOverlay(b);
}

void MainWindow::toggleShowOverlay3(bool b)
{
    m_overlay_button3->setText(b ? tr("Hide Overlays") : tr("Show Overlays"));

    foreach (QtSvgDialGauge *gauge, m_overlay_button3->parentWidget()->findChildren<QtSvgDialGauge *>())
                gauge->setShowOverlay(b);
}

QWidget *MainWindow::createExit()
{
	QWidget *page = new QWidget();	
	return page;
}

/*!
    fill sheet "Graphs" with the graphs
*/
QWidget *MainWindow::createGraphs()
{
    QWidget *page = new QWidget();
    QVBoxLayout *toplay = new QVBoxLayout(page);

    QWidget *group = new QGroupBox(tr("Graph with Static or Dynamic Content"), page);
    QGridLayout *grid = new QGridLayout(group);

    toplay->addWidget(group);

    // create sinus graph and model
    m_graph = new QtBasicGraph(group);
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    m_graph->setStyle(new QWindowsStyle());
#endif
    m_graph->setProperty("isEmbedded", m_embedded);
    m_graph->setFocusPolicy(Qt::NoFocus);
    if (!m_embedded)
        m_graph->setRenderHints(QPainter::Antialiasing);

    grid->addWidget(m_graph, 0, 0, 1, 4);

    QLabel *label = new QLabel(tr("Choose Graph Type"), group);
    grid->addWidget(label, 1, 1, Qt::AlignRight);
    QComboBox *chooser = new QComboBox(group);
    chooser->addItems(QStringList() << tr("Static Graph") << tr("Dynamic Sinus Graph") << tr("Dynamic Heartbeat Graph"));
    connect(chooser, SIGNAL(currentIndexChanged(int)), this, SLOT(showGraph(int)));
    grid->addWidget(chooser, 1, 2);
    
    showGraph(0);

    return page;
}

void MainWindow::fillStaticGraph(QtBasicGraph *graph)
{
    graph->addPoint(QPointF(0, 0));
    graph->addPoint(QPointF(20, 0));
    graph->addPoint(QPointF(20, 10));
    graph->addPoint(QPointF(50, 10));
    graph->addPoint(QPointF(50, -10));
    graph->addPoint(QPointF(80, -10));
    graph->addPoint(QPointF(80, 10));
    graph->addPoint(QPointF(110, 10));
    graph->addPoint(QPointF(110, -10));
    graph->addPoint(QPointF(140, -10));
    graph->addPoint(QPointF(140, 0));

    for (int i = 0; i < 120; ++i) {
        double val = sin(i / 120.0 * 3.1415926535 * 7.0);
        graph->addPoint(QPointF(140 + i, val * 5.0));
    }

    graph->addPoint(QPointF(260, 0));
    graph->addPoint(QPointF(260, -10));
    graph->addPoint(QPointF(290, -10));
    graph->addPoint(QPointF(290, 10));
    graph->addPoint(QPointF(320, 10));
    graph->addPoint(QPointF(320, -10));
    graph->addPoint(QPointF(350, -10));
    graph->addPoint(QPointF(350, 10));
    graph->addPoint(QPointF(380, 10));
    graph->addPoint(QPointF(380, 0));
    graph->addPoint(QPointF(400, 0));
}

void MainWindow::showGraph(int index)
{
    m_graph_timer->stop();
    m_graph_type = index;
    m_graph_tick = 0;

    if (index == 0) { // static
        m_graph->clear();
        m_graph->setYMinMax(-15, 15);
        m_graph->setXRange(400);

        fillStaticGraph(m_graph);
    } else if (index == 1) { // sinus
        m_graph_timer->start(33);

        m_graph->clear();
        m_graph->setYMinMax(-1.2, 1.2);
        m_graph->setXRange(360);
    } else if (index == 2) { // heartbeat
        m_graph_timer->start(33);

        m_graph->clear();
        m_graph->setYMinMax(-10, 10);
        m_graph->setXRange(180);
    }
}

void MainWindow::generatorTick()
{
    ++m_graph_tick;

    if (m_graph_type == 1) { // sinus
        double calc_at = (m_graph_tick % 360) * 3.1415926535798932846 / 180.0;
        m_graph->addPoint(QPointF(m_graph_tick, sin(calc_at)));
    } else if (m_graph_type == 2) { // heartbeat
        int frame = m_graph_tick % 27;

        if (frame == 25)
            m_graph->addPoint(QPointF(m_graph_tick, 5.0));
        else if (frame == 26)
            m_graph->addPoint(QPointF(m_graph_tick, -2.0));
        else
            m_graph->addPoint(QPointF(m_graph_tick, 0.5*qrand() / static_cast<double>(RAND_MAX)));
    } else {
        m_graph_timer->stop();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        qApp->quit();
}

void MainWindow::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu menu(this);
    QAction* action = menu.addAction(tr("Close Catalog"));

    if (menu.exec(event->globalPos()) == action) {
        close();
    }
}

void MainWindow::slider1Update()
{
	static FLAG flag = UP;
	static int intCount = 0;
	int val = slider1->value();
//printf("%d %d %d\n", flag, intCount, val);
	switch (flag){
	case UP:
		if (intCount < 255){
			slider1->setValue(randVal[intCount++]);
		}else{
			flag = DOWN;
			intCount = 0;
		}
		break;
	case DOWN:
		if (val >= 2){
			val = val-1;
			slider1->setValue(val);
		} else {
			flag = STAY;
		}
		break;
	case STAY:
		if (intCount < 80){
			slider1->setValue(val);
			intCount++;
			break;
		}
	default:
		flag = UP;
		intCount = 0;
	}
}

void MainWindow::slider2Update()
{
	static FLAG flag2 = UP;
        int val2 = slider2->value();
	static int intCount2 = 0;
//printf("%d %d\n",val2, flag2);
	switch(flag2){
	case UP:
		if (val2 < 359){
			val2 += 2;
			slider2->setValue(val2);
            }else{
			flag2 = DOWN;
		}
		break;
	case DOWN:        
		if (val2 >= 2){
			val2 = val2-1;
			slider2->setValue(val2);
		} else {
			flag2 = STAY;
		}
		break;
	case STAY:
		if (intCount2 < 80){
			slider2->setValue(val2);
			intCount2++;
			break;
		}
	default:
		flag2 = UP;
		intCount2 = 0;
	}
}

void MainWindow::slider3Update()
{
	static FLAG flag3 = UP;
	static int intCount3 = 0;
        int val3 = slider3->value();

	switch (flag3){
	case UP:
		if (intCount3 < 250){
			slider3->setValue(thermVal[intCount3++]);
		}else{
			flag3 = DOWN;
			intCount3 = 0;
		}
		break;
	case DOWN:
		if (val3 >= 2){
			val3 = val3-1;
			slider3->setValue(val3);
		} else {
			flag3 = STAY;
		}
		break;
	case STAY:
		if (intCount3 < 80){
			slider3->setValue(val3);
			intCount3++;
			break;
		}
	default:
		flag3 = UP;
		intCount3 = 0;             
	}
}

void MainWindow::mainTimerControl (int index)
{
	mainTimerControlAccessory (currentActiveIndex, FALSE);
	currentActiveIndex = index;
	mainTimerControlAccessory (currentActiveIndex, TRUE);	
}

void MainWindow::mainTimerControlAccessory (int index, bool b)
{
	switch (index) 
	{
	case TACHOMETER:
		toggleTimerControl1(b);
		break;
	case THERMOMETER:
		toggleTimerControl2(b);
                break;
	case AMPEREMETER:
		toggleTimerControl3(b);
                break;
	case EXIT:
		this->close();
		break;
	case GRAPHS:
	default:
		break;
	}
}
