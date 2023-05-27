#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include <QObject>
#include <QPushButton>
#include <QTableWidget>
#include <QWidget>

class ButtonHandler : public QObject {
public:
    explicit ButtonHandler(QTableWidget *input_table,
                           QTableWidget *output_table, QPushButton *add_input,
                           QPushButton *add_output, QPushButton *add_term,
                           QPushButton *remove_input,
                           QPushButton *remove_output,
                           QPushButton *remove_term);

public slots:
    void addInput();
    void addOutput();
    void addTerm();
    void deleteInput();
    void deleteOutput();
    void deleteTerm();
    void changeInput(QTableWidgetItem *index);
    void changeOutput(QTableWidgetItem *index);

private:
    QTableWidget *m_input_table;
    QTableWidget *m_output_table;
    QPushButton *m_add_input;
    QPushButton *m_add_output;
    QPushButton *m_add_term;
    QPushButton *m_remove_input;
    QPushButton *m_remove_ouput;
    QPushButton *m_remove_term;

private:
    unsigned m_inputs{1};
    unsigned m_outputs{1};
    unsigned m_terms{1};
};

#endif  // BUTTONHANDLER_H
