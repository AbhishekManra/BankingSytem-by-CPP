#include <bits/stdc++.h>
#include <map>
#include <fstream>
using namespace std;
#define MIN_AMT 500
class Account{
    string name;
    float balance;
    long AccountNumber;
    static long nextAccountNumber;
    public:
    string getName(){return name;}
    float getblance(){return balance;}
    long getAccountNumber(){return AccountNumber;}
    void deposit(float amount);
    void WithDraw(float amount);
    void setLastAccountNumber(long AccountNumber){nextAccountNumber = AccountNumber; }

    Account(){}; // non parameterized constructor
    Account(string name , float balance); // parameterized constructor
    friend ofstream & operator<<(ofstream & ofs , Account & a);
    friend ifstream & operator>>(ifstream & ifs , Account & a);
    friend ostream & operator<<(ostream & out , Account & a);
};

long Account::nextAccountNumber = 0;

class Bank{
    map<long,Account> accounts;
    public:
    Bank();
    Account OpenAccount(string name , float balance);
    Account Enquiry(long AccountNumber);
    Account Deposit(long AccountNumber , float amount);
    Account WithDraw(long AccountNumber , float amount);
    void CloseAccount(long AccountNumber);
    void showAllAccounts();
    ~Bank();
};

int main(){
    Bank b;
    Account account;
    string name;
    float balance;
    int choice;

    float amount;
    long accountNumber;
    do
        {
        cout<<"\n\tSelect one option below ";
        cout<<"\n\t1 Open an Account";
        cout<<"\n\t2 Balance Enquiry";
        cout<<"\n\t3 Deposit";
        cout<<"\n\t4 Withdrawal";
        cout<<"\n\t5 Close an Account";
        cout<<"\n\t6 Show All Accounts";
        cout<<"\n\t7 Quit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"Enter Name: ";
                cin>>name;
                cout<<"Enter initil Balance: ";
                cin>>balance;
                account = b.OpenAccount(name , balance);
                cout<<endl<<"Congradulation Account is Created"<<endl;
                cout << account;
            break;
            case 2:
                cout<<"Enter Account Number:";
                cin>>accountNumber;
                cout<<endl<<"Your Account Details"<<endl;
                account = b.Enquiry(accountNumber);
                cout << account;
            break;
            case 3:
                cout<<"Enter Account Number:";
                cin>>accountNumber;
                cout<<"Enter Balance:";
                cin>>amount;
                account = b.Deposit(accountNumber , amount);
                cout<<endl<<"Amount is Deposited"<<endl;
                cout << account;
            break;
            case 4:
                cout<<"Enter Account Number:";
                cin>>accountNumber;
                cout<<"Enter Balance:";
                cin>>amount;
                account = b.WithDraw(accountNumber,amount);
                cout<<endl<<"Amount Withdrawn"<<endl;
                cout << account;
            break;
            case 5:
                cout<<"Enter Account Number:";
                cin>>accountNumber;
                b.CloseAccount(accountNumber);
                cout<<endl<<"Account is Closed"<<endl;

            case 6:
                b.showAllAccounts();
            break;
            case 7: break;
            default:
            cout<<"\nEnter corret choice";
            exit(0);
        }
        }while(choice!=7);
return 0 ;
}

// for constructing the methods of the class
Account::Account(string name , float balance){
    nextAccountNumber++;
    this->name = name;
    this->balance = balance;
    this->AccountNumber = nextAccountNumber;
}
ofstream & operator<<(ofstream & ofs , Account & a){
    ofs << a.AccountNumber << endl;
    ofs << a.name << endl;
    ofs << a.balance << endl;
    return ofs;
}
ifstream & operator>>(ifstream & ifs , Account & a){
    ifs >> a.AccountNumber ;
    ifs >> a.name ;
    ifs >> a.balance ;
    return ifs;
}
void Account::deposit(float amount){
    balance+=amount;
}
void Account::WithDraw(float amount){
    if(balance-amount<=500){
        cout << "invalid" << endl;
    }else{
    balance-=amount;
    }
}
ostream & operator<<(ostream & out , Account & a){
    out << "Account Number : " << a.AccountNumber << endl;
    out << "Account holder Name : " << a.name << endl;
    out << "Account Holder Balance : " << a.balance << endl;
    return out;
}
Bank::Bank(){
    Account account;
    ifstream ifs("BankDB.txt");
    while (!ifs.eof())
    {   
        ifs>>account;
        accounts.insert(pair<long,Account>(account.getAccountNumber(),account));
    }
    account.setLastAccountNumber(account.getAccountNumber());
    ifs.close();
}
Account Bank::OpenAccount(string name , float balance){
    Account account(name, balance);
    accounts.insert(pair<long,Account>(account.getAccountNumber(),account));
    map<long,Account>::iterator itr;
    ofstream ofs("BankDB.txt",ios::trunc);
    for (itr=accounts.begin();itr!=accounts.end();itr++)
    {
        ofs << itr->second;
    }
    ofs.close();
    return account;
}
Account Bank::Deposit(long AccountNumber , float amount){
    map<long,Account>::iterator itr=accounts.find(AccountNumber);
    itr->second.deposit(amount);
    return itr->second;
}
Account Bank::WithDraw(long AccountNumber , float amount){
    map<long,Account>::iterator itr=accounts.find(AccountNumber);
    itr->second.WithDraw(amount);
    return itr->second;
}
Account Bank::Enquiry(long AccountNumber){
    map<long,Account>::iterator itr=accounts.find(AccountNumber);
    return itr->second;
}
void Bank::CloseAccount(long AccountNumber){
    map<long,Account>::iterator itr=accounts.find(AccountNumber);
    cout << itr->second;
    cout << "This account is Suspended" <<endl;

    accounts.erase(AccountNumber);
}
void Bank::showAllAccounts(){
    map<long,Account>::iterator itr;
    for (itr=accounts.begin();itr!=accounts.end();itr++)
    {
        cout << "------------------ |Vijay Malya Bank ltd.| --------------------" << endl;
        cout << itr->second;
        cout << "--------------------------------------" << endl;
    }
}
Bank::~Bank(){
    ofstream ofs("BankDB.txt",ios::trunc);
    map<long,Account>::iterator itr;
    for (itr=accounts.begin();itr!=accounts.end();itr++)
    {
        ofs << itr->second;
    }
    ofs.close();
}