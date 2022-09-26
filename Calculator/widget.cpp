#include "widget.h"
#include "ui_widget.h"
#include"QMessageBox"
#include<QDebug>
#include<QStack>
#include<QtMath>
//判断字符是否是操作符（不包括括号）
bool isOperator(QChar c)
{
    return (c == '+' || c == '-'|| c == '*' || c == '/' || c == '^');
}
bool check(QString exp)
{
   int size = exp.size();
   int left = 0,right = 0,dot = 0;//dot记录每个数中小数点个数
   for(int i = 0;i < size;i++)
   {
       if(exp[i] == '.')
       {
           if(++dot >= 2)
               throw "一个数中出现多个小数点!";
       }
       else if(isOperator(exp[i]))
       {
           dot = 0;
       }
       else if(exp[i] == '(')
           left++;
       else if(exp[i] == ')')
           right++;
       else if(!exp[i].isDigit())
           throw "表达式中出现非法字符！";
       if(i <= size-2)
       {
           if(exp[i].isDigit() && exp[i+1] == '(')
               throw "非法表达式，数字后是左括号！";
           if(exp[i] == '.' && !exp[i+1].isDigit())
               throw "非法表达式，小数点后不是数字！";
           if(exp[i] == '(' && (!exp[i+1].isDigit() && exp[i+1] != '('))
               throw "非法表达式，左括号后不是数字或左括号！";
           if(exp[i] == ')' &&(!isOperator(exp[i+1]) && exp[i+1] != ')'))
               throw "非法表达式，右括号后不是操作符或右括号！";
           if(isOperator(exp[i]) && (!exp[i+1].isDigit() && exp[i+1] != '('))
               throw "非法表达式，操作符后不是数字或左括号！";
       }
   }
   if(left != right)
       throw "左右括号数不等！";
   return true;
}
int prior(char oper)
{
    switch(oper)
    {
        case '(':
        case ')':return 0;
        case '+':
        case '-':return 1;
        case '*':
        case '/':return 2;
        case '^':return 3;
    }
}
double calculate(char oper,double num1,double num2)
{
    switch(oper)
    {
        case '+':return (num1+num2);
        case '-':return (num1-num2);
        case '*':return (num1*num2);
        case '/':if(num2 == 0)
                    throw"除数为0！";
                return (num1/num2);
        case '^':return qPow(num1,num2);
    }
}
double exp_calculate(QString exp,Widget *pointer)
{
    int size = exp.size();
    //num记录表达式中的double数据
    QString num ;
    //创建运算符栈和操作数栈
    QStack<QChar> operator_stack;
    QStack<double>num_stack;
    //两个操作数
    double num1,num2;
    //运算符
    QChar oper;
    //result记录最终结果
    //QMessageBox::critical()
    double result;
    for(int i = 0;i < size;i++)
    {
        if(exp[i].isDigit() || exp[i] == '.')
        {
            num.append(exp[i]);
        }
        else if(exp[i] == '(')
        {
            operator_stack.push(exp[i]);
        }
        //可能出现多个右括号连在一起的情况：））
        else if(exp[i] == ')')
        {
            if(!num.isEmpty())
            {
                num_stack.push(num.toDouble());
                num.clear();
            }
            while(operator_stack.top() != '(')
            {
                oper = operator_stack.pop();
                num2 = num_stack.pop();
                num1 = num_stack.pop();
                num_stack.push(calculate(oper.toLatin1(),num1,num2));
            }
            operator_stack.pop();
        }
        else if(isOperator(exp[i]))
        {
            if(!num.isEmpty())
            {
                num_stack.push(num.toDouble());
                num.clear();
            }
           while(prior(operator_stack.top().toLatin1()) >= prior(exp[i].toLatin1()))
           {
                oper = operator_stack.pop();
                num2 = num_stack.pop();
                num1 = num_stack.pop();
                num_stack.push(calculate(oper.toLatin1(),num1,num2));
           }
           operator_stack.push(exp[i]);
        }
    }
    result = num_stack.pop();
    return result;
}
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->textEdit->setText("0");
    ui->textEdit->setAlignment(Qt::AlignRight);
    ui->textEdit->moveCursor(QTextCursor::End);
}

Widget::~Widget()
{
    delete ui;
}
//特殊情况：初始状态或按下了等于符号
void Widget::on_pushButton0_clicked()
{
    if(ui->textEdit->toPlainText() == "0" || (!ui->lineEdit->text().isEmpty()))
    {
        ui->textEdit->setText("0");
        ui->textEdit->setAlignment(Qt::AlignRight);
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->lineEdit->clear();
    }
    else
    {
        ui->textEdit->insertPlainText("0");
    }
}
void Widget::on_pushButton1_clicked()
{
    if(ui->textEdit->toPlainText() == "0" || (!ui->lineEdit->text().isEmpty()))
    {
        ui->textEdit->setText("1");
        ui->textEdit->setAlignment(Qt::AlignRight);
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->lineEdit->clear();
    }
    else
    {
        ui->textEdit->insertPlainText("1");
    }
}
void Widget::on_pushButton2_clicked()
{
    if(ui->textEdit->toPlainText() == "0" || (!ui->lineEdit->text().isEmpty()))
    {
        ui->textEdit->setText("2");
        ui->textEdit->setAlignment(Qt::AlignRight);
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->lineEdit->clear();
    }
    else
    {
        ui->textEdit->insertPlainText("2");
    }
}
void Widget::on_pushButton3_clicked()
{
    if(ui->textEdit->toPlainText() == "0" || (!ui->lineEdit->text().isEmpty()))
    {
        ui->textEdit->setText("3");
        ui->textEdit->setAlignment(Qt::AlignRight);
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->lineEdit->clear();
    }
    else
    {
        ui->textEdit->insertPlainText("3");
    }
}
void Widget::on_pushButton4_clicked()
{
    if(ui->textEdit->toPlainText() == "0" || (!ui->lineEdit->text().isEmpty()))
    {
        ui->textEdit->setText("4");
        ui->textEdit->setAlignment(Qt::AlignRight);
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->lineEdit->clear();
    }
    else
    {
        ui->textEdit->insertPlainText("4");
    }
}
void Widget::on_pushButton5_clicked()
{
    if(ui->textEdit->toPlainText() == "0" || (!ui->lineEdit->text().isEmpty()))
    {
        ui->textEdit->setText("5");
        ui->textEdit->setAlignment(Qt::AlignRight);
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->lineEdit->clear();
    }
    else
    {
        ui->textEdit->insertPlainText("5");
    }
}
void Widget::on_pushButton6_clicked()
{
    if(ui->textEdit->toPlainText() == "0" || (!ui->lineEdit->text().isEmpty()))
    {
        ui->textEdit->setText("6");
        ui->textEdit->setAlignment(Qt::AlignRight);
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->lineEdit->clear();
    }
    else
    {
        ui->textEdit->insertPlainText("6");
    }
}
void Widget::on_pushButton7_clicked()
{
    if(ui->textEdit->toPlainText() == "0" || (!ui->lineEdit->text().isEmpty()))
    {
        ui->textEdit->setText("7");
        ui->textEdit->setAlignment(Qt::AlignRight);
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->lineEdit->clear();
    }
    else
    {
        ui->textEdit->insertPlainText("7");
    }
}
void Widget::on_pushButton8_clicked()
{
    if(ui->textEdit->toPlainText() == "0" || (!ui->lineEdit->text().isEmpty()))
    {
        ui->textEdit->setText("8");
        ui->textEdit->setAlignment(Qt::AlignRight);
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->lineEdit->clear();
    }
    else
    {
        ui->textEdit->insertPlainText("8");
    }
}
void Widget::on_pushButton9_clicked()
{
    if(ui->textEdit->toPlainText() == "0" || (!ui->lineEdit->text().isEmpty()))
    {
        ui->textEdit->setText("9");
        ui->textEdit->setAlignment(Qt::AlignRight);
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->lineEdit->clear();
    }
    else
    {
        ui->textEdit->insertPlainText("9");
    }
}

void Widget::on_pushButton_dot_clicked()
{
    //检查前面是否为数字
    QString exp = ui->textEdit->toPlainText();
    //按下等于后再按下了小数点
    if(!ui->lineEdit->text().isEmpty())
    {
        ui->textEdit->setText("0.");
        ui->textEdit->setAlignment(Qt::AlignRight);
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->lineEdit->clear();
    }
    else
    {
        if(exp.at(exp.size()-1).isDigit())
        {
            ui->textEdit->insertPlainText(".");
        }
        else
        {
            QMessageBox::critical(this,"错误提示","小数点前不是数字！");
        }
    }
}

void Widget::on_pushButton_plus_clicked()
{
    //未按下等于符号情况
    if(ui->lineEdit->text().isEmpty())
    {
        //检查前一字符是否是数字
        QString exp = ui->textEdit->toPlainText();
        if(exp.at(exp.size()-1).isDigit() || exp.at(exp.size()-1) == ')')
        {
            ui->textEdit->insertPlainText("+");
        }
        else
        {
            QMessageBox::critical(this,"错误提示","运算符前不是数字或右括号！");
        }
    }
    //按下等于符号情况，将结果框字符结果作为起始输入并加上运算符，将结果框清除
    else
    {
        //截取结果框中的数字部分并加上运算符作为输入,将结果框清除
        QString exp = ui->lineEdit->text().mid(2) + "+";
        ui->textEdit->setText(exp);
        ui->textEdit->setAlignment(Qt::AlignRight);
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->lineEdit->clear();
    }
}

void Widget::on_pushButton_minus_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QString exp = ui->textEdit->toPlainText();
        if(exp.at(exp.size()-1).isDigit() || exp.at(exp.size()-1) == ')')
        {
           ui->textEdit->insertPlainText("-");
        }
        else
        {
            QMessageBox::critical(this,"错误提示","运算符前不是数字或右括号！");
        }
    }
    else
    {
        QString exp = ui->lineEdit->text().mid(2) + "-";
        ui->textEdit->setText(exp);
        ui->textEdit->setAlignment(Qt::AlignRight);
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->lineEdit->clear();
    }
}

void Widget::on_pushButton_multiply_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QString exp = ui->textEdit->toPlainText();
        if(exp.at(exp.size()-1).isDigit() || exp.at(exp.size()-1) == ')')
        {
            ui->textEdit->insertPlainText("*");
        }
        else
        {
            QMessageBox::critical(this,"错误提示","运算符前不是数字或右括号！");
        }
    }
    else
    {
        QString exp = ui->lineEdit->text().mid(2) + "*";
        ui->textEdit->setText(exp);
        ui->textEdit->setAlignment(Qt::AlignRight);
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->lineEdit->clear();
    }
}

void Widget::on_pushButton_divide_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QString exp = ui->textEdit->toPlainText();
        if(exp.at(exp.size()-1).isDigit() || exp.at(exp.size()-1) == ')')
        {
            ui->textEdit->insertPlainText("/");
        }
        else
        {
            QMessageBox::critical(this,"错误提示","运算符前不是数字或右括号！");
        }
    }
    else
    {
        QString exp = ui->lineEdit->text().mid(2) + "/";
        ui->textEdit->setText(exp);
        ui->textEdit->setAlignment(Qt::AlignRight);
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->lineEdit->clear();
    }
}

void Widget::on_pushButton_pow_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QString exp = ui->textEdit->toPlainText();
        if(exp.at(exp.size()-1).isDigit() || exp.at(exp.size()-1) == ')')
        {
           ui->textEdit->insertPlainText("^");
        }
        else
        {
            QMessageBox::critical(this,"错误提示","运算符前不是数字或右括号！");
        }
    }
    else
    {
        QString exp = ui->lineEdit->text().mid(2) + "^";
        ui->textEdit->setText(exp);
        ui->textEdit->setAlignment(Qt::AlignRight);
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->lineEdit->clear();
    }
}

//左括号前必须是操作符或空白
void Widget::on_pushButton_left_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QString exp = ui->textEdit->toPlainText();
       if(exp == "0")
        {
            ui->textEdit->setText("(");
            ui->textEdit->setAlignment(Qt::AlignRight);
            ui->textEdit->moveCursor(QTextCursor::End);
        }
        else if(isOperator(exp.at(exp.size()-1)) || exp.at(exp.size()-1) == '(')
        {
            ui->textEdit->insertPlainText("(");
        }
       else
       {
           QMessageBox::critical(this,"错误提示","左括号前是数字,小数点或右括号！");
       }
    }
    else
    {
        ui->textEdit->setText("(");
        ui->textEdit->setAlignment(Qt::AlignRight);
        ui->textEdit->moveCursor(QTextCursor::End);
        ui->lineEdit->clear();
    }
}
//右括号前必须是数字或右括号
void Widget::on_pushButton_right_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        QString exp = ui->textEdit->toPlainText();
        if(exp.at(exp.size()-1).isDigit() || exp.at(exp.size()-1) == ')')
        {
            ui->textEdit->insertPlainText(")");
            ui->textEdit->setAlignment(Qt::AlignRight);
            ui->textEdit->moveCursor(QTextCursor::End);
        }
        else
        {
            QMessageBox::critical(this,"错误提示","右括号前不是数字或右括号！");
        }
    }
    else
    {
        QMessageBox::critical(this,"错误提示","计算完未清零前不能输入右括号！");
    }
}

void Widget::on_pushButton_equal_clicked()
{
    //if(check(ui->textEdit->toPlainText()))
    if(true)
    try
    {
        QString exp = ui->textEdit->toPlainText();
        //表达式首个数为负数的特殊情况
        if(exp[0] == '-')
        {
            exp = "0" + exp;
        }
        exp = "(" + exp + ")";
        check(exp);
        double double_result = exp_calculate(exp,this);
        QString str_result = "= " + QString::number(double_result,'f');
        //将结果显示到lineEdit中
        ui->lineEdit->setText(str_result);
    }
    catch(char const *str)
    {
        QMessageBox::critical(this,"错误提示",str);
    }
}

void Widget::on_pushButton_delete_clicked()
{
    QString exp = ui->textEdit->toPlainText();
    //删除操作
    if(exp.size() <= 1)
    {
        ui->textEdit->setText("0");
        ui->textEdit->setAlignment(Qt::AlignRight);
        ui->textEdit->moveCursor(QTextCursor::End);
    }
    else
    {
        QTextCursor cursor = ui->textEdit->textCursor();
        if(cursor.hasSelection())
            cursor.clearSelection();
        cursor.deletePreviousChar();
    }
    ui->lineEdit->clear();
}

void Widget::on_pushButton_cancel_clicked()
{
    ui->textEdit->setText("0");
    ui->textEdit->setAlignment(Qt::AlignRight);
    ui->textEdit->moveCursor(QTextCursor::End);
    ui->lineEdit->clear();
}


