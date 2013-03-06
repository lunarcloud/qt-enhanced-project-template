#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("%ProductName%");

#ifdef Q_WS_MAC

    /* Dock Menu */
    QMenu *menu = new QMenu;
    // Add actions to the menu

    extern void qt_mac_set_dock_menu(QMenu *);
    qt_mac_set_dock_menu(menu);
    
    setUnifiedTitleAndToolBarOnMac(true);
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

void MainWindow::about()
{
    QMessageBox::about(this,
                       "About %ProductName%",
                       QString("<html><b><p>%short_description%</p></b>")
                       + QString("<p>%long_description%</p><br>")
                       + QString("Author: %author% <%email%><br>")
                       + QString("Homepage: %homepage%<br>")
                       + QString("License: %license%<br>")
                       + QString("<b>Copyright &copy; %year%, %Company%</b>")
                       );
}

void MainWindow::writeSettings()
{
    QSettings settings; // To add settings: settings.setValue(QString("key"),QVariant());
}

void MainWindow::readSettings()
{
    QSettings settings;  //To get settings: QVariant thing = settings.value("key").toQVariant();
}
