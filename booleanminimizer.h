#ifndef BOOLEANMINIMIZER_H
#define BOOLEANMINIMIZER_H

#include <QObject>
#include <QTextBrowser>
#include <cstdint>
#include <map>
#include <mutex>
#include <vector>

#include "qtablewidget.h"

class BooleanMinimizer : public QObject {
public:
    explicit BooleanMinimizer(QTextBrowser *output_display);

public slots:
    void addInput();
    void addOutput();
    void addTerm();
    void deleteInput();
    void deleteOutput();
    void deleteTerm();
    void changeInput(QTableWidgetItem *index);
    void changeOutput(QTableWidgetItem *index);

public:
    std::vector<std::vector<std::vector<int8_t>>> getBooleanFunction();

private:
    void calculate();
    std::vector<std::vector<int8_t>> calculateColumn(std::vector<int> &indexes);
    void convertToString(std::vector<QString> &str,
                         std::vector<std::vector<std::vector<int8_t>>> &table);

private:
    QTextBrowser *m_output_display;
    std::vector<std::vector<int8_t>> m_input_table{{1}};
    std::vector<std::vector<int8_t>> m_output_table{{1}};
    std::vector<std::vector<std::vector<int8_t>>> m_boolean_function;
    int m_inputs{1};
    int m_outputs{1};
    int m_terms{1};

private:
    std::mutex mutex;

private:
    void change(std::vector<std::vector<int8_t>> &table,
                QTableWidgetItem *index);
    void update();
};

#endif  // BOOLEANMINIMIZER_H
