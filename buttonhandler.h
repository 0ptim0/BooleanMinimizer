#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include <QObject>
#include <QPushButton>
#include <QTableWidget>
#include <QWidget>

class ButtonHandler : public QObject {
public:
    ButtonHandler(QTableWidget *table, QPushButton *add_input,
                  QPushButton *add_output, QPushButton *add_term,
                  QPushButton *remove_input, QPushButton *remove_output,
                  QPushButton *remove_term);

public slots:
    void addInput();
    void addOutput();
    void addTerm();
    void deleteInput();
    void deleteOutput();
    void deleteTerm();

private:
    QTableWidget *m_table;
    QPushButton *m_add_input;
    QPushButton *m_add_output;
    QPushButton *m_add_term;
    QPushButton *m_remove_input;
    QPushButton *m_remove_ouput;
    QPushButton *m_remove_term;

private:
    unsigned m_inputs;
    unsigned m_outputs;
    unsigned m_terms;

private:
    enum ButtonType {
        INPUT = 0,
        OUTPUT = 1,
        TERM = 2,
    };

private:
    bool increase(ButtonType type);
    bool reduce(ButtonType type);
};

#endif  // BUTTONHANDLER_H
