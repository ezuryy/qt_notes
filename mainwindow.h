#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QLineEdit>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_tableView_clicked(const QModelIndex &index);

    void on_ButtonCreateNote_clicked();

    void on_ButtonSaveOpenedNote_clicked();

    void on_ButtonDelete_clicked();

    void on_ButtonPlus_clicked();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *model;

    int row;
    QString title, text;
};
#endif // MAINWINDOW_H
