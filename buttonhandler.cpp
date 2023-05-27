#include "buttonhandler.h"

ButtonHandler::ButtonHandler(QTableWidget *input_table,
                             QTableWidget *output_table, QPushButton *add_input,
                             QPushButton *add_output, QPushButton *add_term,
                             QPushButton *remove_input,
                             QPushButton *remove_output,
                             QPushButton *remove_term)
    : m_input_table(input_table),
      m_output_table(output_table),
      m_add_input(add_input),
      m_add_output(add_output),
      m_add_term(add_term),
      m_remove_input(remove_input),
      m_remove_ouput(remove_output),
      m_remove_term(remove_term) {}

void ButtonHandler::addInput() {
    m_input_table->insertColumn(m_inputs++);
    m_input_table->setHorizontalHeaderItem(
        m_inputs - 1,
        new QTableWidgetItem(QStringLiteral("X%1").arg(m_inputs)));
}

void ButtonHandler::addOutput() {
    m_output_table->insertColumn(m_outputs++);
    m_output_table->setHorizontalHeaderItem(
        m_outputs - 1,
        new QTableWidgetItem(QStringLiteral("Y%1").arg(m_outputs)));
}

void ButtonHandler::addTerm() {
    m_input_table->insertRow(m_terms);
    m_output_table->insertRow(m_terms);
    m_terms++;
}

void ButtonHandler::deleteInput() {
    if (m_inputs == 1) return;
    m_input_table->removeColumn(--m_inputs);
}

void ButtonHandler::deleteOutput() {
    if (m_outputs == 1) return;
    m_output_table->removeColumn(--m_outputs);
}

void ButtonHandler::deleteTerm() {
    if (m_terms == 1) return;
    m_terms--;
    m_input_table->removeRow(m_terms);
    m_output_table->removeRow(m_terms);
}

void ButtonHandler::changeInput(QTableWidgetItem *index) {
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
}

void ButtonHandler::changeOutput(QTableWidgetItem *index) {
    bool check = false;
    int value = index->text().toInt(&check);
    if (!check || (value != 0 && value != 1)) {
        index->setText("0");
    }
}
