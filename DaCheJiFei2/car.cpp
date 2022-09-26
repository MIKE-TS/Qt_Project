#include "car.h"

Car::Car()
{

}
Car::Car(double *p,double Initiate,double Banking,double Banking2,QString NAME):Price(p), InitiateDistance(Initiate),BankingDistance(Banking),BankingDistance2(Banking2),Size(6),Name(NAME)
{

}

QString Car::GetName()
{
    return Name;
}
