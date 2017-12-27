#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include "account.h"
#include<string>
using namespace std;

class bankAccount:public account 
{
public:
    bankAccount();
    ~bankAccount();
    double view_balance();
    void deposit_bank(double);
    void withdraw_bank(double);
    void print_bankHistory();
    string getDate();
    string getTime();
    virtual double getBalance();
    virtual void setBalance(double);
};
#endif 