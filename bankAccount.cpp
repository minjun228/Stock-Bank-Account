#include<string>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<time.h>
#include<cstdlib>
#include "bankAccount.h"
#include "account.h"
using namespace std;

bankAccount::bankAccount() 
{

}

bankAccount::~bankAccount() 
{

}

string bankAccount::getDate() 
{
    char dateStr[9];
    _strdate_s(dateStr);
    return dateStr;
}

string bankAccount::getTime() 
{
    char timeStr[9];
    _strtime_s(timeStr);
    return timeStr;
}

double bankAccount::view_balance() 
{
    cout<<"\nCash balance= $"<<cash_balance<<"\n";          
    return cash_balance;
}

void bankAccount::deposit_bank(double money) 
{
    cash_balance+=money;
    cout<<"\nDeposit $"<<money<<" to bank account";
    cout<<"\n\nCash balance= $"<<cash_balance<<endl;

    ofstream myfile;
    myfile.open("bank_transaction_history.txt",ios::app);
    if(myfile.is_open())
    {
        myfile.eof();
        myfile<<"\nDeposit\t\t$"<<money<<"\t"<<cash_balance<<"\t\t"<<getDate()<<"\t"<<getTime()<<endl;
    }
    else
    {
        cout<<"Cannot record this transaction. File opening failed.\n";
    }
}

void bankAccount::withdraw_bank(double money) 
{
    if(money<cash_balance)
    {
        cash_balance-=money;
        cout<<"\nWithdraw $"<<money<<" from bank account";
        cout<<"\n\nCash balance= $"<<cash_balance<<endl;
    
        ofstream myfile;
        myfile.open("bank_transaction_history.txt",ios::app);

        if(myfile.is_open())
        {
            myfile<<"\nWithdrawal\t$"<<money<<"\t"<<cash_balance<<"\t\t"<<getDate()<<"\t"<< getTime()<<endl;
        }
        else
        {
            cout<<"Cannot record this transaction. File opening failed.\n";
        }
    }
    else
        cout<<"Transaction failed. Insufficient balance\n"; 
}

void bankAccount::print_bankHistory() 
{
    ifstream myfile;
    string line;
    myfile.open("bank_transaction_history.txt",ios::app);
    if(myfile.is_open())
    {
        while(!myfile.eof())
        {
            getline(myfile,line);
            cout<<line<<endl;
        }
        myfile.close();
    }
    else
        cout<<"Error in opening the file.\n";
}

double bankAccount::getBalance()
{
    return cash_balance;
}

void bankAccount::setBalance(double blnc)
{
    cash_balance=blnc;
}