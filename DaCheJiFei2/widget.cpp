#include "widget.h"
#include "ui_widget.h"
#include"car.h"
#include"passenger.h"
#define CAR_NUMBER 4

double price[CAR_NUMBER][6] = {{1,2.6,2.0,1.8,10,0.5},{0,2.8,1.9,1.5,10,1},{0.5,3.0,1.8,1.2,8,0.5},{0.8,2.4,2.0,1.8,12,0.7}};
double distance[CAR_NUMBER][3] = {{3,35,40},{3.5,30,38},{2.7,37,42},{3.5,38,45}};
QString name[CAR_NUMBER] = {"出租车","滴滴专车","顺风专车","礼橙专车"};
Car car[CAR_NUMBER] = {Car(price[0],distance[0][0],distance[0][1],distance[0][2],name[0]),
                       Car(price[1],distance[1][0],distance[1][1],distance[1][2],name[1]),
                       Car(price[2],distance[2][0],distance[2][1],distance[2][2],name[2]),
                       Car(price[3],distance[3][0],distance[3][1],distance[3][2],name[3])};
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
   // connect(ui->comboBox_number,QComboBox::currentIndexChanged();)
    ui->doubleSpinBox_distance->valueChanged(1);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_close_clicked()
{
    this->close();
}

void Widget::on_pushButton_calculate_clicked()
{
    QString type = ui->comboBox_type->currentText();
    int index = 0;
    for(int i = 0;i < CAR_NUMBER;i++)
    {
        if(car[i].GetName() == type)
        {
            index = i;
            break;
        }
    }
    double Distance[4];
    Distance[0] = ui->doubleSpinBox_reserve->value();
    Distance[1] = ui->doubleSpinBox_distance->value();
    Distance[2] = ui->doubleSpinBox_distance2->value();
    Distance[3] = ui->doubleSpinBox_distance3->value();
    Passenger passenger(Distance,car[index]);
    ui->lcdNumber->display(passenger.calculate());
}

void Widget::on_doubleSpinBox_distance_valueChanged(const QString &arg1)
{
   emit ui->pushButton_calculate->clicked();
}

void Widget::on_comboBox_type_currentIndexChanged(const QString &arg1)
{
    emit ui->pushButton_calculate->clicked();
}

void Widget::on_doubleSpinBox_reserve_valueChanged(const QString &arg1)
{
    emit ui->pushButton_calculate->clicked();
}

void Widget::on_doubleSpinBox_distance2_valueChanged(const QString &arg1)
{
    emit ui->pushButton_calculate->clicked();
}

void Widget::on_doubleSpinBox_distance3_valueChanged(const QString &arg1)
{
    emit ui->pushButton_calculate->clicked();
}
