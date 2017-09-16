#-------------------------------------------------
#
# %{ProductName}
#
# %{short_description}
#
# @author %{author}
#
##-------------------------------------------------

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
TARGET = "%{ProductName}"

win32   {
    QT += winextras

    RC_FILE = %{ProjectName}.rc
}

macx   {
    QT += macextras

    ICON = icons/application-%{ProjectName}.icns
    QMAKE_INFO_PLIST = Info.plist
}

linux-*   {
    QT += dbus

    target.path = /usr/bin
    icon.path = /usr/share/pixmaps
    icon.files = icons/application-%{ProjectName}.png
    desktop.path = /usr/share/applications
    desktop.files = application-%{ProjectName}.desktop

    INSTALLS += target icon desktop
}

SOURCES += main.cpp\
        mainwindow.cpp \

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += resources.qrc

OTHER_FILES +=  application.desktop \
                icons/application-%{ProjectName}.svg \
                icons/application-%{ProjectName}.png \
                icons/application-%{ProjectName}.icns \
                icons/%{ProjectName}.ico \
                %{ProjectName}.rc \
                Info.plist \
                README.md
