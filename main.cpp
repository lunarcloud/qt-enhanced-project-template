#include <QtGui/QApplication>
#include "mainwindow.h"

#ifdef Q_WS_WIN
    #include "qtwin/qtwin.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon(":/app/icons/application-%ProjectName%.png"));
    QCoreApplication::setOrganizationName("%Company%");
    QCoreApplication::setOrganizationDomain("%homepage%");
    QCoreApplication::setApplicationName("%ProductName%");
    
    MainWindow window;

#ifdef Q_WS_WIN
    if (QtWin::isCompositionEnabled()) {
        QtWin::extendFrameIntoClientArea(&window);
        window.setContentsMargins(0, 0, 0, 5);
    }
#endif
   
    window.show();

    return a.exec();
}
