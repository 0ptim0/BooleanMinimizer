#ifndef MAINWINDOW
#define MAINWINDOW

#include <QMainWindow>

#include "booleanminimizer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    BooleanMinimizer *boolean_minimizer;

private:
    unsigned m_inputs{1};
    unsigned m_outputs{1};
    unsigned m_terms{1};

public slots:
    void print();
    void print(QTableWidgetItem *index);
    void print(std::vector<QString> &vec);
    void addInput();
    void addOutput();
    void addTerm();
    void deleteInput();
    void deleteOutput();
    void deleteTerm();
    void changeInput(QTableWidgetItem *index);
    void changeOutput(QTableWidgetItem *index);
};
#endif  // MAINWINDOW
