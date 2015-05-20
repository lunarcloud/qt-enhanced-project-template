#include <QApplication>
#include "mainwindow.h"

#ifdef Q_OS_WIN
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

#ifdef Q_OS_WIN
    if (QtWin::isCompositionEnabled()) {
            QtWin::extendFrameIntoClientArea(&window, -1, -1, -1, -1);
            window.setAttribute(Qt::WA_TranslucentBackground, true);
            window.setAttribute(Qt::WA_NoSystemBackground, false);
            window.setStyleSheet("MainWindow { background: transparent; }");
        } else {
            QtWin::resetExtendedFrame(&window);
            window.setAttribute(Qt::WA_TranslucentBackground, false);
            //window.setStyleSheet(QString("MainWindow { background: %1; }").arg(QtWin::realColorizationColor().name()));
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
