#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#ifdef Q_OS_LINUX
    #include <QtDBus>
#endif

namespace Ui {
class MainWindow;
}

QT_FORWARD_DECLARE_CLASS(QWinTaskbarButton)

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *e);

private:
    Ui::MainWindow *ui;
    void readSettings();
#ifdef Q_OS_WIN32
    QWinTaskbarButton *taskbarButton;
#endif

private slots:
    void about();
    void writeSettings();
    void setIconNumber(int);
    void clearIconNumber();

signals:

};

#endif // MAINWINDOW_H

