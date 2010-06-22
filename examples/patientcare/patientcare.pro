TEMPLATE = app
INCLUDEPATH += .

include(../../src/common/common.pri)
include(../../src/svgslideswitch/svgslideswitch.pri)
include(../../src/scrolldial/scrolldial.pri)
include(../../src/5waybutton/5waybutton.pri)
include(../../src/multislider/multislider.pri)
include(../../src/basicgraph/basicgraph.pri)
include(../../src/svgtoggleswitch/svgtoggleswitch.pri)

CONFIG += release
CONFIG -= debug

RESOURCES += patientcare.qrc \
    ../../skins/beryl_multislider.qrc \
    ../../skins/beryl_svgslideswitch.qrc \
    ../../skins/beryl_scrolldial.qrc \
    ../../skins/beryl_5waybutton.qrc \
    ../../skins/beryl_scrollwheel.qrc \
    ../../skins/beryl_svgtoggleswitch.qrc


HEADERS += \
    mainwindow.h \
    datagenerator.h \
    patientcarecontroller.h \
    lazytimer.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    datagenerator.cpp \
    patientcarecontroller.cpp \
    lazytimer.cpp

FORMS = patientcare.ui

QT *= svg
