#include "booleanminimizer.h"

#include <iostream>

BooleanMinimizer::BooleanMinimizer() {}

BooleanMinimizer::BooleanMinimizer(std::vector<std::vector<int8_t>> &input,
                                   std::vector<std::vector<int8_t>> &output)
    : m_input_table(input),
      m_output_table(output),
      m_inputs(input.size() > 0 ? input[0].size() : 0),
      m_outputs(output.size() > 0 ? output[0].size() : 0) {}

std::vector<QString> BooleanMinimizer::calculate() {
    mutex.lock();

    std::vector<std::vector<std::vector<int8_t>>> m_boolean_function;
    calculateOutputs(m_boolean_function);

    std::vector<QString> s;
    convertToString(s, m_boolean_function);

    mutex.unlock();
    return s;
}

void BooleanMinimizer::calculateOutputs(
    std::vector<std::vector<std::vector<int8_t>>> &boolean_function) {
    for (int r_c = 0, r_i = 0;
         r_i < m_output_table.size() && r_c < m_output_table[r_i].size();
         r_c++) {
        std::vector<std::vector<int8_t>> input;
        std::vector<std::vector<int8_t>> output;
        for (; r_i < m_output_table.size(); r_i++) {
            if (m_output_table[r_i][r_c] == 1) {
                input.push_back(m_input_table[r_i]);
            }
        }
        r_i = 0;
        calculateOutput(input, output);
        boolean_function.push_back(output);
    }
}

void BooleanMinimizer::calculateOutput(
    const std::vector<std::vector<int8_t>> &input,
    std::vector<std::vector<int8_t>> &output) {
    std::map<std::vector<int8_t>, int> uniq;
    std::multimap<int, std::vector<int8_t>> sorted;

    for (int i = 0; i < input.size(); i++) {
        int ones = 0;
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] == 1) {
                ones++;
            }
        }
        uniq.insert(std::pair<std::vector<int8_t>, int>(input[i], ones));
    }

    for (auto &i : uniq) {
        sorted.insert(std::pair<int, std::vector<int8_t>>(i.second, i.first));
    }

    bool loop = true;
    std::multimap<int, std::vector<int8_t>> pmap(sorted);
    std::multimap<int, std::vector<int8_t>> nmap;
    std::vector<std::vector<int8_t>> simple;

    while (loop) {
        std::map<std::vector<int8_t>, bool> indexes;

        for (auto it = pmap.begin(); it != pmap.end(); it++) {
            indexes[it->second] = false;
        }

        for (auto it_g1 = pmap.begin(); it_g1 != pmap.end(); it_g1++) {
            auto it_g2 = pmap.find(it_g1->first + 1);
            if (it_g2 == pmap.end()) {
                break;
            }
            auto val = *it_g1;
            for (; it_g2 != pmap.end(); it_g2++) {
                int index = 0;
                if ((index = compareWithDiff(val.second, it_g2->second)) >= 0) {
                    auto new_val = val.second;
                    new_val[index] = -1;
                    nmap.insert(std::pair<int, std::vector<int8_t>>(val.first,
                                                                    new_val));
                    indexes[val.second] = true;
                    indexes[it_g2->second] = true;
                }
            }
        }
        for (auto &i : indexes) {
            if (!i.second) {
                simple.push_back(i.first);
            }
        }
        if (nmap.size() == 0) {
            loop = false;
        } else {
            pmap = nmap;
            nmap.clear();
        }
    }

    std::vector<std::vector<int>> kernel(simple.size());
    for (int i = 0; i < simple.size(); i++) {
        int j = 0;
        for (auto &b : sorted) {
            if (compareWithAbsorb(simple[i], b.second)) {
                kernel[i].push_back(j);
            }
            j++;
        }
    }

    std::set<int> tmp;
    std::set<int> ind;
    std::vector<std::set<int>> minimal_w_indexes;
    for (int i = 1; i <= simple.size(); i++) {
        combine(kernel, i, 0, sorted.size(), tmp, ind, minimal_w_indexes);
    }

    if (minimal_w_indexes.size() > 0) {
        int min_ind = 0;
        int min_size = minimal_w_indexes[min_ind].size();
        for (int i = 1; i < minimal_w_indexes.size(); i++) {
            if (minimal_w_indexes[i].size() <= min_size) {
                min_size = minimal_w_indexes.size();
                min_ind = i;
            };
        }
        output.resize(minimal_w_indexes[min_ind].size());
        std::transform(minimal_w_indexes[min_ind].begin(),
                       minimal_w_indexes[min_ind].end(), output.begin(),
                       [&](const auto &a) { return simple[a]; });
    } else {
        output = input;
    }
}

int BooleanMinimizer::compareWithDiff(const std::vector<int8_t> &first,
                                      const std::vector<int8_t> &second) {
    int diff_index = -1;
    if (first.size() != second.size()) {
        return diff_index;
    }
    for (int i = 0; i < first.size(); i++) {
        if (first[i] == second[i]) {
            continue;
        } else if (diff_index == -1) {
            diff_index = i;
        } else {
            diff_index = -1;
            break;
        }
    }
    return diff_index;
}

bool BooleanMinimizer::compareWithAbsorb(const std::vector<int8_t> &first,
                                         const std::vector<int8_t> &second) {
    if (first.size() != second.size()) {
        return false;
    }
    for (int i = 0; i < first.size(); i++) {
        if (first[i] == second[i] || (first[i] == -1 || second[i] == -1)) {
            continue;
        } else {
            return false;
        }
    }
    return true;
}

void BooleanMinimizer::combine(
    std::vector<std::vector<int>> &minterms_w_indexes, int number_of_miniterms,
    int index, int dnf_length, std::set<int> &tmp, std::set<int> &indexes,
    std::vector<std::set<int>> &minimal_w_indexes) {
    for (int i = index; i < minterms_w_indexes.size(); i++) {
        std::set<int> dindexes = indexes;
        dindexes.insert(i);
        std::set<int> dtmp = tmp;
        for (int j = 0; j < minterms_w_indexes[i].size(); j++) {
            dtmp.insert(minterms_w_indexes[i][j]);
        }
        if (number_of_miniterms > 1) {
            combine(minterms_w_indexes, number_of_miniterms - 1, index + 1,
                    dnf_length, dtmp, dindexes, minimal_w_indexes);
        } else {
            if (dtmp.size() == dnf_length) {
                minimal_w_indexes.push_back(dindexes);
            }
        }
    }
    return;
}

void BooleanMinimizer::convertToString(
    std::vector<QString> &str,
    std::vector<std::vector<std::vector<int8_t>>> &table) {
    for (int y = 0; y < table.size(); y++) {
        // if (table[y].size() >= 1) {
            str.push_back(QString("Y%1 = ").arg(y + 1));
        // }
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
}

void BooleanMinimizer::addOutput() {
    for (auto &r : m_output_table) {
        r.push_back(0);
    }
    m_outputs++;
    mutex.unlock();
}

void BooleanMinimizer::addTerm() {
    mutex.lock();
    std::vector<int8_t> i(m_inputs, 0);
    std::vector<int8_t> o(m_outputs, 0);
    m_input_table.push_back(i);
    m_output_table.push_back(o);
    m_terms++;
    mutex.unlock();
}

void BooleanMinimizer::deleteInput() {
    if (m_inputs == 1) return;
    mutex.lock();
    for (auto &r : m_input_table) {
        r.erase(r.end() - 1);
    }
    m_inputs--;
    mutex.unlock();
}

void BooleanMinimizer::deleteOutput() {
    if (m_outputs == 1) return;
    mutex.lock();
    for (auto &r : m_output_table) {
        r.erase(r.end() - 1);
    }
    m_outputs--;
    mutex.unlock();
}

void BooleanMinimizer::deleteTerm() {
    if (m_terms == 1) return;
    mutex.lock();
    m_input_table.erase(m_input_table.end() - 1);
    m_output_table.erase(m_output_table.end() - 1);
    m_terms--;
    mutex.unlock();
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
}

void BooleanMinimizer::changeInput(QTableWidgetItem *index) {
    change(m_input_table, index);
}

void BooleanMinimizer::changeOutput(QTableWidgetItem *index) {
    change(m_output_table, index);
}
