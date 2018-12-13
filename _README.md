README
=======

Windows
----------
Blur behind is enabled, extending the glass to the toolbars, an rc file and an ico style icon.

### Deployment
  1. Use this tool http://doc.qt.io/qt-5/windows-deployment.html
  2. Use dependency walker if windeployqt missed DLLs: http://www.dependencywalker.com/
  3. Then use an installer maker, I suggest NSIS (http://http://nsis.sourceforge.net/)
  3. Submit to store or manually distribute.

OS X
----------
For Mac, an empty menu to add actions to is included, which will show up as the dock's menu.
There's an included icns file.

### Deployment
  1. Build in release mode
  2. Use this tool: http://doc.qt.io/qt-5/macos-deployment.html#macdeploy
  3. If you want to make it more professional, you can make the DMG yourself: http://el-tramo.be/guides/fancy-dmg
  3. Submit to store or manually distribute.

Ubuntu
----------
A cmake-style debian directory was premade for you.
There's also a .desktop file, so when you install the deb you've made it'll show up in the desktop menu.
There's an included png icon file.

### Deployment
  1. `sudo apt-get install build-essential autoconf automake autotools-dev dh-make debhelper devscripts fakeroot xutils lintian pbuilder cdbs`
  2. Update the changelog file: https://wiki.ubuntu.com/PackagingGuide/Complete#changelog
  3. `cd PROJECTDIR && debuild --no-tgz-check`
  4. `make clean`
  5. Submit to ppa / repos or manually distribute.

Android
----------
There is the minimum files required to provide an App with a name and icon.

### Deployment
  1. Build in release mode for your target Architecture.
  2. Copy the APK
  3. Submit to stores or manually distribute.

Icons
----------
PNG: Any drawing program
* http://www.gimp.org/

ICNS: Convert from PNG
* sudo apt-get install icnsutils
* http://www.img2icnsapp.com/

ICO: Convert from PNG
* http://www.pngtoico.com/
