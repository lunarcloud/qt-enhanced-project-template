#include <QApplication>
#include "mainwindow.h"

#ifdef QT_WINEXTRAS_LIB
    #include <QWinFunctions>
#endif

#ifdef Q_OS_LINUX
    #include <QtDBus>
#endif


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon(":/app/icons/application-%ProjectName%.png"));
    QCoreApplication::setOrganizationName("%Company%");
    QCoreApplication::setOrganizationDomain("%homepage%");
    QCoreApplication::setApplicationName("%ProductName%");

    MainWindow window;

#ifdef QT_WINEXTRAS_LIB
    if (QtWin::isCompositionEnabled()) {
        QtWin::extendFrameIntoClientArea(&window);
        window.setContentsMargins(0, 0, 0, 5);
    }
#endif

#ifdef Q_OS_LINUX
    QDBusMessage signal = QDBusMessage::createSignal("/", "com.canonical.Unity.LauncherEntry", "Update");
    signal << "application://%ProductName%.desktop";
    QVariantMap setProperty;
    setProperty.insert("count", qint64(0));
    setProperty.insert("count-visible", false);
    setProperty.insert("progress", double(0.00));
    setProperty.insert("progress-visible", false);
    setProperty.insert("urgent", false);
    signal << setProperty;
    QDBusConnection::sessionBus().send(signal);
#endif

    window.show();

    return a.exec();
}
