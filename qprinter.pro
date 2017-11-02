include(shared.pri)

#TEMPLATE = app
TEMPLATE = lib

TARGET   = qprinter

#CONFIG += warn_off
CONFIG += warn_off dll
QT += core widgets axserver websockets

SOURCES  = main.cpp \
    setupbox.cpp
RC_FILE  = qprinter.rc
DEF_FILE = qprinter.def

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/activeqt/simple
#INSTALLS += target

HEADERS += \
    setupbox.h
