######################################################################
# Automatically generated by qmake (2.01a) Thu Jan 24 19:42:29 2013
######################################################################

TEMPLATE = app
TARGET = SimpleImageWrite
CONFIG -= app_bundle
DEPENDPATH += .
INCLUDEPATH += .

#QMAKE_CXXFLAGS+=$$system(Magick++-config --cppflags )
#LIBS+=$$system(Magick++-config --ldflags --libs )
win32:{
    PRE_TARGETDEPS+=$$(HOMEDRIVE)\\$$(HOMEPATH)\vcpkg\installed\x64-windows\lib\OpenImageIO.lib

    INCLUDEPATH += $(HOMEDRIVE)\$(HOMEPATH)\vcpkg\installed\x64-windows\include
    LIBS += -L$(HOMEDRIVE)\$(HOMEPATH)\vcpkg\installed\x64-windows\lib\ -lOpenImageIO

}
# Input
SOURCES += SimpleImageWrite.cpp
