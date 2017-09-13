#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QMessageBox>

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    #include <QtWidgets>
#endif

#ifdef Q_OS_WIN
    #include <QtWinExtras>
#endif

#ifdef Q_OS_MACX
    #include <QtMac>
    extern void qt_mac_set_dock_menu(QMenu *);
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("%{ProductName}");

#ifdef Q_OS_MACX

    /* Dock Menu */
    QMenu *menu = new QMenu;
    // Add actions to the menu

    qt_mac_set_dock_menu(menu);
#endif

#ifdef Q_OS_WIN
    taskbarButton = new QWinTaskbarButton(this);
    taskbarButton->setWindow(this->windowHandle());
	
    /* Jump List */
    QWinJumpList jumplist;
    //Add categories, tasks, items, and links to the menu
#endif

    connect(ui->actionAbout_Qt,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
    connect(ui->action_About,SIGNAL(triggered()),this,SLOT(about()));
    connect(ui->action_Quit,SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(qApp,SIGNAL(aboutToQuit()),this,SLOT(writeSettings()));

    readSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *e)
{
#ifdef Q_OS_WIN32
    taskbarButton->setWindow(this->windowHandle());
#endif

    e->accept();
}

void MainWindow::about()
{
    QMessageBox::about(this,
                       "About %{ProductName}",
                       QString("<html><b><p>%{short_description}</p></b>")
                       + QString("<p>%{long_description}</p><br>")
                       + QString("Author: %{author} <%{email}><br>")
                       + QString("Homepage: %{homepage}<br>")
                       + QString("License: %{license}<br>")
                       + QString("<b>Copyright &copy; %{year}, %{Company}</b>")
                       );
}

void MainWindow::setIconNumber(int number)
{
#ifdef Q_OS_MACX
    QtMac::setBadgeLabelText(QString::number(number));
#endif

#ifdef Q_OS_WIN
    QString value = QString::number(number);
    if (number > 99) value = "+";
    if (number < -99) value = "-";

    QImage image = QImage(64,64,QImage::Format_ARGB32);
    QPainter painter(&image);
    painter.setBackgroundMode(Qt::TransparentMode);
    painter.setBrush(QBrush(Qt::red));
    painter.drawEllipse(0, 0, 64, 64);
    painter.setPen(Qt::white);

    int fontsize = value == "+" ? 54 : ( value.length() == 1 ? 48 : 32 );
    painter.setFont(QFont("Segoe UI", fontsize, QFont::Bold));

    int antimargin = value == "+" ? -8 : -4;
    painter.drawText(0, antimargin, 64, 64,
                     Qt::AlignCenter|Qt::AlignTop,
                     value);

//    taskbarButton->clearOverlayIcon();
    taskbarButton->setOverlayIcon(QIcon(QPixmap::fromImage(image)));
#endif

#ifdef Q_OS_LINUX
    QDBusMessage signal = QDBusMessage::createSignal("/", "com.canonical.Unity.LauncherEntry", "Update");
    signal << "application://%{ProductName}.desktop";
    QVariantMap setProperty;
    setProperty.insert("count", qint64(number));
    setProperty.insert("count-visible", true);
    setProperty.insert("progress", double(0.00));
    setProperty.insert("progress-visible", false);
    setProperty.insert("urgent", true);
    signal << setProperty;
    QDBusConnection::sessionBus().send(signal);
#endif
}

void MainWindow::clearIconNumber()
{

#ifdef Q_OS_MACX
    QtMac::setBadgeLabelText(QString());
#endif

#ifdef Q_OS_WIN
    taskbarButton->clearOverlayIcon();
#endif

#ifdef Q_OS_LINUX
    QDBusMessage signal = QDBusMessage::createSignal("/", "com.canonical.Unity.LauncherEntry", "Update");
    signal << "application://%{ProductName}.desktop";
    QVariantMap setProperty;
    setProperty.insert("count", qint64(0));
    setProperty.insert("count-visible", false);
    setProperty.insert("progress", double(0.00));
    setProperty.insert("progress-visible", false);
    setProperty.insert("urgent", false);
    signal << setProperty;
    QDBusConnection::sessionBus().send(signal);
#endif
}

void MainWindow::writeSettings()
{
    QSettings settings; // To add settings: settings.setValue(QString("key"),QVariant());
}

void MainWindow::readSettings()
{
    QSettings settings;  //To get settings: QVariant thing = settings.value("key").toQVariant();
}
