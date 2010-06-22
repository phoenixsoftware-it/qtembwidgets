/*
 Embedded Widgets Demo
 Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).*
 Contact:  Qt Software Information (qt-info@nokia.com)**
 This file may be used under the terms of the Embedded Widgets Demo License
 Agreement.
*/

#include "mainwindow.h"

#include <QtGui>

#include <Qt5WayButton>
#include <QtBasicDialGauge>
#include <QtBasicGraph>
#include <QtMultiSlider>
#include <QtScrollDial>
#include <QtScrollWheel>
#include <QtSvgButton>
#include <QtSvgDialGauge>
#include <QtSvgSlideSwitch>
#include <QtSvgToggleSwitch>

#include <math.h>

/*!
    \page Catalog Catalog example

    \brief This is an example implementation to show the different
    embedded widgets.

    Here are the used controls with their skins.

    \section Gauges Sheet "Gauges"
        The following skins with QtSvgDialGauge are used.
        - Gauge with skin "Tachometer"
        - Gauge with skin "Thermometer"
        - Gauge with skin "Amperemeter"

        QtBasicDialGauge without skin.

    \section Buttons Sheet "Buttons"
        with skin "Beryl"
        - QtSvgSlideSwitch
        - QtSvgButton
        with skin BerylSquare
        - QtSvgButton
        with skin "Beryl"
        - QtSvgToggleSwitch
        with skin "BerylSquare"
        - QtSvgToggleSwitch

    \section Advanced_Widgets Sheet "Advanced Widgets"
        with skin "Beryl"
        - Qt5WayButton
        - QtScrollDial

    \section Sliders Sheet "Sliders"
        with skin "Beryl"
        - QtScrollWheel
        - QtMultiSlider

    \section Graphs Sheet "Graphs"
        - QtBasicGraph
*/

class HackTabWidget : public QTabWidget {
public:
    using QTabWidget::tabBar;
};

/*!
    \class MainWindow
    \brief Fill the graphical user interface with the controls
*/
MainWindow::MainWindow()
    : QWidget(), m_embedded(false), m_graph_type(0) 
{
#if defined(Q_WS_HILDON) || defined(Q_WS_S60) || defined(Q_WS_QWS) || defined(Q_OS_WINCE)
    m_embedded = true;
#endif
    if (QApplication::arguments().contains("-embedded"))
        m_embedded = true;
    if (QApplication::arguments().contains("-no-embedded"))
        m_embedded = false;

    setWindowTitle(tr("Embedded Widget Catalog"));
    setWindowIcon(QIcon(":/qtlogo-16.png")); 

    m_graph_timer = new QTimer(this);
    connect(m_graph_timer, SIGNAL(timeout()), this, SLOT(generatorTick()));

    QTabWidget *tw = new QTabWidget(this);
    tw->setStyle(new QWindowsStyle());
    static_cast<HackTabWidget *>(tw)->tabBar()->setFocusPolicy(Qt::NoFocus);
    QBoxLayout *lay = new QVBoxLayout(this);
    int t;
    lay->getContentsMargins(0, &t, 0, 0);
    lay->setContentsMargins(0, t, 0, 0);
    lay->addWidget(tw);

    tw->addTab(createGauges(), tr("Gauges"));
    tw->addTab(createButtons(), tr("Buttons"));
    tw->addTab(createAdvanced(), tr("Advanced"));
    tw->addTab(createSliders(), tr("Sliders"));
    tw->addTab(createGraphs(), tr("Graphs"));

    if (!m_embedded) {
        resize(800, 600);
    } else {
        qApp->setOverrideCursor(Qt::BlankCursor);
        setWindowState(Qt::WindowFullScreen);
    }
}


MainWindow::~MainWindow()
{
    // no need to delete the user interface, Qt does it for us
}

/*!
    fill sheet "Gauges" with the gauges
*/
QWidget *MainWindow::createGauges(bool with_overlay)
{
    QWidget *page = new QWidget();
    QVBoxLayout *toplay = new QVBoxLayout(page);

    QWidget *group = new QGroupBox(tr("Different Gauges"), page);
    QGridLayout *grid = new QGridLayout(group);

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
    gauge->setMaximumSize(200, 200);

    QLabel* label = new QLabel(tr("Tachometer"), group);
    label->setAlignment(Qt::AlignHCenter);

    QSlider* slider = new QSlider(Qt::Horizontal, group);
    slider->setRange(0, 360);
    slider->setValue(0);
    slider->setProperty("isEmbedded", m_embedded);
    connect(slider, SIGNAL(valueChanged(int)), gauge, SLOT(setValue(int)));
    
    grid->addWidget(gauge, 0, 0, Qt::AlignHCenter);
    grid->addWidget(label, 1, 0);
    grid->addWidget(slider, 2, 0);
    
    // Thermometer
    gauge = new QtSvgDialGauge(group);
    gauge->setSkin("Thermometer");
    gauge->setNeedleOrigin(0.456, 0.459);
    gauge->setMinimum(0);
    gauge->setMaximum(360);
    gauge->setStartAngle(-90);
    gauge->setEndAngle(150);
    gauge->setValue(0);
    gauge->setMaximumSize(200, 200);

    label = new QLabel(tr("Thermometer"), group);
    label->setAlignment(Qt::AlignHCenter);

    slider = new QSlider(Qt::Horizontal, group);
    slider->setRange(0, 360);
    slider->setValue(0);
    slider->setProperty("isEmbedded", m_embedded);
    connect(slider, SIGNAL(valueChanged(int)), gauge, SLOT(setValue(int)));

    grid->addWidget(gauge, 0, 1, Qt::AlignHCenter);
    grid->addWidget(label, 1, 1);
    grid->addWidget(slider, 2, 1);

    // Amperemeter
    gauge = new QtSvgDialGauge(group);
    gauge->setSkin("Amperemeter");
    gauge->setNeedleOrigin(0.5, .83596590);
    gauge->setMinimum(0);
    gauge->setMaximum(360);
    gauge->setStartAngle(-42);
    gauge->setEndAngle(42);
    gauge->setValue(0);
    gauge->setMaximumSize(200, 200);

    label = new QLabel(tr("Amperemeter"), group);
    label->setAlignment(Qt::AlignHCenter);

    slider = new QSlider(Qt::Horizontal, group);
    slider->setRange(0, 360);
    slider->setValue(0);
    slider->setProperty("isEmbedded", m_embedded);
    connect(slider, SIGNAL(valueChanged(int)), gauge, SLOT(setValue(int)));

    grid->addWidget(gauge, 0, 2, Qt::AlignHCenter);
    grid->addWidget(label, 1, 2);
    grid->addWidget(slider, 2, 2);

    m_overlay_button = new QPushButton(tr("Show Overlays"), group);
    m_overlay_button->setObjectName("ToggleOverlay");
    m_overlay_button->setCheckable(true);
    m_overlay_button->setChecked(true);
    connect(m_overlay_button, SIGNAL(toggled(bool)), this, SLOT(toggleShowOverlay(bool)));

    grid->addWidget(m_overlay_button, 3, 1);

    grid->setRowStretch(grid->rowCount(), 100);
    
    toggleShowOverlay(with_overlay);

    return page;
}

void MainWindow::toggleShowOverlay(bool b)
{
    m_overlay_button->setText(b ? tr("Hide Overlays") : tr("Show Overlays"));

    foreach (QtSvgDialGauge *gauge, m_overlay_button->parentWidget()->findChildren<QtSvgDialGauge *>())
        gauge->setShowOverlay(b);
}

/*!
    fill sheet "Buttons" with the buttons
*/
QWidget *MainWindow::createButtons()
{
    QWidget *page = new QWidget();
    QGridLayout *toplay = new QGridLayout(page);
    
    QGroupBox *beryl = new QGroupBox(tr("Beryl"), page);
    QGroupBox *berylsq = new QGroupBox(tr("Beryl Square"), page);
    QGroupBox *metallic = new QGroupBox(tr("Metallic Brush"), page);
    metallic->setProperty("isMetallic", true);
    
    toplay->addWidget(beryl, 0, 0);
    toplay->addWidget(metallic, 1, 0);
    toplay->addWidget(berylsq, 0, 1, 2, 1);
    toplay->setColumnStretch(0, 60);
    toplay->setColumnStretch(1, 40);

    QGridLayout *bgrid = new QGridLayout(beryl);
    QGridLayout *mgrid = new QGridLayout(metallic);
    QGridLayout *sgrid = new QGridLayout(berylsq);


    QtSvgSlideSwitch* slide;
    QtSvgButton *button;
    QtSvgToggleSwitch *toggle;
    QLabel* label;

    // Beryl
    slide = new QtSvgSlideSwitch(beryl);
    slide->setSkin("Beryl");    
    label = new QLabel(tr("QtSvgSlideSwitch"), beryl);
    label->setAlignment(Qt::AlignHCenter);
    bgrid->addWidget(slide, 0, 0, Qt::AlignHCenter);
    bgrid->addWidget(label, 1, 0, Qt::AlignHCenter);

    button = new QtSvgButton(beryl);
    button->setSkin("Beryl");
    label = new QLabel(tr("QtSvgButton"), beryl);
    label->setAlignment(Qt::AlignHCenter);
    bgrid->addWidget(button, 0, 1, Qt::AlignHCenter);
    bgrid->addWidget(label, 1, 1, Qt::AlignHCenter);

    toggle = new QtSvgToggleSwitch(beryl);
    toggle->setSkin("Beryl");
    label = new QLabel(tr("QtSvgToggleSwitch"), beryl);
    label->setAlignment(Qt::AlignHCenter);
    bgrid->addWidget(toggle, 0, 3, Qt::AlignHCenter);
    bgrid->addWidget(label, 1, 3, Qt::AlignHCenter);

    bgrid->setRowStretch(bgrid->rowCount(), 100);

    // Metallic Brush
    slide = new QtSvgSlideSwitch(metallic);
    slide->setSkin("MetallicBrush");
    label = new QLabel(tr("QtSvgSlideSwitch"), metallic);
    label->setAlignment(Qt::AlignHCenter);
    mgrid->addWidget(slide, 0, 0, Qt::AlignHCenter);
    mgrid->addWidget(label, 1, 0, Qt::AlignHCenter);

    button = new QtSvgButton(metallic);
    button->setSkin("MetallicBrush");
    label = new QLabel(tr("QtSvgButton"), metallic);
    label->setAlignment(Qt::AlignHCenter);
    mgrid->addWidget(button, 0, 1, Qt::AlignHCenter);
    mgrid->addWidget(label, 1, 1, Qt::AlignHCenter);

    mgrid->setRowStretch(mgrid->rowCount(), 100);

    // Beryl Square
    button = new QtSvgButton(beryl);
    button->setSkin("BerylSquare");
    label = new QLabel(tr("QtSvgButton"), berylsq);
    label->setAlignment(Qt::AlignHCenter);
    sgrid->addWidget(button, 0, 0, Qt::AlignHCenter);
    sgrid->addWidget(label, 1, 0, Qt::AlignHCenter);
    
    sgrid->setRowMinimumHeight(2, 16);
    
    toggle = new QtSvgToggleSwitch(metallic);
    toggle->setSkin("BerylSquare");
    label = new QLabel(tr("QtSvgToggleSwitch"), berylsq);
    label->setAlignment(Qt::AlignHCenter);
    sgrid->addWidget(toggle, 3, 0, Qt::AlignHCenter);
    sgrid->addWidget(label, 4, 0, Qt::AlignHCenter);

    sgrid->setRowStretch(sgrid->rowCount(), 100);

    return page;
}

/*!
    fill sheet "Advanced Widgets" with the advanced widgets
*/
QWidget *MainWindow::createAdvanced()
{
    QWidget *page = new QWidget();
    QVBoxLayout *toplay = new QVBoxLayout(page);

    QWidget *group = new QGroupBox(tr("Beryl"), page);
    QGridLayout *grid = new QGridLayout(group);

    toplay->addWidget(group);

    QLabel *label;
    
    Qt5WayButton *nav5way = new Qt5WayButton(group);
    nav5way->setSkin("Beryl");
    label = new QLabel(tr("Qt5WayButton"), group);
    label->setAlignment(Qt::AlignHCenter);
    grid->addWidget(nav5way, 0, 0, Qt::AlignHCenter);
    grid->addWidget(label, 1, 0, Qt::AlignHCenter);

    QtScrollDial *dial = new QtScrollDial(group);
    dial->setRange(0, 100);
    dial->setValue(50);
    dial->setSkin("Beryl");
    dial->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    label = new QLabel(tr("QtScrollDial"), group);
    label->setAlignment(Qt::AlignHCenter);
    grid->addWidget(dial, 0, 1, Qt::AlignHCenter);
    grid->addWidget(label, 1, 1, Qt::AlignHCenter);

    return page;
}

/*!
    fill sheet "Sliders" with the sliders
*/
QWidget *MainWindow::createSliders()
{
    QWidget *page = new QWidget();
    QVBoxLayout *toplay = new QVBoxLayout(page);

    QWidget *group = new QGroupBox(tr("Beryl"), page);
    QGridLayout *grid = new QGridLayout(group);

    toplay->addWidget(group);

    QLabel *label;

    QtScrollWheel *scrollWheel = new QtScrollWheel(group);
    scrollWheel->setRange(0, 100);
    scrollWheel->setValue(50);
    scrollWheel->setSkin("Beryl");
    label = new QLabel(tr("QtScrollWheel"), group);
    label->setAlignment(Qt::AlignHCenter);
    grid->addWidget(scrollWheel, 0, 0, Qt::AlignHCenter);
    grid->addWidget(label, 1, 0, Qt::AlignHCenter);

    QtMultiSlider *multiSlider = new QtMultiSlider(group);
    multiSlider->setSkin("Beryl");
    multiSlider->setValue(70);
    label = new QLabel(tr("QtMultiSlider"), group);
    label->setAlignment(Qt::AlignHCenter);
    grid->addWidget(multiSlider, 0, 1, Qt::AlignHCenter);
    grid->addWidget(label, 1, 1, Qt::AlignHCenter);


    QSlider* slider = new QSlider(Qt::Vertical, group);
    slider->setValue(30);
    QString css = "QSlider::groove:vertical {"
                  "  border: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
                  "    stop:0 #B1B1B1, stop:1 #000000);"
                  "}"
                  "QSlider::handle:vertical {"
                  "  background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                  "    stop:0 #DFDFDF, stop: 0.5 #7E7E7E, stop:1 #BCBCBC);"
                  "  border: 2px solid #709E10;"
                  "  border-radius: 3px;"
                  "  width: 30px;"
                  "  height: 30px;"
                  "} "
                  "QSlider::add-page:vertical {"
                  "  background: qlineargradient(x1:0, y1:0, x2:1, y2:0, "
                  "    stop: 0 #C3E0CC, stop: 0.5 #7FB605, stop:1 #D8F000);"
                  "}"
                  "QSlider::sub-page:vertical {"
                  "  background: qlineargradient(x1:0, y1:0, x2:1, y2:0, "
                  "    stop: 0 #CCD5CC, stop: 0.5 #435A12, stop:1 #5C6700);"
                  "}"
                  "QSlider::handle:pressed {"
                  "  background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                  "    stop:0 #DFDFDF, stop: 0.5 #7E7E7E, stop:1 #BCBCBC);"
                  "  border: 2px solid #D0F201;"
                  "  border-radius: 3px;"
                  "}";
    slider->setStyleSheet(css);
    label = new QLabel(tr("QSlider\n(Qt Style Sheets)"), group);
    label->setAlignment(Qt::AlignHCenter);
    grid->addWidget(slider, 0, 2, Qt::AlignHCenter);
    grid->addWidget(label, 1, 2, Qt::AlignHCenter);
    
    grid->setRowStretch(grid->rowCount(), 100);
    
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
    m_graph->setStyle(new QWindowsStyle());
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

