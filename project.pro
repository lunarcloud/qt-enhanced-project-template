#-------------------------------------------------
#
# %{ProductName}
#
# %{short_description}
#
# @author %{author}
#
##-------------------------------------------------

QT += core gui widgets
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

linux:!android   {
    QT += dbus

    target.path = /usr/bin
    icon.path = /usr/share/pixmaps
    icon.files = icons/application-%{ProjectName}.png
    desktop.path = /usr/share/applications
    desktop.files = application-%{ProjectName}.desktop

    INSTALLS += target icon desktop
}

android {
    #QT += androidextras
    TARGET = %{ProjectName}
    INSTALLS += target
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
	
	DISTFILES += \\
		android/AndroidManifest.xml \\
		android/res/values/libs.xml \\
		android/build.gradle
}

SOURCES += main.cpp \\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += resources.qrc

OTHER_FILES +=  application.desktop \\
                icons/application-%{ProjectName}.svg \\
                icons/application-%{ProjectName}.png \\
                icons/application-%{ProjectName}.icns \\
                icons/%{ProjectName}.ico \\
                %{ProjectName}.rc \\
                Info.plist \\
                README.md
