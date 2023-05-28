#include "mainwindow.h"

#include <QObject>
#include <QPushButton>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->input_plus, &QPushButton::clicked, this, &MainWindow::addInput);
    connect(ui->output_plus, &QPushButton::clicked, this,
            &MainWindow::addOutput);
    connect(ui->term_plus, &QPushButton::clicked, this, &MainWindow::addTerm);
    connect(ui->input_minus, &QPushButton::clicked, this,
            &MainWindow::deleteInput);
    connect(ui->output_minus, &QPushButton::clicked, this,
            &MainWindow::deleteOutput);
    connect(ui->term_minus, &QPushButton::clicked, this,
            &MainWindow::deleteTerm);

    connect(ui->input_table, &QTableWidget::itemChanged, this,
            &MainWindow::changeInput);
    connect(ui->output_table, &QTableWidget::itemChanged, this,
            &MainWindow::changeOutput);

    boolean_minimizer = new BooleanMinimizer();
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

void MainWindow::print(std::vector<QString> &vec) {
    ui->output_display->clear();
    for (auto &c : vec) {
        ui->output_display->append(c);
    }
}

void MainWindow::addInput() {
    ui->input_table->insertColumn(m_inputs++);
    ui->input_table->setHorizontalHeaderItem(
        m_inputs - 1,
        new QTableWidgetItem(QStringLiteral("X%1").arg(m_inputs)));

    boolean_minimizer->addInput();
}

void MainWindow::addOutput() {
    ui->output_table->insertColumn(m_outputs++);
    ui->output_table->setHorizontalHeaderItem(
        m_outputs - 1,
        new QTableWidgetItem(QStringLiteral("Y%1").arg(m_outputs)));

    boolean_minimizer->addOutput();
}

void MainWindow::addTerm() {
    ui->input_table->insertRow(m_terms);
    ui->output_table->insertRow(m_terms);
    m_terms++;

    boolean_minimizer->addTerm();
}

void MainWindow::deleteInput() {
    if (m_inputs == 1) return;
    ui->input_table->removeColumn(--m_inputs);

    boolean_minimizer->deleteInput();
}

void MainWindow::deleteOutput() {
    if (m_outputs == 1) return;
    ui->output_table->removeColumn(--m_outputs);

    boolean_minimizer->deleteOutput();
}

void MainWindow::deleteTerm() {
    if (m_terms == 1) return;
    m_terms--;
    ui->input_table->removeRow(m_terms);
    ui->output_table->removeRow(m_terms);

    boolean_minimizer->deleteTerm();
}

void MainWindow::changeInput(QTableWidgetItem *index) {
    bool check = false;
    int value = index->text().toInt(&check);
    if (!check || (value != 0 && value != 1)) {
        std::string a = index->text().toStdString();
        if (a.size() == 1 && (a[0] == '-')) {
            index->setText("-");
        } else {
            index->setText("0");
        }
    }

    boolean_minimizer->changeInput(index);
    auto s = boolean_minimizer->calculate();
    print(s);
}

void MainWindow::changeOutput(QTableWidgetItem *index) {
    bool check = false;
    int value = index->text().toInt(&check);
    if (!check || (value != 0 && value != 1)) {
        index->setText("0");
    }

    boolean_minimizer->changeOutput(index);
    auto s = boolean_minimizer->calculate();
    print(s);
}
