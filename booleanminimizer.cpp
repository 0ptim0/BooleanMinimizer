#include "booleanminimizer.h"

#include <iostream>

BooleanMinimizer::BooleanMinimizer(QTextBrowser *output_display)
    : m_output_display(output_display) {}

void BooleanMinimizer::calculate() {
    mutex.lock();
    std::vector<std::vector<int>> indexes(m_outputs);
    std::vector<int> v;
    std::fill(indexes.begin(), indexes.end(), v);

    for (int r_i = 0; r_i < m_output_table.size(); r_i++) {
        for (int r_c = 0; r_c < m_output_table[r_i].size(); r_c++) {
            if (m_output_table[r_i][r_c] == 1) {
                indexes[r_c].push_back(r_i);
            }
        }
    }

    m_boolean_function.clear();
    for (auto &i : indexes) {
        m_boolean_function.push_back(calculateColumn(i));
    }

    std::vector<QString> s;
    convertToString(s, m_boolean_function);
    m_output_display->clear();
    for (auto &c : s) {
        m_output_display->append(c);
    }
    mutex.unlock();
}

std::vector<std::vector<int8_t>> BooleanMinimizer::calculateColumn(
    std::vector<int> &indexes) {
    std::vector<std::vector<int8_t>> vec;
    std::map<std::vector<int8_t>, int> uniq;
    std::multimap<int, std::vector<int8_t>> sorted;
    int prev = 0;

    for (auto &i : indexes) {
        vec.push_back(m_input_table[i]);
    }

    for (int i = 0; i < vec.size(); i++) {
        int ones = 0;
        for (int j = 0; j < vec[i].size(); j++) {
            if (vec[i][j] == 1) {
                ones++;
            }
        }
        prev = ones;
        uniq.insert(std::pair<std::vector<int8_t>, int>(vec[i], ones));
    }

    bool loop = false;
    for (auto &i : uniq) {
        sorted.insert(std::pair<int, std::vector<int8_t>>(i.second, i.first));
        if (i.second - prev == 1) {
            loop = true;
        }
        prev = i.second;
    }

    while (0) {
    }

    return vec;
}

std::vector<std::vector<std::vector<int8_t>>>
BooleanMinimizer::getBooleanFunction() {
    mutex.lock();
    std::vector<std::vector<std::vector<int8_t>>> tmp = m_boolean_function;
    mutex.unlock();
    return tmp;
}

void BooleanMinimizer::convertToString(
    std::vector<QString> &str,
    std::vector<std::vector<std::vector<int8_t>>> &table) {
    for (int y = 0; y < table.size(); y++) {
        //        if (table[y].size() >= 1) {
        str.push_back(QString("Y%1 = ").arg(y + 1));
        //        }
        for (int t = 0; t < table[y].size(); t++) {
            for (int m = 0; m < table[y][t].size(); m++) {
                if (table[y][t][m] == 1) {
                    str[y].append(QString("X%1").arg(m + 1));
                } else if (table[y][t][m] == 0) {
                    str[y].append(QString("X̄%1").arg(m + 1));
                }
            }
            if (t + 1 != table[y].size()) {
                str[y].append(QString(" + "));
            }
        }
    }
}

void BooleanMinimizer::addInput() {
    mutex.lock();
    for (auto &r : m_input_table) {
        r.push_back(0);
    }
    m_inputs++;
    mutex.unlock();
    calculate();
}

void BooleanMinimizer::addOutput() {
    std::vector<int8_t> vec;
    for (auto &r : m_output_table) {
        r.push_back(0);
    }
    m_outputs++;
    mutex.unlock();
    calculate();
}

void BooleanMinimizer::addTerm() {
    mutex.lock();
    std::vector<int8_t> c(m_inputs);
    std::fill(c.begin(), c.end(), 0);
    m_input_table.push_back(c);
    c.resize(m_outputs);
    std::fill(c.begin(), c.end(), 0);
    m_output_table.push_back(c);
    m_terms++;
    mutex.unlock();
    calculate();
}

void BooleanMinimizer::deleteInput() {
    if (m_inputs == 1) return;
    mutex.lock();
    for (auto &r : m_input_table) {
        r.erase(r.end() - 1);
    }
    m_inputs--;
    mutex.unlock();
    calculate();
}

void BooleanMinimizer::deleteOutput() {
    if (m_outputs == 1) return;
    mutex.lock();
    for (auto &r : m_output_table) {
        r.erase(r.end() - 1);
    }
    m_outputs--;
    mutex.unlock();
    calculate();
}

void BooleanMinimizer::deleteTerm() {
    if (m_terms == 1) return;
    mutex.lock();
    m_input_table.erase(m_input_table.end() - 1);
    m_output_table.erase(m_output_table.end() - 1);
    m_terms--;
    mutex.unlock();
    calculate();
}

void BooleanMinimizer::change(std::vector<std::vector<int8_t>> &table,
                              QTableWidgetItem *index) {
    bool check = false;
    int rv = 0;
    int value = index->text().toInt(&check);
    if (check && (value == 0 || value == 1)) {
        if (value == 1) {
            rv = 1;
        }
    } else {
        std::string a = index->text().toStdString();
        if (a.size() == 1 && (a[0] == '-')) {
            rv = -1;
        }
    }
    mutex.lock();
    if (index->row() <= table.size() && index->column() <= table[0].size()) {
        table[index->row()][index->column()] = rv;
    }
    mutex.unlock();
    calculate();
}

void BooleanMinimizer::changeInput(QTableWidgetItem *index) {
    change(m_input_table, index);
}

void BooleanMinimizer::changeOutput(QTableWidgetItem *index) {
    change(m_output_table, index);
}
