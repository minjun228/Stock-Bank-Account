#ifndef ACCOUNT_H
#define ACCOUNT_H

class account 
{
 public:
     account(); 
     virtual double getBalance()=0;
     virtual void setBalance(double)=0;
     static double cash_balance;
};
#endif 