QT += testlib sql
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testdocuments.cpp \
    ../Plan-Describer/documenttablesaggregate.cpp

HEADERS += \
    ../Plan-Describer/documenttablesaggregate.hpp
