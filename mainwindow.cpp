#include "mainwindow.h"

#include <QObject>
#include <QPushButton>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    button_handler = new ButtonHandler(
        ui->input_table, ui->output_table, ui->input_plus, ui->output_plus,
        ui->term_plus, ui->input_minus, ui->output_minus, ui->term_minus);
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

    connect(ui->input_table, &QTableWidget::itemChanged, button_handler,
            &ButtonHandler::changeInput);
    connect(ui->output_table, &QTableWidget::itemChanged, button_handler,
            &ButtonHandler::changeOutput);

    boolean_minimizer = new BooleanMinimizer(ui->output_display);

    connect(ui->input_plus, &QPushButton::clicked, this,
            (void(MainWindow::*)())(&MainWindow::print));
    connect(ui->output_plus, &QPushButton::clicked, this,
            (void(MainWindow::*)())(&MainWindow::print));
    connect(ui->term_plus, &QPushButton::clicked, this,
            (void(MainWindow::*)())(&MainWindow::print));
    connect(ui->input_minus, &QPushButton::clicked, this,
            (void(MainWindow::*)())(&MainWindow::print));
    connect(ui->output_minus, &QPushButton::clicked, this,
            (void(MainWindow::*)())(&MainWindow::print));
    connect(ui->term_minus, &QPushButton::clicked, this,
            (void(MainWindow::*)())(&MainWindow::print));

    connect(ui->input_table, &QTableWidget::itemChanged, this,
            (void(MainWindow::*)(QTableWidgetItem *))(&MainWindow::print));
    connect(ui->output_table, &QTableWidget::itemChanged, this,
            (void(MainWindow::*)(QTableWidgetItem *))(&MainWindow::print));

    connect(ui->input_plus, &QPushButton::clicked, boolean_minimizer,
            &BooleanMinimizer::addInput);
    connect(ui->output_plus, &QPushButton::clicked, boolean_minimizer,
            &BooleanMinimizer::addOutput);
    connect(ui->term_plus, &QPushButton::clicked, boolean_minimizer,
            &BooleanMinimizer::addTerm);
    connect(ui->input_minus, &QPushButton::clicked, boolean_minimizer,
            &BooleanMinimizer::deleteInput);
    connect(ui->output_minus, &QPushButton::clicked, boolean_minimizer,
            &BooleanMinimizer::deleteOutput);
    connect(ui->term_minus, &QPushButton::clicked, boolean_minimizer,
            &BooleanMinimizer::deleteTerm);

    connect(ui->input_table, &QTableWidget::itemChanged, boolean_minimizer,
            &BooleanMinimizer::changeInput);
    connect(ui->output_table, &QTableWidget::itemChanged, boolean_minimizer,
            &BooleanMinimizer::changeOutput);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::print() {
    ui->output_display->append("Check");
}

void MainWindow::print(QTableWidgetItem *index) {
    ui->output_display->append(QString("Row = %1").arg(index->row()));
    ui->output_display->append(QString("Column = %1").arg(index->column()));
    ui->output_display->append(QString("Value = %1").arg(index->text()));
}
