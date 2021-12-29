#include<iostream>
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
    string getfname(){
        return firstname;
    }
    string getlname(){
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
    
};
int main(){
    bank b;
    account acc;
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
    ifs>acc.lastname;
    ifs>>acc.balance;
    return ifs;
}
ostream & operator<<(ostream &os,account &acc){
    os<<"first name : "<<acc.getfname()<<endl;
    os<<"last name : "<<acc.getlname()<<endl;
    os<<"account number : "<<acc.getaccno()<<endl;
    os<<"account balance : "<<acc.getbalance()<<endl;
    return os;
}
    