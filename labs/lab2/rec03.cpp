/*
  MarcAnthony Williams
  rec03_start.cpp
  2024 Fall
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
     struct Account{
          int account_num;
          string account_name;
     };
// Task 2
// Define an Account class (use a different name than in Task 1)

class Deloitte{
     public:
         Deloitte(const int account_num, const string& name) : account_num(account_num), account_name(name){}

         const int& get_account_num() const{
          // Mark methods (and functions) that get or inspect const.
          //Const before to ensure data type doesn't change. 
          return account_num;
         }
         const string& get_account_name() const{
          return account_name;
         }

         friend ostream& operator<<(ostream& os, const Deloitte& deloitte);
     private:
          int account_num;
          string account_name;
};

ostream& operator<<(ostream& os, const Deloitte& deloitte){
     //os << deloitte.get_account_name() << " " << deloitte.get_account_num() << endl;
     os << deloitte.account_name << " " << deloitte.account_num << endl;
     return os;
}
// Task 3
// Define another Account class (use a different name than in Task
// 1&2) and a Transaction class. The Transaction class is to be
// defined outside of the Account class, i.e. it is not "nested".

class Transaction{
     public:
          Transaction(const string& type, const int& amt) : command(type), amount(amt) {}
          friend ostream& operator<<(ostream& os, const Transaction& ts);
     private:
          // Deposit or Withdrawal
          string command;
          int amount;

};
ostream& operator<<(ostream& os, const Transaction& ts){
     if(ts.command == "W"){
          os << "\t Withdrawal " << ts.amount;
     }else{
          os << "\t Deposit " << ts.amount;
     }

     return os;
}

class CapitalOne{
     friend ostream& operator<<(ostream& os, const CapitalOne& c_one);
     public:
          // class Transaction;
          
          CapitalOne(const string& name, const int account_num) : account_name(name), account_num(account_num){}

          void deposit(const int& deposit_amount){
              balance += deposit_amount;
              transactions.emplace_back("D", deposit_amount);
          }

          void withdrawal(const int withdraw_amt){
               
               if(can_withdraw(withdraw_amt) == false){
                    cout << "Account# " << account_num << " has only " << balance << ". Insufficient for withdrawal of "
                    << withdraw_amt << endl;
               }else{
                    balance -= withdraw_amt;
                    transactions.emplace_back("W", withdraw_amt);
               }
               
          }

          const int get_account_num() const{
               return account_num;
          }
          

     private:
          bool can_withdraw(const int withdraw_amt) const{
               if(balance - withdraw_amt < 0){
                    return false;
               }else{return true;}
          }
          int balance = 0;
          vector<Transaction> transactions;
          string account_name;
          int account_num;
};


ostream& operator<<(ostream& os, const CapitalOne& c_one){
     os << c_one.account_name << " " << c_one.account_num << ":" << endl; // moe 6
     for(const Transaction& ts : c_one.transactions){
          os << ts << endl;
     }
     return os;
}

// Task 4
// Define yet another Account class, this time with a nested public
// Transaction class. Again use a different name for the Account class
// than in the previous Tasks. Note that it is NOT necessary to rename
// the Transaction class, since it is nested.



class BankofAmerica{
     friend ostream& operator<<(ostream& os, const BankofAmerica& boa);
     public:
          class Transaction{
               friend ostream& operator<<(ostream& os, const Transaction& ts);
               public:
                    Transaction(const string& type, const int& amt) : command(type), amount(amt) {}
                    
               private:
                    // Deposit or Withdrawal
                    string command;
                    int amount;
          };

         BankofAmerica(const string& name, const int account_num) : account_name(name), account_num(account_num){}

          void deposit(const int& deposit_amount){
              balance += deposit_amount;
              transactions.emplace_back("D", deposit_amount);
          }

          void withdrawal(const int withdraw_amt){
               if(can_withdraw(withdraw_amt) == false){
                    cout << "Account# " << account_num << " has only " << balance << ". Insufficient for withdrawal of "
                    << withdraw_amt << endl;
               }else{
                    balance -= withdraw_amt;
                    transactions.emplace_back("W", withdraw_amt);
               }
               
          }

          const int get_account_num() const{
               return account_num;
          }

          void display_transactions() const{
               for(const Transaction& ts : transactions){
                    cout << ts << endl;
               }
          }

     private:
          bool can_withdraw(const int withdraw_amt){
               if(balance - withdraw_amt < 0){
                    return false;
               }else{return true;}
          }
          int balance = 0;
          vector<Transaction> transactions;
          string account_name;
          int account_num;
};


ostream& operator<<(ostream& os, const BankofAmerica& boa){
     os << boa.account_name << " " << boa.account_num << ":" << endl; // moe 6
     for(const BankofAmerica::Transaction& ts : boa.transactions){
          os << ts << endl;
     }

     return os;
}

ostream& operator<<(ostream& os, const BankofAmerica::Transaction& ts){
     if(ts.command == "W"){
          os << "\t Withdrawal " << ts.amount;
     }else{
          os << "\t Deposit " << ts.amount;
     }

     return os;
}

// Task 5
// Same as Task 4, but make the Transaction nested class private.
// Yes, the Account class needs a new name but, again, the Transaction
// class does not.


int main() {

    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n"
         << "Filling vector of struct objects, define a local struct instance\n"
         << "and set fields explicitly:\n";
     vector<Account> accounts;
     ifstream ifs;
     string name;
     int account_num;

     ifs.open("accounts.txt");
     if(!ifs){
          cerr << "Cannot open file." << endl;
     }

     while(ifs >> name >> account_num){
          Account temp;
          temp.account_name = name;
          temp.account_num = account_num;
          accounts.push_back(temp);
     }
     
     ifs.close();

     for(const Account& account : accounts){
          cout << account.account_name << " " << account.account_num << endl;
     } cout << endl;

    //      1b
    cout << "Task1b:\n"
         << "Filling vector of struct objects, using {} initialization:\n";
         accounts.clear();
          do{
               ifs.open("accounts.txt");
               if(!ifs){
                    cerr << "Cannot open file." << endl;
               }
          }while(!ifs);

          while(ifs >> name >> account_num){
               Account temp{account_num, name};
               accounts.push_back(temp);
          }ifs.close();

          for(const Account& account : accounts){
               cout << account.account_name << " " << account.account_num << endl;
          } cout << endl;

    //==================================
    // Task 2: account as class

    vector<Deloitte> deloitte_accounts;


    //      2a
    cout << "==============\n";
    cout << "\nTask2a:"
         << "\nFilling vector of class objects, using local class object:\n";
         do{
               ifs.open("accounts.txt");
               if(!ifs){
                    cerr << "Cannot open file." << endl;
               }
          }while(!ifs);

          while(ifs >> name >> account_num){
               Deloitte temp(account_num,name);
               deloitte_accounts.push_back(temp);
          }
          
          ifs.close();

          for(const Deloitte& acc : deloitte_accounts){
               cout << acc.get_account_name() << " " << acc.get_account_num() << endl;
          }cout << endl;

    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
          for(const Deloitte& acc : deloitte_accounts){
               cout << acc;
          }
          
          cout << endl;


    

    cout << "\nTask2c:\n"
         << "output using output operator as friend without getters\n";
         for(const Deloitte& acc : deloitte_accounts){
               cout << acc;
          }cout << endl;


    cout << "\nTask2d:\n"
         << "Filling vector of class objects, using temporary class object:\n";
         deloitte_accounts.clear();
          do{
               ifs.open("accounts.txt");
               if(!ifs){
                    cerr << "Cannot open file." << endl;
               }
          }while(!ifs);

          while(ifs >> name >> account_num){
               deloitte_accounts.push_back(Deloitte(account_num, name));
          }ifs.close();

          for(const Deloitte& acc : deloitte_accounts){
               cout << acc;
          }cout << endl;
         

    
    cout << "\nTask2e:\n"
         << "Filling vector of class objects, using emplace_back:\n";
         deloitte_accounts.clear();
         do{
               ifs.open("accounts.txt");
               if(!ifs){
                    cerr << "Cannot open file." << endl;
               }
          }while(!ifs);

          while(ifs >> name >> account_num){
               deloitte_accounts.emplace_back(account_num, name);
          }ifs.close();

          for(const Deloitte& acc : deloitte_accounts){
               cout << acc;
          }cout << endl;


    
    cout << "==============\n"
         << "\n Task 3:\nAccounts and Transaction:\n";
         string command;
         string names;
         int account_number; 
         vector<CapitalOne> c_one_accounts;


         ifstream ifby;
         do{
               ifby.open("transactions.txt");
               if(!ifby){
                    cerr << "Could not open file";
               }
         }while(!ifby);
          
          while(ifby >> command){
               float amt = 0;
               if(command == "Account"){
                    ifby >> names >> account_number;
                    c_one_accounts.emplace_back(names, account_number);
               }
               else if(command == "Deposit"){
                    ifby >> account_num >> amt;
                    for(CapitalOne& c_one_acc : c_one_accounts){
                         if(c_one_acc.get_account_num() == account_num){
                              c_one_acc.deposit(amt);
                              break;
                         }
                    }
               }
               else if(command == "Withdraw"){
                    ifby >> account_num >> amt;
                    for(CapitalOne& c_one_acc : c_one_accounts){
                         if(c_one_acc.get_account_num() == account_num){
                              c_one_acc.withdrawal(amt);
                              break;
                         }
                    }
               }
          }

          for(const CapitalOne& c_one_acc : c_one_accounts){
               cout << c_one_acc;
               //c_one_acc.display_transactions();
          }
          cout << endl;


    cout << "==============\n"
         << "\nTask 4:\nTransaction nested in public section of Account:\n";
         vector<BankofAmerica> boa_accounts;


         ifstream iffy;
         do{
               iffy.open("transactions.txt");
               if(!iffy){
                    cerr << "Could not open file";
               }
         }while(!iffy);
          
          while(iffy >> command){
               float amt = 0;
               if(command == "Account"){
                    iffy >> names >> account_number;
                    boa_accounts.emplace_back(names, account_number);
               }
               else if(command == "Deposit"){
                    iffy >> account_num >> amt;
                    for(BankofAmerica& boa_acc : boa_accounts){
                         if(boa_acc.get_account_num() == account_num){
                              boa_acc.deposit(amt);
                              break;
                         }
                    }
               }
               else if(command == "Withdraw"){
                    iffy >> account_num >> amt;
                    for(BankofAmerica& boa_acc : boa_accounts){
                         if(boa_acc.get_account_num() == account_num){
                              boa_acc.withdrawal(amt);
                              break;
                         }
                    }
               }
          }

          for(const BankofAmerica& boa_acc : boa_accounts){
               cout << boa_acc;
               //boa_acc.display_transactions();
          }
          cout << endl;


    
    cout << "==============\n"
         << "\nTask 5:\nTransaction nested in private section of Account:\n";

    
}
