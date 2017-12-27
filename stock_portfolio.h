#ifndef STOCKPORTFOLIO_H
#define STOCKPORTFOLIO_H

#include "account.h"
#include<string>
using namespace std;

class Index
{
    friend class stockaccount; 
    public: 
        Index(string& name,int numb)
        :symbol(name),number(numb)
        {
            this->next=NULL;
            this->prev=NULL;
        }

private:
    string symbol;
    int number;
    Index *next;
    Index *prev;
};

class stockaccount:public account 
{
public:
    stockaccount();
    static double total_portfolio_value;
    void display();
    void current_portfolio();
    void buy_shares();
    void sell_shares();
    void addIndex(Index *);
    void eraseIndex(string Index);
    void transac_history();
    void update_stocks();
    string getTime();
    Index *split(Index *);
    Index *merge_sort(Index *);
    Index *sortList(Index *first,Index *second);
    void sort_wrapper();
    virtual double getBalance();
    virtual void setBalance(double);
private:
    Index *firstPtr; 
    Index *lastPtr; 
    int size_list; 
};
#endif 