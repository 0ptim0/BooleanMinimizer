#include "buttonhandler.h"

ButtonHandler::ButtonHandler(QTableWidget *table, QPushButton *add_input,
                             QPushButton *add_output, QPushButton *add_term,
                             QPushButton *remove_input,
                             QPushButton *remove_output,
                             QPushButton *remove_term)
    : m_table(table),
      m_add_input(add_input),
      m_add_output(add_output),
      m_add_term(add_term),
      m_remove_input(remove_input),
      m_remove_ouput(remove_output),
      m_remove_term(remove_term),
      m_inputs(1),
      m_outputs(1),
      m_terms(2) {}

bool ButtonHandler::increase(ButtonType type) {
    switch (type) {
        case INPUT:
            m_inputs++;
            break;
        case OUTPUT:
            m_outputs++;
            break;
        case TERM:
            m_terms++;
            break;
        default:
            return false;
    }
    return true;
}

bool ButtonHandler::reduce(ButtonType type) {
    switch (type) {
        case INPUT:
            if (m_inputs == 1) {
                return false;
            }
            m_inputs--;
            break;
        case OUTPUT:
            if (m_outputs == 1) {
                return false;
            }
            m_outputs--;
            break;
        case TERM:
            if (m_terms == 2) {
                return false;
            }
            m_terms--;
            break;
        default:
            return false;
    }
    return true;
}

void ButtonHandler::addInput() {
    if (increase(INPUT)) {
        m_table->insertColumn(m_inputs - 1);
        m_table->setHorizontalHeaderItem(
            m_inputs - 1,
            new QTableWidgetItem(QStringLiteral("X%1").arg(m_inputs)));
    }
}

void ButtonHandler::addOutput() {
    if (increase(OUTPUT)) {
        m_table->insertColumn(m_inputs - 1 + m_outputs);
        m_table->setHorizontalHeaderItem(
            m_inputs - 1 + m_outputs,
            new QTableWidgetItem(QStringLiteral("Y%1").arg(m_outputs)));
    }
}

void ButtonHandler::addTerm() {
    if (increase(TERM)) {
        m_table->insertRow(m_terms - 1);
    }
}

void ButtonHandler::deleteInput() {
    if (reduce(INPUT)) {
        m_table->removeColumn(m_inputs);
    }
}

void ButtonHandler::deleteOutput() {
    if (reduce(OUTPUT)) {
        m_table->removeColumn(m_inputs + m_outputs);
    }
}

void ButtonHandler::deleteTerm() {
    if (reduce(TERM)) {
        m_table->removeRow(m_terms);
    }
}
