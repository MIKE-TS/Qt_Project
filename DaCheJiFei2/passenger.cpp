#include "passenger.h"

Passenger::Passenger()
{

}

Passenger::Passenger(double* distance,Car c):Distance(distance),Size(4),car(c)
{
   Share = (Distance[2]&&Distance[3]);//给Share赋值，若Distance[2]和Distance[3]均为0表示未拼车，赋值为false
}

double Passenger::calculate()
{
     double price = 0;
     price += Distance[0]*car.Price[0];//预约服务费
     //乘车里程费计算：
     if(Distance[1] + Distance[2] + Distance[3] <= car.InitiateDistance && Distance[1] + Distance[2] + Distance[3] > 0)
     {
         price+=car.Price[4];//起步费
         return price;
     }
     else if(Distance[1] + Distance[2] + Distance[3] > car.InitiateDistance)
     {
         if(Distance[1] > car.InitiateDistance)
         {
             price+=(car.Price[4]+car.Price[1]*(Distance[1] - car.InitiateDistance) + car.Price[2]*Distance[2] + car.Price[3]*Distance[3]); 
         }
         else
         {
             if((Distance[1] + Distance[2]) > car.InitiateDistance)
             {
                 price+=(car.Price[4]+car.Price[2]*(Distance[1] + Distance[2] - car.InitiateDistance) + car.Price[3]*Distance[3]); 
             }
             else
             {
                 price += car.Price[4] + car.Price[3]*(Distance[1] + Distance[2] +Distance[3] - car.InitiateDistance);
             }
         }
     }
     //空行费：
     double Banking = (Share ? car.BankingDistance2:car.BankingDistance);//空行距离
     if(Distance[1] + Distance[2] + Distance[3] > Banking)
     {
         price += car.Price[5]*(Distance[1] + Distance[2] + Distance[3] - Banking);
     }
     return price;
}
