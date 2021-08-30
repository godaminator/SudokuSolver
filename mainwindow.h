#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QButtonGroup>
#include <QPushButton>
#include <QList>
#include <QGridLayout>
#include <QInputDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QLabel>
#include <sudokusolveengine.h>
#include <iostream>
#include <vector>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void on_pushButton_clicked(QAbstractButton *button);
    void on_Calculate_clicked();
    void resetGrid();
    void closeProgram();


private:
    std::vector<std::vector<char>> sudokugrid;
    Ui::MainWindow *ui;
    QWidget * centerW;
    QHBoxLayout *layout;
    QGridLayout * SudokuLayout;
    QLabel *Slabel;

    QList<QList<QPushButton*>> mygrid;
    QButtonGroup * buttonGroup;

    enum class sudokustatus {invalid=0,valid=1};

private:
//function
    void ButtonConstruction();
    void setupLayout();
    void initSudokuGrid();
    void setupcalculate();

};
#endif // MAINWINDOW_H
