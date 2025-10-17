#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStack>
#include<QKeyEvent>
#include<QPushButton>
#include<QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString operand;
    QString opcode;
    QStack<QString> operands;
    QStack<QString> opcodes;
    QMap<int,QPushButton*> btnNums;
    QMap<int,QPushButton*> btnOP;

    QString calculation();

private slots :

    void btnNumClicked();

    void on_btnDot_clicked();

    void on_btnDel_clicked();

    void btnBinaryOperatorClicked();

    void btnUnaryOperatorClicked();

    void on_btnClear_clicked();

    void on_btnEqual_clicked();

    void on_btnSwitch_clicked();

    void on_btnCE_clicked();

    virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
