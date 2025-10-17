#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    btnNums ={{Qt::Key_0,ui->btnNum0},
              {Qt::Key_1,ui->btnNum1},
              {Qt::Key_2,ui->btnNum2},
              {Qt::Key_3,ui->btnNum3},
              {Qt::Key_4,ui->btnNum4},
              {Qt::Key_5,ui->btnNum5},
              {Qt::Key_6,ui->btnNum6},
              {Qt::Key_7,ui->btnNum7},
              {Qt::Key_8,ui->btnNum8},
              {Qt::Key_9,ui->btnNum9},
             };

    btnOP = {{Qt::Key_Delete, ui->btnCE},
             {Qt::Key_Backspace, ui->btnDel},
            {Qt::Key_Period, ui->btnDot},
            {Qt::Key_Plus, ui->btnPlus},
            {Qt::Key_Minus, ui->btnSub},
            {Qt::Key_Asterisk, ui->btnMulti},
            {Qt::Key_Slash, ui->btnDivide},
            {Qt::Key_Percent, ui->btnPercent},
            {Qt::Key_Equal, ui->btnEqual},
            {Qt::Key_Enter, ui->btnEqual},
            {Qt::Key_Return, ui->btnEqual}
            };


    foreach(auto btn,btnNums)
        connect(btn,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    // connect(ui->btnNum0,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum1,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum2,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum3,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum4,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum5,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum6,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum7,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum8,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    // connect(ui->btnNum9,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    connect(ui->btnMulti,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnPlus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnDivide,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnSub,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));

    connect(ui->btnDenominator,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnRoot,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSquare,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnPercent,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
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
        else if(op =="/")
            if(op2==0)
                return "除数不能为0";
            else
                res = op1/op2;
        else if (op=="*")
            res = op1*op2;
    }

    operands.push_back(QString ::number(res));
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
    // if(operand !="")
    if(ui->display->text()!="")     //单操作符直接用operand容易在单双操作符运算的时候产生错误
    {
        double res = ui->display->text().toDouble();
        operand = "";

        //单操作符运算开始时清除栈内数据，因为这时候得出的结果为一个操作数，再按双操作符会再输入一个操作数
        //去除先双操作符运算后按等于号入栈的数据
        operands.clear();

        QString op = qobject_cast<QPushButton*>(sender())->text();
        if(op=="%")
            res /=100.0;
        else if(op=="1/X")
            res = 1/res;
        else if (op=="X^2")
            res *=res;
        else if(op=="√")
            res = sqrt(res);
        operands.push_back(QString ::number(res));
        ui->display->setText(QString::number(res));
    }

}





void MainWindow::on_btnClear_clicked()
{
    operand.clear();
    ui->display->setText(operand);
}


void MainWindow::on_btnEqual_clicked()
{
    if(operand !="")
    {
        operands.push_back(operand);
        operand = "";
    }

    QString res = calculation();
    ui->display->setText(res);
    // operand = res;
    // operands.push_back(operand);
    // operand="";
}



void MainWindow::on_btnSwitch_clicked()
{

    if (operand.isEmpty()) {
        operand = ui->display->text();      //获取文本框数据 因为连续计算后数字是入栈的
    }

    else if (operand.startsWith('-')) {
        operand = operand.mid(1);
        if (operand == "0" ) {
            operand = "0";
        }
    }
    else if (operand != "0") {
        operand = "-" + operand;
    }

    ui->display->setText(operand);
}


void MainWindow::on_btnCE_clicked()
{
    operand.clear();
    operands.clear();
    opcode.clear();
    opcodes.clear();
    ui->display->setText(operand);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    foreach(auto btnKey,btnNums.keys())
    {
        if(event->key()==btnKey)
            btnNums[btnKey]->animateClick();
    }

    foreach(auto btnOPKey,btnOP.keys())
    {
        if(event->key()==btnOPKey)
            btnOP[btnOPKey]->animateClick();
    }
}

