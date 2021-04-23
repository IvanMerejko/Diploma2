QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QT += quick
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Executors/Action.cpp \
    Data/Attribute.cpp \
    Data/DataBuilder.cpp \
    Data/JsonNode.cpp \
    Data/XMLNode.cpp \
    Data/BaseNode.cpp \
    Executors/BaseFilter.cpp \
    Executors/CompoundFilter.cpp \
    Executors/Filter.cpp \
    Executors/Parser.cpp \
    Models/ActionsTableModel.cpp \
    Models/AttributesTableModel.cpp \
    Models/FilterResultTable.cpp \
    Models/FiltersTableModel.cpp \
    Models/RulesTableModel.cpp \
    Models/TreeModel.cpp \
    Executors/Rule.cpp \
    Utils.cpp \
    Windows/MainWindowQml.cpp \
    Windows/FindWindow.cpp \
    Windows/NodeInfoWindow.cpp \
    main.cpp


HEADERS += \
    Executors/Action.h \
    Data/Attribute.h \
    Data/BaseNode.h \
    Data/DataBuilder.h \
    Data/JsonNode.h \
    Data/XMLNode.h \
    Executors/BaseFilter.h \
    Executors/CompoundFilter.h \
    Executors/Filter.h \
    Executors/Parser.h \
    Models/ActionsTableModel.h \
    Models/AttributesTableModel.h \
    Models/FilterResultTable.h \
    Models/FiltersTableModel.h \
    Models/RulesTableModel.h \
    Models/TreeModel.h \
    Executors/Rule.h \
    Utils.h \
    Windows/MainWindowQml.h \
    Windows/FindWindow.h \
    Types.h \
    Windows/NodeInfoWindow.h

CONFIG += conan_basic_setup
include(conanbuildinfo.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
   qml.qrc
