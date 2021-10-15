#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->plainTextEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbrir_triggered()
{
    QFile archivo;
    QTextStream io;
    QString nombreArchivo;

    nombreArchivo = QFileDialog::getOpenFileName(this, "Abir");

    // Preguntar que el nombre sea valido
    if(nombreArchivo.isEmpty())
        return;

    archivo.setFileName(nombreArchivo);
    archivo.open(QIODevice::ReadOnly | QIODevice::Text);

    if(!archivo.isOpen()) {
        QMessageBox::critical(this, "Error", archivo.errorString());
        return;
    }

    // Si se abre correctamente
    io.setDevice(&archivo);
    ui->plainTextEdit->setPlainText(io.readAll());

    archivo.flush();
    archivo.close();
}

void MainWindow::on_actionGuardar_como_triggered()
{
    QFile archivo;
    QTextStream io;
    QString nombreArchivo;

    nombreArchivo = QFileDialog::getSaveFileName(this, "Guardar");

    if(nombreArchivo.isEmpty())
        return;

    archivo.setFileName(nombreArchivo);
    archivo.open(QIODevice::WriteOnly | QIODevice::Text);

    if(!archivo.isOpen()) {
        QMessageBox::critical(this, "Error", archivo.errorString());
        return;
    }

    // Si se logra guardar
    io.setDevice(&archivo);
    io <<ui->plainTextEdit->toPlainText();

    archivo.close();
}

void MainWindow::on_actionQuitar_triggered()
{
    close();
}

void MainWindow::on_actionCopiar_triggered()
{
    ui->plainTextEdit->copy();
}

void MainWindow::on_actionCortar_triggered()
{
    ui->plainTextEdit->cut();
}

void MainWindow::on_actionPegar_triggered()
{
    ui->plainTextEdit->paste();
}

void MainWindow::on_actionAcerca_de_triggered()
{
    QMessageBox::aboutQt(this, "Qt");
}
