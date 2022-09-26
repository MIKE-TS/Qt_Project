#ifndef CAR_H
#define CAR_H
#include"QString"

class Car
{
public:
    Car();
    Car(double *p,double Initiate,double Banking,double Banking2,QString NAME);
    QString GetName();
private:
    double *Price;//分别记录预约服务费，1,2,3拼车价和起步价，服务费
    int Size;
    double InitiateDistance;
    double BankingDistance;//空行公里数（非拼车）
    double BankingDistance2;//空行公里数(拼车）
    QString Name;
    friend class Passenger;
};

#endif // CAR_H
