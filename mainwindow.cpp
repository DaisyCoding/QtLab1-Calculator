#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnNum0,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum1,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum2,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum3,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum4,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum5,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum6,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum7,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum8,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum9,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    connect(ui->btnMulti,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnPlus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnDivide,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnSub,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::calculation()
{
    double res = 0;
    if(operands.size()==2 && opcodes.size()>=1)
    {
        //取操作数
        double op1 = operands.front().toDouble();
        operands.pop_front();
        double op2 = operands.front().toDouble();
        operands.pop_front();

        //取操作符
        QString op = opcodes.front();
        opcodes.pop_front();

        if(op =="+")
            res = op1+op2;
        else if(op =="-")
            res = op1-op2;
        else if(op =="÷")
            if(op2==0)
                return "除数不能为0";
            else
                res = op1/op2;
        else if (op=="×")
            res = op1*op2;
    }
    return QString::number(res);
}

void MainWindow::btnNumClicked()
{

    QString digit = qobject_cast<QPushButton *>(sender())->text();
    // if(digit=="0"&&operand=="0")
    //     digit ="";

    if (operand == "0") {
        if (digit == "0") {
            digit = "";
        } else {
            operand.clear();
        }
    }

    operand += digit;
    ui->display->setText(operand);
}

void MainWindow::on_btnDot_clicked()
{
    //如果有小数点则不加入
    if(!operand.contains("."))
        operand+=qobject_cast<QPushButton *>(sender())->text();
    ui->display->setText(operand);
}


void MainWindow::on_btnDel_clicked()
{

    operand = operand.left(operand.length()-1);         //取从左数str.length()-1个单位的字符
    ui->display->setText(operand);
}

void MainWindow::btnBinaryOperatorClicked()
{

    QString opcode = qobject_cast<QPushButton *>(sender())->text();
    if(operand != "")
    {
        operands.push_back(operand); //双操作数，入栈等待
        operand = "";
    }
    opcodes.push_back(opcode);      //存入操作符

    if(operands.size()>1)
        {                           //当没有操作数的时候 证明进行了计算，才给出计算结果
        QString res = calculation();
        ui->display->setText(res);
    }
}

void MainWindow::btnUnaryOperatorClicked()
{

}





void MainWindow::on_btnClear_clicked()
{
    operand.clear();
    ui->display->setText(operand);
}


void MainWindow::on_btnEqual_clicked()
{

}

