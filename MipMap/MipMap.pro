######################################################################
# Automatically generated by qmake (2.01a) Thu Jan 24 19:42:29 2013
######################################################################

TEMPLATE = app
TARGET = MipMap
CONFIG -= app_bundle
DEPENDPATH += .
INCLUDEPATH += .

QMAKE_CXXFLAGS+=$$system(/opt/local/bin/Magick++-config --cppflags )
LIBS+=$$system(/opt/local/bin/Magick++-config --ldflags --libs )
macx:CONFIG+=c++11
macx:INCLUDEPATH+=/opt/ImageMagick/include/ImageMagick-6/
macx:INCLUDEPATH+=/usr/local/include
macx:LIBS+= -L/opt/ImageMagick/lib/ -lMagick++-6.Q16 -lc++
macx:QMAKE_CXXFLAGS+= -std=c++11 -stdlib=libc++

# Input
SOURCES += MipMap.cpp