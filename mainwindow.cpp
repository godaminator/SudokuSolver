#include "mainwindow.h"
#include "./ui_mainwindow.h"





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),sudokugrid(std::vector<std::vector<char>>(9,std::vector<char> (9,'.')))
    , ui(new Ui::MainWindow)
{
    //initSudokuGrid();
    ui->setupUi(this);
    this->menuBar()->setNativeMenuBar(false);
    centerW=this->centralWidget();
    setupLayout();
    ButtonConstruction();
    setupcalculate();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setupLayout()
{
    layout=new QHBoxLayout(centerW);
    SudokuLayout=new QGridLayout();
    SudokuLayout->setSpacing(0);

    QVBoxLayout *lV= new QVBoxLayout();
    QHBoxLayout *lH= new QHBoxLayout();

    QSpacerItem *spacerT= new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem *spacerB= new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem *spacerL= new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem *spacerR= new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);


    lH->addSpacerItem(spacerL);
    lH->addLayout(SudokuLayout);
    lH->addSpacerItem(spacerR);

    lV->addSpacerItem(spacerT);
    lV->addLayout(lH);
    lV->addSpacerItem(spacerB);

    layout->addLayout(lV);



}
//need to be removed
void MainWindow::initSudokuGrid()
{

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            sudokugrid[i][j]='.';

        }
    }
}

void MainWindow::setupcalculate()
{
    QVBoxLayout *rightlayout=new QVBoxLayout();
    QPushButton * Calc=new QPushButton(this);
    QSpacerItem *spacerT= new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    QSpacerItem *spacerB= new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);

    Calc->setText("Calculate");
    Calc->setFixedSize(100,40);


    Slabel = new QLabel(this);
    Slabel->setText("Status: Initialize Sudoku!! ");

    rightlayout->addSpacerItem(spacerT);
    rightlayout->addWidget(Slabel);
    rightlayout->addWidget(Calc);
    rightlayout->addSpacerItem(spacerB);

    layout->addLayout(rightlayout);
    connect(Calc,&QPushButton::clicked,this,&MainWindow::on_Calculate_clicked);

}

void MainWindow::ButtonConstruction(){


    buttonGroup=new QButtonGroup(centerW);

    for(int i=0;i<9;i++){
        QList<QPushButton*> temp;
        for(int j=0;j<9;j++){

            QPushButton * Button=new QPushButton(centerW);
            buttonGroup->addButton(Button,i*9+j);
            Button->setFixedSize(40,40);
            SudokuLayout->addWidget(Button,i,j);

            temp<<Button;

        }
        mygrid<<temp;

    }
    connect(buttonGroup,&QButtonGroup::buttonClicked,this,&MainWindow::on_pushButton_clicked);
}

void MainWindow::on_pushButton_clicked(QAbstractButton *button){
    QPushButton *mybutton=static_cast<QPushButton*>(button);

    int id=buttonGroup->id(mybutton);
    int row=id/9;
    int col=id%9;
    qDebug()<<row<<col;
    bool ok;
    int i = QInputDialog::getInt(this, tr("QInputDialog::getInt()"),
                                 tr("value:"), 1, 1, 9, 1, &ok);
    if(ok){
    sudokugrid[row][col]='0'+i;
    mybutton->setText(QString(sudokugrid[row][col]));
    }else{
        //if cancled inputbox
        sudokugrid[row][col]='.';
        mybutton->setText("");
    }


}

void MainWindow::on_Calculate_clicked()
{
    qInfo()<<"Claculate cliked";


    //call solver engine
    SudokuSolveEngine engine;
    bool ok;
    vector<vector<char>> memento=sudokugrid;

    engine.solveSudoku(sudokugrid,ok);
    qInfo()<<"Returned  from engine";

    for(int i=0;i<9;i++){
        QDebug dbg(QtDebugMsg);
        for(int j=0;j<9;j++){
            dbg<<sudokugrid[i][j]<<" ";

        }

    }
    if(ok){
    for(int i=0;i<9;i++){

        for(int j=0;j<9;j++){
            mygrid[i][j]->setText(QString(sudokugrid[i][j]));

        }

    }
    Slabel->setText("Status: Calculated!");
    }else{
        sudokugrid=memento;
        Slabel->setText("Status: Invalid Configuration!");
    }

}

void MainWindow::resetGrid()
{
    qDebug()<<"x";
    sudokugrid=std::vector<std::vector<char>>(9,std::vector<char> (9,'.'));
    for(int i=0;i<9;i++){

        for(int j=0;j<9;j++){
            mygrid[i][j]->setText("");

        }

    }
    Slabel->setText("Status: Initialize Sudoku!! ");

}

void MainWindow::closeProgram()
{
    QApplication::quit();
}




