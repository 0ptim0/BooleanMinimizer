#include "mainwindow.h"

#include <QObject>
#include <QPushButton>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    button_handler = new ButtonHandler(
        ui->truth_table, ui->input_plus, ui->output_plus, ui->term_plus,
        ui->input_minus, ui->output_minus, ui->term_minus);
    connect(ui->input_plus, &QPushButton::clicked, button_handler,
            &ButtonHandler::addInput);
    connect(ui->output_plus, &QPushButton::clicked, button_handler,
            &ButtonHandler::addOutput);
    connect(ui->term_plus, &QPushButton::clicked, button_handler,
            &ButtonHandler::addTerm);
    connect(ui->input_minus, &QPushButton::clicked, button_handler,
            &ButtonHandler::deleteInput);
    connect(ui->output_minus, &QPushButton::clicked, button_handler,
            &ButtonHandler::deleteOutput);
    connect(ui->term_minus, &QPushButton::clicked, button_handler,
            &ButtonHandler::deleteTerm);
}

MainWindow::~MainWindow() {
    delete ui;
}
