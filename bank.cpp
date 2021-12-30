#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<map>
using namespace std;
#define min_balance 500
class insufficientfunds{};
class account{
    private:
    long accountnumber;
    string firstname;
    string lastname;
    float balance;
    static long nextaccountnumber;
    public:
    account(){}
    account(string fname,string lname,float balance);
    string getfirstname(){
        return firstname;
    }
    string getlastname(){
        return lastname;
    }
    long getaccno(){
        return accountnumber;
    }
    float getbalance(){
        return balance;
    }
    void deposit(float amount);
    void withdraw(float amount);
    static void setlastaccountnumber(long accountnumber);
    static long getlastaccountnumber();
    friend ofstream & operator<<(ofstream &ofs,account &acc);
    friend ifstream & operator>>(ifstream &ifs,account &acc);
    friend ostream & operator<<(ostream &os,account &acc);

};
long account::nextaccountnumber=0;
class bank{
    private:
    map<long,account> accounts;
    public:
    bank();
    account openaccount(string fname,string lname,float balance);
    account balanceenquiry(long accountnumber);
    account withdraw(long accountnumber,float amount);
    account deposit(long accountnumber,float balance);
    void closeaccount(long accountnumber);
    void showallaccounts();
    ~bank();
    
};
int main()
{
    bank b;
    account acc;
    int choice;
    string fname;string lname;
    long accountnumber;float balance;
    float amount;
    cout<<"     BANKING SYSTEM     "<<endl;
    do{
        cout<<"\n\tselect one option below";
        cout<<"\n\t1 open an account";
        cout<<"\n\t2 balance enquiry";
        cout<<"\n\t3 deposit";
        cout<<"\n\t4 withdrawal";
        cout<<"\n\t5 close an account";
        cout<<"\n\t6 show all accounts";
        cout<<"\n\t7 quit";
        cout<<"\nenter your choice : ";
        cin>>choice;
        switch(choice)
        {
            case 1:
            cout<<"enter first name: ";
            cin>>fname;
            cout<<"enter last name: ";
            cin>>lname;
            cout<<"inter intital balance: ";
            cin>>balance;
            acc=b.openaccount(fname,lname,balance);
            cout<<endl<<"Congradulation Account is Created"<<endl;
            cout<<acc;
            break;
            case 2: 
            cout<<"enter account number : ";
            cin>>accountnumber;
            acc=b.balanceenquiry(accountnumber);
            cout<<endl<<"your account details"<<endl;
            cout<<acc;
            break;
            case 3:
            cout<<"enter account number: ";
            cin>>accountnumber;
            cin>>amount;
            acc=b.deposit(accountnumber,amount);
            cout<<endl<<"amount is deposited"<<endl;
            cout<<acc;
            break;
            case 4:
            cout<<"enter account number: ";
            cin>>accountnumber;
            cin>>amount;
            acc=b.withdraw(accountnumber,amount);
            cout<<endl<<"amount is withdrawn"<<endl;
            cout<<acc;
            break;
            case 5:
            cout<<"enter account number: ";
            cin>>accountnumber;
            b.closeaccount(accountnumber);
            cout<<endl<<"accoutn is closed"<<endl;
            cout<<acc;
            case 6:
            b.showallaccounts();
            break;
            case 7:
            break;
            default:
            cout<<"\nenter correct choice";
            exit(0);
        }
    }while(choice!=7);
    return 0;
}
 
account::account(string fname,string lname,float balance){
    nextaccountnumber++;
    accountnumber=nextaccountnumber;
    firstname=fname;
    lastname=lname;
    this->balance=balance;
}
void account::deposit(float amount){
        balance+=amount;
    }
void account::withdraw(float amount){
    if(balance-amount<min_balance)
    throw insufficientfunds();
    balance-=amount;
}
void account::setlastaccountnumber(long accountnumber){
    nextaccountnumber=accountnumber;
}
long account::getlastaccountnumber(){
    return nextaccountnumber;
}
ofstream & operator<<(ofstream &ofs,account &acc){
    ofs<<acc.accountnumber<<endl;
    ofs<<acc.firstname<<endl;
    ofs<<acc.lastname<<endl;
    ofs<<acc.balance<<endl;
    return ofs;
}
ifstream & operator>>(ifstream &ifs,account &acc){
    ifs>>acc.accountnumber;
    ifs>>acc.firstname;
    ifs>>acc.lastname;
    ifs>>acc.balance;
    return ifs;
}
ostream & operator<<(ostream &os,account &acc){
    os<<"first name : "<<acc.getfirstname()<<endl;
    os<<"last name : "<<acc.getlastname()<<endl;
    os<<"account number : "<<acc.getaccno()<<endl;
    os<<"account balance : "<<acc.getbalance()<<endl;
    return os;
}

bank::bank(){
    account account1;
    ifstream infile;
    infile.open("bank.data");
    if(!infile)
    {
        cout<<"error is opening, file not found!";
        return;
    }
    while(!infile.eof()){
        infile>>account1;
        accounts.insert(pair<long,account>(account1.getaccno(),account1));
    }
    account::setlastaccountnumber(account1.getaccno());
    infile.close();
}
account bank::openaccount(string fname,string lname,float balance){
    ofstream outfile;
    account account1(fname,lname,balance);
    accounts.insert(pair<long,account>(account1.getaccno(),account1));
    outfile.open("bank.data",ios::trunc);
    map<long,account>::iterator itr;
    for(itr=accounts.begin();itr!=accounts.end();itr++){
        outfile<<itr->second;
    }
    outfile.close();
    return account1;
}
account bank::balanceenquiry(long accountnumber){
    map<long,account>::iterator itr=accounts.find(accountnumber);
    return itr->second;
}
account bank::deposit(long accountnumber,float amount){
    map<long,account>::iterator itr=accounts.find(accountnumber);
    itr->second.deposit(amount);
    return itr->second;
}
account bank::withdraw(long accountnumber,float amount){
    map<long,account>::iterator itr=accounts.find(accountnumber);
    itr->second.withdraw(amount);
    return itr->second;
}
void bank::closeaccount(long accountnumber){
    map<long,account>::iterator itr=accounts.find(accountnumber);
    cout<<"account deleted "<<itr->second;
    accounts.erase(accountnumber);
}
void bank::showallaccounts(){
    map<long,account>::iterator itr;
    for(itr=accounts.begin();itr!=accounts.end();itr++){
        cout<<"account "<<itr->first<<endl<<itr->second<<endl;
    }
}
bank::~bank(){
    ofstream outfile;
    outfile.open("bank.data",ios::trunc);
    map<long,account>::iterator itr;
    for(itr=accounts.begin();itr!=accounts.end();itr++){
        outfile<<itr->second;
    }
    outfile.close();
}