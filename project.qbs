/*-------------------------------------------------
*
* %ProductName%
*
* %short_description%
*
* @author %author%
*
*-------------------------------------------------*/
import qbs 1.0

Application {
	name: "%ProductName%"
    files: [
        "main.cpp",
        "mainwindow.cpp",
        "mainwindow.h",
        "mainwindow.ui",
        "resources.qrc",
        "icons/application-%ProjectName%.svg",
        "README.md"
    ]
    Group {
        condition: qbs.targetOS.contains("windows")
        name: "Windows"
        files: ["icons/%ProjectName%.ico", "%ProjectName%.rc"]
    }
    Group {
        condition: qbs.targetOS.contains("linux")
        name: "Linux"
        Application.targetName: "%ProjectName%"
        files: ["application.desktop", "icons/application-%ProjectName%.png", "application-%ProjectName%.desktop"]
        //target.path = /usr/bin
        //icon.path = /usr/share/pixmaps
        //icon.files = icons/application-%ProjectName%.png
        //desktop.path = /usr/share/applications
        //desktop.files = application-%ProjectName%.desktop
    }
    Group {
        condition: qbs.targetOS.contains("macos")
        name: "macOS"
        files: ["Info.plist", "icons/application-%ProjectName%.icns"]
        bundle.infoPlistFile: "Info.plist"
		/* Following is not tested
        dmg.backgroundColor: "#41cd52"
		dmg.badgeVolumeIcon: true
		dmg.iconPositions: [
			{"x": 200, "y": 200, "path": "Cocoa Application.app"},
			{"x": 400, "y": 200, "path": "Applications"}
		]
		dmg.windowX: 420
		dmg.windowY: 250
		dmg.windowWidth: 600
		dmg.windowHeight: 422 // this *includes* the macOS title bar height of 22
		dmg.iconSize: 64*/
    }
    Depends {
        condition: qbs.targetOS.contains("macos")
        name: "bundle"
    }
    Depends {
        condition: qbs.targetOS.contains("macos")
        name: "Qt.macextras"
    }
    Depends {
        condition: qbs.targetOS.contains("windows")
        name: "Qt.winextras"
    }
    Depends {
        condition: qbs.targetOS.contains("linux")
        name: "Qt.dbus"
    }
    Depends { name: "Qt"; submodules: ["core", "gui", "widgets"] }
    Depends { name: "cpp" }
}
