#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QMessageBox>
#include <QtWidgets>

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

    /* Setup Actions */
    ui->action_About->setIcon(QIcon::fromTheme("help-about", this->style()->standardIcon(QStyle::SP_DialogHelpButton)));
    ui->action_Quit->setIcon(QIcon::fromTheme("application-exit"));

    /* Setup Main Toolbar */
    ui->mainToolBar->addAction(ui->action_About);
	
#ifdef Q_OS_MACX

    /* Dock Menu */
    QMenu *menu = new QMenu;
    // Add actions to the menu

    qt_mac_set_dock_menu(menu);
#endif

#ifdef Q_OS_WIN
    taskbarButton = new QWinTaskbarButton(this);
	
    /* Jump List */
    QWinJumpList jumplist;
    //Add categories, tasks, items, and links to the menu
#endif

    connect(ui->actionAbout_Qt, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(ui->action_About, &QAction::triggered, this, &MainWindow::about);
    connect(ui->action_Quit, &QAction::triggered, qApp, &QApplication::quit);
    connect(qApp, &QApplication::aboutToQuit, this, &MainWindow::writeSettings);

    readSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *e)
{
#ifdef Q_OS_WIN32
    taskbarButton->setWindow(windowHandle());
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
#ifdef Q_OS_ANDROID
    Q_UNUSED( number )
#endif

#ifdef Q_OS_MACX
    QtMac::setBadgeLabelText(QString::number(number));
#endif

#ifdef Q_OS_WIN
    QString value = QString::number(number);
    if (number > 99) value = "+";
    if (number < -99) value = "-";

    const int size = 64;
    const int edgeMargin = abs(number) > 99 ? 8 : 4;
    const int fontsize = size - 2 - ( abs(number) > 99 ? 0 : edgeMargin * 4 );
    QImage image = QImage(size, size, QImage::Format_ARGB32);
	{
		QPainter painter(&image);
        painter.setRenderHint( QPainter::Antialiasing , true );
		painter.setBackgroundMode(Qt::TransparentMode);
		painter.setBrush(QBrush(Qt::red));
		painter.drawEllipse(1, 1, size-2, size-2);
		painter.setPen(Qt::white);

        QFont font = QApplication::font("QMenu"); /* Default UI font */
        font.setPixelSize(fontsize);
        font.setBold(true);
        painter.setFont(font);

        painter.drawText(0, -1 * edgeMargin, size, size, Qt::AlignCenter, value);
	}	
    taskbarButton->setOverlayIcon(QIcon(QPixmap::fromImage(image, Qt::ImageConversionFlag::AutoColor)));
#endif

#ifdef Q_OS_LINUX
#ifndef Q_OS_ANDROID
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
#ifndef Q_OS_ANDROID
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
