######################################################################
# Automatically generated by qmake (3.1) Wed Dec 5 23:02:32 2018
######################################################################

TEMPLATE = app
TARGET = build/cwk2
OBJECTS_DIR = generated_files
MOC_DIR = generated_files

INCLUDEPATH += . src inc /opt/local/include

QT += widgets opengl openglextensions gui

LIBS += -lGLU -lglut -lGL

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += inc/*
SOURCES += src/*
