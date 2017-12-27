
#include<iostream>
#include<cstdlib>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<sstream>
#include<time.h>

#include "stockportfolio.h"
#include "bankAccount.h"
#include "account.h"

using namespace std;

int main()
{
    int choice=999,s_choice=999,b_choice=999;
    double deposit, withdraw;
    stockaccount stk_obj; 
    bankAccount bank_obj;

    fstream myfile;
    string line;
    double sub;

    stk_obj.update_stocks(); 
    stk_obj.current_portfolio(); 
    cout<<"\nWelcome to the Account Management System.\n";
    while(choice!=3)
    {
        cout<<"\nPlease select an account to access \n\t1. Stock Portfolio Account \n\t2. Bank Account \n\t3. Exit";
        cout<<"\n\tYour selection:\t ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            {
            cout<<"\nPlease select an option \n\t1. Display current price for a stock symbol";
            cout<<"\n\t2. Buy stock \n\t3. Sell stock \n\t4. Display current portfolio \n\t5. Display transactions history";
            cout<<"\n\t6. Return to main menu";
            cout<<"\n\tYour selection:\t ";
            cin>>s_choice;

            while(s_choice!=6)
            {
                switch (s_choice)
                {
                case 1:
                    stk_obj.display(); 
                    break;
                case 2:
                    stk_obj.buy_shares(); 
                    break;
                case 3:
                    stk_obj.sell_shares(); 
                    break;
                case 4:
                    stk_obj.sort_wrapper(); 
                    stk_obj.current_portfolio();
                    break;
                case 5:
                    cout<< "\nAction\tSymbol\tShares\tPrice\tTime" <<endl;
                    stk_obj.transac_history();
                    break;
                case 6:
                    break;
                default:
                cout<<"Please enter a number in between 1 and 7"<<endl;
                break;
            }
            cout<<"\nPlease select an option \n\t1. Display current price for a stock symbol";
            cout<<"\n\t2. Buy stock \n\t3. Sell stock \n\t4. Display current portfolio \n\t5. Display transactions history";
            cout<<"\n\t6. Return to main menu";
            cout<<"\n\tYour selection:\t ";
            cin>>s_choice;
            }
            }
            break;


        case 2:
            {
            cout<<"\nPlease select an option \n\t1. View account balance \n\t2. Deposit money \n\t3. Withdraw money";
            cout<<"\n\t4. Display transactions history \n\t5. Return to previous menu"<<endl;
            cout<<"\tYour selection:\t ";
            cin>>b_choice;
            while(b_choice!=5)
            {
            switch(b_choice)
            {
            case 1:
                bank_obj.view_balance();
                break;
            case 2:
                cout<<"\nEnter amount to be deposit: ";
                cin>>deposit;
                bank_obj.deposit_bank(deposit);
                break;
            case 3:
                cout<<"\nEnter amount to be withdrawn: ";
                cin>>withdraw;
                bank_obj.withdraw_bank(withdraw);
                break;
            case 4:
                cout<< "\nAction\t\tAmount\tCash Balance\tDate\t\tTime" <<endl;
                bank_obj.print_bankHistory();
                break;
            case 5:
                break;
            default:
                cout<<"Please enter a number in between 1 and 5"<<endl;
                break;
            }
            cout<<"\nPlease select an option \n\t1. View account balance \n\t2. Deposit money \n\t3. Withdraw money";
            cout<<"\n\t4. Display transactions history \n\t5. Return to previous menu"<<endl;
            cout<<"\tYour selection:\t ";
            cin>>b_choice;
            }
            }
            break;


        case 3:
            break;
        default:
            cout<<"Please enter a number in between 1 and 3"<<endl;
            break;
            }

    }

    cout << "\nProgram terminated." << endl;
    system("PAUSE");
    return 0;
}