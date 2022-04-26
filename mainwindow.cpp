#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Notes");

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../../../../Notes/testDB.db");
    if (db.open())
    {
        qDebug("Database is opened");
    }
    else
    {
        qDebug("Error! Database is not opened!");
    }

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE IF NOT EXISTS notes (name TEXT, text TEXT);");

    model = new QSqlTableModel(this, db);
    model->setTable("notes");

    model->select();
    ui->tableView->setModel(model);

    ui->noteTitle->setToolTip("Enter the title of the note");
    ui->textEdit->setToolTip("Enter the content of the note. To save the note press button 'Create note'");
}

MainWindow::~MainWindow()
{
    db.close();
    delete query;
    delete model;
    delete ui;
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
    title = index.sibling(row, 0).data().toString();
    text = index.sibling(row, 1).data().toString();
    ui->noteTitle->setText(title);
    ui->textEdit->setText(text);
}

void MainWindow::on_ButtonCreateNote_clicked()
{
    QString new_title = ui->noteTitle->text();
    QString new_text = ui->textEdit->toPlainText();
    QString command = "INSERT INTO notes VALUES ('" + new_title
            + "', '" + new_text + "');";

    if (query->exec(command))
    {
        qDebug("The note is inserted successfully");
    }
    else
    {
        qDebug("Error! The note is not inserted!");
    }
    model->select();
    ui->tableView->setModel(model);
    ui->noteTitle->clear();
    ui->textEdit->clear();
}


void MainWindow::on_ButtonSaveOpenedNote_clicked()
{
    QString new_title = ui->noteTitle->text();
    QString new_text = ui->textEdit->toPlainText();
    QString command = "UPDATE notes SET name='" + new_title
            + "', text='" + new_text + "' WHERE name='" + title + "';";

    if (query->exec(command))
    {
        qDebug("The table is updated successfully");
    }
    else
    {
        qDebug("Error! The table is not updated!");
    }
    model->select();
    ui->tableView->setModel(model);
    ui->noteTitle->clear();
    ui->textEdit->clear();
}


void MainWindow::on_ButtonDelete_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("You are trying to delete the note");
    msgBox.setInformativeText("Do you want to delete the note?");
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    switch (ret)
    {
      case QMessageBox::Yes:
          model->removeRow(row);
          model->select();
          ui->tableView->setModel(model);
          ui->noteTitle->clear();
          ui->textEdit->clear();
          break;
      default:
          break;
    }
}

void MainWindow::on_ButtonPlus_clicked()
{
    ui->noteTitle->clear();
    ui->textEdit->clear();
}

