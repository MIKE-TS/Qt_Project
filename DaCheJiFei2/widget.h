#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:

    void on_pushButton_calculate_clicked();

    void on_pushButton_close_clicked();

    void on_comboBox_type_currentIndexChanged(const QString &arg1);

    void on_doubleSpinBox_distance_valueChanged(const QString &arg1);



    void on_doubleSpinBox_reserve_valueChanged(const QString &arg1);

    void on_doubleSpinBox_distance2_valueChanged(const QString &arg1);

    void on_doubleSpinBox_distance3_valueChanged(const QString &arg1);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
