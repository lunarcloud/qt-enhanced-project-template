README
------------------------------

WINDOWS 
----------
Blur behind is enabled, extending the glass to the toolbars, and other Windows sexiness from here: http://labs.qt.nokia.com/2009/09/15/using-blur-behind-on-windows/
There's also an rc file and ico.

DEPLOYMENT:
    Use dependency walker to find the DLL files you'll need to include: http://www.dependencywalker.com/
    Then use an installer maker, I suggest Inno Setup due to it being easy: http://www.jrsoftware.org/isinfo.php

Mac OSX 
----------
For Mac, an empty menu to add actions to is included, which will show up as the dock's menu.
Unified title and toolbar is enabled, creating the very mac effect of your toolbars being on the outside of the app, like in Finder or iTunes.
There's an included icns file.

DEPLOYMENT:
    Run the app in Qt Creator in "Release" mode.
    Open Terminal.app 
    cd to your folder ("cd /Users/sam/Source/projectx-build-desktop")
    run "macdeployqt -dmg ProjectX.app"

    if you want to make it more professional, you can make the DMG yourself: http://el-tramo.be/guides/fancy-dmg

Kubuntu / Ubuntu / Debian
----------
A cmake-style debian directory was premade for you.
There's also a .desktop file, so when you install the deb you've made it'll show up in the gnome/kde menu.
There's an included png file.

DEPLOYMENT:
    First ensure that the required software is installed.
        
        sudo apt-get install build-essential autoconf automake autotools-dev dh-make debhelper devscripts fakeroot xutils lintian pbuilder cdbs

    If this template was installed via package, then these should already be installed as dependencies.
    Next, crucial: update the changelog file: 
        
        https://wiki.ubuntu.com/PackagingGuide/Complete#changelog

    Then, we simply cd to the project's directory and run:

        debuild --no-tgz-check

    This will create unnecessary files, some of which can be cleared out by running

        make clean

ICONS
----------
PNG: Any drawing program
    http://www.gimp.org/
ICNS: Convert from PNG 
    sudo apt-get install icnsutils
    http://www.img2icnsapp.com/
ICO: Convert from PNG
    http://www.pngtoico.com/