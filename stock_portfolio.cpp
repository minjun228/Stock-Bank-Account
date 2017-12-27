#include<string>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<time.h>
#include<cstdlib>
#include <vector>

#include "stockportfolio.h"
using namespace std;

double stockaccount::total_portfolio_value=0; 

string stockaccount::getTime() 
{
    char timeStr[9];
    _strtime_s(timeStr);
    return timeStr;
}

stockaccount::stockaccount()
{
    firstPtr=0;
    lastPtr=0;
}



void stockaccount::display() 
{
 
    string symb;
    cout<<"\nEnter stock symbol for checking price: ";
    cin>>symb;
    fstream myfile; 
    string line,sub;
    vector <string> lines;
    vector <string> symbols;
    string temp;
    string tempSymbol;
    string delim = "\t";

    int random=rand()%4;
    if(random==0)
    {
        myfile.open("stock1.txt");
    }
    else if(random==1)
    {
        myfile.open("stock2.txt");
    }
    else if(random==2)
    {
        myfile.open("stock3.txt");
    }
    else 
    {
        myfile.open("stock4.txt");
    }

    if(myfile.is_open())
    {
        while(getline(myfile,line))
        {
            temp=line;
            lines.push_back(temp);
            
        }
        for(int i = 0; i <lines.size(); i++){
        
            tempSymbol = lines[i].substr(0, lines[i].find(delim));
            symbols.push_back(tempSymbol);
        }
           
        for (int j =0; j< lines.size(); j++){
                      if(symb == symbols[j])
                      {
                         cout << "\n" << lines[j] << "\t" <<getTime() << endl;
                      }
            }
    }
    myfile.close();
}


void stockaccount::buy_shares() 
{
    string symb;
    int num;
    double max_pershare;
    time_t seconds;
    seconds=time(NULL);
    struct tm *timeinfo;
    errno_t localtime_s(  
   struct tm* _tm,  
   const time_t *time   
);  
    bool stock=false;
    bool available=false;
    int one;
    string second,third,fourth, fifth;

    cout<<"\nEnter buy options: ";
    cin>>symb;
    cin>>num;
    cin>>max_pershare;

    fstream myfile; 
    string line,sub;

    int i=rand()%4 +1;
    if(i==0)
    {
        myfile.open("stock1.txt");
    }
    else if(i==1)
    {
        myfile.open("stock2.txt");
    }
    else if(i==2)
    {
        myfile.open("stock3.txt");
    }
    else 
    {
        myfile.open("stock4.txt");
    }

    if(myfile.is_open())
    {
        while(getline(myfile,line))
        {
            
            istringstream iss(line); 
            double val;

            while(iss>>sub>>one >> second >> third >> fourth >> fifth >>  val)
            {
                if(sub==symb)
                {
                available=true;
                if(max_pershare>val) 
                {
                    double total_val=num*val;
                    if(total_val>cash_balance)
                    {
                        cout<<"Transaction failed. Insufficient balance in your account.\n";
                    }
                    else
                    {
                    ofstream myfile;
                    myfile.open("stock_transaction_history.txt",ios::app); 
                    if(myfile.is_open())
                    {
                        myfile<<"Buy\t";
                        myfile<<symb<<"\t";
                        myfile<<num<<"\t";
                        myfile<<""<<val<<"\t";
                        myfile<<getTime()<<endl;
                        myfile.close();
                    }
                    else
                    {
                       cout<<"Transaction failed. Unable to open file"<<endl;
                       break;
                    }

                    cash_balance=cash_balance-total_val; 
                
                    Index *ptr=firstPtr;
                    
                    if(stock==false) 
                    {
                       
                        Index *xIndex=new Index(symb,num);
                        addIndex(xIndex);
                    }
                    break;
                    }

                }
                else
                {
                    cout<<"Transaction failed. The maximum amount entered is less than the price of the stock"<<endl;
                    break;
                }
                }

            }
        }
    }

    if(available==false)
    {
        cout<<"Transaction failed. The stock you want to buy is not available\n";
    }
}

void stockaccount::sell_shares() 
{
    string symb2;
    int one;
    string second,third,fourth, fifth;

    int num;
    double min_pershare;
    bool available=false;
    if(firstPtr!=0)
    {
    cout<<"\nEnter selling options: ";
    cin>>symb2;
    cin>>num;
    cin>>min_pershare;

    fstream myfile; 
    string line,sub;

   int i=rand()%4;
    if(i==0)
    {
        myfile.open("stock1.txt");
    }
    else if(i==1)
    {
        myfile.open("stock2.txt");
    }
    else if(i==2)
    {
        myfile.open("stock3.txt");
    }
    else 
    {
        myfile.open("stock4.txt");
    }

    if(myfile.is_open())
    {
        while(getline(myfile,line))
        {
            istringstream iss(line); 
            double val;
            while(iss>>sub>>one >> second >> third >> fourth >> fifth >>  val)
            {
                Index *ind=firstPtr;
                while(ind!=0)
                {
                if(sub==symb2&&ind->symbol==symb2) 
                {
                    available=true;
                    if(ind->number<num) 
                    {
                        cout<<"Transaction failed. You do not have enough shares to sell.\n";
                    }
                    else
                    {
                    if(min_pershare<val) 
                    {
                        double total_val=num*val;
                        ofstream myfile_in;
                        myfile_in.open("stock_transaction_history.txt",ios::app); 
                        if(myfile_in.is_open())
                        {
                            myfile_in<<"Sell\t";
                            myfile_in<<symb2<<"\t";
                            myfile_in<<num<<"\t";
                            myfile_in<<""<<val<<"\t";
                            myfile_in<<getTime()<<endl;
                            myfile_in.close();
                        }
                        else
                        {
                            cout<<"Transaction failed. Unable to open file"<<endl;
                            break;
                        }

                        ofstream myfile3;

                        cash_balance=cash_balance+total_val; 
                        Index *ptr=firstPtr;
                        while(ptr!=0)
                        {
                            if(ptr->symbol==symb2)
                            {
                                ptr->number=ptr->number-num;
                                if(ptr->number==0) 
                                {
                                    eraseIndex(symb2);
                                }
                            }
                            ptr=ptr->next;
                        }
                    }
                    else
                    {
                        cout<<"Transaction failed. The amount you entered is greater than the price of the stock"<<endl;
                    }
                    }

                }
                ind=ind->next;
                }
            }
        }
    }
    if(available==false)
    {
        cout<<"Transaction failed. The stock you want to sell is not available\n";
    }
    }
    else
        cout<<"You have no shares to sell\n";

}

void stockaccount::current_portfolio()
{
    Index *ptr4=firstPtr;
    string sym;
    int num=0;
    double sum=0;
    if(ptr4==0) 
    {
        cout<<"";
        return;
    }
    else
    {
        
        while(ptr4!=0)
        {
            sym=ptr4->symbol;
            num=ptr4->number;
            if(num!=0)
            {
            fstream myfile; 
            string line,sub;
            bool stock=false;

            int i=rand()%4;
    if(i==0)
    {
        myfile.open("stock1.txt");
    }
    else if(i==1)
    {
        myfile.open("stock2.txt");
    }
    else if(i==2)
    {
        myfile.open("stock3.txt");
    }
    else 
    {
        myfile.open("stock4.txt");
    }
            if(myfile.is_open())
            {
                while(getline(myfile,line))
                {
                    istringstream iss(line); 
            double val;
            string val1;
            string val2;
            string val3;
            string val4;
            double val5;
            while(iss>>sub>>val>>val1>>val2>>val3>>val4>>val5)
                    {
                      if(sub==sym)
                      {
                          sum=val5*num;
                          total_portfolio_value=sum+cash_balance;
                          cout<<"\nCash balance = $"<<cash_balance<<"\n";
                          cout<<"\nSymbol\tCompany\t\t\t\tNumber\tPrice\tTotal\n";
                          cout<<""<<sub<< "\t" << val << "" << val1 << " " << val2 << " " << val3 << "" << val4 << "\t\t" << num <<"\t" << val5 << "\t" << sum << endl;
                          cout<<"\nTotal portfolio value : $"<<total_portfolio_value<<endl;
                          stock=true;
                          break;
                      }
                    }
                }

            }
            }

            ptr4=ptr4->next;
        }
    }
}


void stockaccount::addIndex(Index *xIndex) 
{
    if(firstPtr==0)
    {
        firstPtr=lastPtr=xIndex;
    }
    else
    {
        xIndex->next=firstPtr;
        firstPtr->prev=xIndex;
        firstPtr=xIndex;
        xIndex->prev=NULL;
    }
}


void stockaccount::eraseIndex(string ind) 
{
    Index *ptr=firstPtr;
    Index *temp1=0;
    Index *temp2=0;
    if(firstPtr==0)
    {
    }
    while(ptr!=0) 
    {
        if(ptr->symbol==ind)
        {
            break;
        }
        else
        {
            ptr=ptr->next;
        }
    }
    temp1=ptr->prev; 
    temp2=ptr->next;
    if(ptr==0)
    {
        cout<<"Stock not found\n";
    }
    else
    {
        if(ptr==firstPtr)
        {
            if(ptr==lastPtr)
            {
                cout<<"Selling the last stock you own\n";
                firstPtr=lastPtr=0;
            }
            else
                firstPtr=firstPtr->next;

        }
        else
        {
            temp1->next=ptr->next;
            temp2->prev=ptr->prev;
        }
        delete ptr;
    }

}

void stockaccount::transac_history()
{
    ifstream myfile;
    string line;
    myfile.open("stock_transaction_history.txt",ios::app);
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

double stockaccount::getBalance()
{
    return cash_balance;
}

void stockaccount::setBalance(double blnc)
{
    cash_balance=blnc;
}

void stockaccount::update_stocks() 
{
    bool stock=false;
    ifstream myfile;
    myfile.open("stock_transaction_history.txt");
    string line,event,stock_symb,date;
    int number_shares;
    double value_perShare, total_value;
    while(getline(myfile,line))
    {
        istringstream iss(line);
        if (myfile.eof())
            break;
        while(iss>>event>>stock_symb>>number_shares>>value_perShare>>total_value>>date)
        {

            if(event=="Buy") 
            {
                Index *ptr=firstPtr;
               
                while(ptr!=0)
                {
                    if(ptr->symbol==stock_symb)
                    {
                        stock=true;
                        ptr->number=number_shares+ptr->number;
                    }
                    else
                        stock=false;
                    ptr=ptr->next;
                }
                if(stock==false)
                {
                    Index *xIndex=new Index(stock_symb,number_shares);
                    addIndex(xIndex); 
                }
        
            }
            else if(event=="Sell")
            {
            
                Index *ptr5=firstPtr;
                stock=false;
                while(ptr5!=0)
                {
                    if(ptr5->symbol==stock_symb)
                    {
                        stock=true;
                        ptr5->number=ptr5->number-number_shares;
                        if(ptr5->number==0)
                        {
                            eraseIndex(stock_symb);
                        }
                    }
                    ptr5=ptr5->next;
                }
            }
    
        }
    

    }
}

Index *stockaccount::sortList(Index *first,Index *second)
{
    if(!first)
        return second;
    if(!second)
        return first;

    ifstream myfile;
    string line,sub;
    double temp_value1,temp_value2;

     int i=rand()%4;
    if(i==0)
    {
        myfile.open("stock1.txt");
    }
    else if(i==1)
    {
        myfile.open("stock2.txt");
    }
    else if(i==2)
    {
        myfile.open("stock3.txt");
    }
    else 
    {
        myfile.open("stock4.txt");
    }
    while(getline(myfile,line))
    {
        istringstream iss(line); 
        double val;

        while(iss>>sub>>val)
        {
            if(sub==first->symbol)
            {
                temp_value1=val;
            }
            if(sub==second->symbol)
            {
                temp_value2=val;
            }
        }

    }

    if(((first->number)*temp_value1) > ((second->number)*temp_value2)) 
    {
        first->next=sortList(first->next,second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        second->next = sortList(first,second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }

}

Index *stockaccount::split(Index *first)
{
    Index *temp1=first;
    Index *temp2=first;
    Index *temp;

    while(temp1->next&&temp1->next->next)
    {
        temp1=temp1->next->next;
        temp2=temp2->next;
    }
    temp=temp2->next;
    temp2->next=NULL;
    return temp;
}


void stockaccount::sort_wrapper() 
{
    if(firstPtr==0)
    {

    }
    else
    {
        firstPtr=merge_sort(firstPtr);
    }

}

Index *stockaccount::merge_sort(Index *firstN) 
{
    if(!firstN || !firstN->next)
    {
        return firstN;
    }
    Index *second=split(firstN);
    firstN=merge_sort(firstN);
    second=merge_sort(second);

    return sortList(firstN,second);
}