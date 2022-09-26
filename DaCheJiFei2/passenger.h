#ifndef PASSENGER_H
#define PASSENGER_H
#include"car.h"

class Passenger
{
public:
    Passenger();
    Passenger(double* distance,Car c);
    double calculate();
private:
    double *Distance;
    int Size;
    bool Share;//记录是否拼车
    Car car;
};

#endif // PASSENGER_H
