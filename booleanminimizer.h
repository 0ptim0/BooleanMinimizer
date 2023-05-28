#ifndef BOOLEANMINIMIZER_H
#define BOOLEANMINIMIZER_H

#include <QObject>
#include <QTextBrowser>
#include <cstdint>
#include <map>
#include <mutex>
#include <set>
#include <vector>

#include "qtablewidget.h"

class BooleanMinimizer : public QObject {
public:
    explicit BooleanMinimizer();
    explicit BooleanMinimizer(std::vector<std::vector<int8_t>> &input,
                              std::vector<std::vector<int8_t>> &output);

public:
    void addInput();
    void addOutput();
    void addTerm();
    void deleteInput();
    void deleteOutput();
    void deleteTerm();
    void changeInput(QTableWidgetItem *index);
    void changeOutput(QTableWidgetItem *index);
    std::vector<QString> calculate();

private:
    std::vector<std::vector<int8_t>> calculateFunction(
        std::vector<int> &indexes);
    void convertToString(std::vector<QString> &str,
                         std::vector<std::vector<std::vector<int8_t>>> &table);
    int compareWithDiff(std::vector<int8_t> &first,
                        std::vector<int8_t> &second);
    bool compareWithAbsorb(std::vector<int8_t> &first,
                           std::vector<int8_t> &second);
    void combine(std::vector<std::vector<int>> &minterms_w_indexes,
                 int number_of_miniterms, int index, int dnf_length,
                 std::set<int> &tmp, std::set<int> &indexes,
                 std::vector<std::set<int>> &minimal_w_indexes);

private:
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
