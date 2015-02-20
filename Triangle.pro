TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
CONFIG += std=c++11

include(deployment.pri)
qtcAddDeployment()

