#-------------------------------------------------
#
# %ProductName%
# 
# %short_description%
#
# @author %author%
#
##-------------------------------------------------

QT       += core gui%QtNetwork%%QtDBus%%QtSQL%%QtWebkit%%OpenGL%
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app

win32   {
    TARGET = "%ProductName%"

    SOURCES += qtwin/qtwin.cpp
    HEADERS += qtwin/qtwin.h 

    RC_FILE = %ProjectName%.rc
}

macx   { 
    TARGET = "%ProductName%"

    # Mac App store requirements: Intel only, 10.6.6 minimum, and custom icon
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.6
    ICON = icons/application-%ProjectName%.icns
    QMAKE_INFO_PLIST = Info.plist
}

linux-*   {
    TARGET = %ProjectName%
    
    target.path = /usr/bin
    icon.path = /usr/share/pixmaps
    icon.files = icons/application-%ProjectName%.png
    desktop.path = /usr/share/applications
    desktop.files = application-%ProjectName%.desktop

    INSTALLS += target icon desktop 
}


SOURCES += main.cpp\
        mainwindow.cpp \

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += resources.qrc

OTHER_FILES += application.desktop \
               icons/application-%ProjectName%.svg \
               icons/application-%ProjectName%.png \
               icons/application-%ProjectName%.icns \
               icons/%ProjectName%.ico \
               %ProjectName%.rc \
               Info.plist \
               README.md
