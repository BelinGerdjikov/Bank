#ifndef TRUST_ACCOUNT
#define TRUST_ACCOUNT
#include "Savings_Account.h"

class Trust_Account:public Savings_Account {
private:
	const int max_withdraws = 4;
	const double max_withdraw_percent = 20;
	const double bonus_deposit=50;
	int num_of_withdraws;
public:
	friend std::istream& operator>>(std::istream& is, Trust_Account& acc) {
		std::string line;
		getline(is, line);
		getline(is, acc.name);
		is >> acc.balance >> acc.int_rate>>acc.num_of_withdraws;
		return is;
	}

	virtual void display() {
		std::cout<<"Account owner: "<<name <<"  Account type: Trust Account"<< std::endl;
		std::cout << "Security number " << security_number << std::endl;
		std::cout<<"Balance: "<<balance << std::endl;
		std::cout<<"Intrest rate: "<<int_rate<<"%" <<std::endl;
		std::cout<<"Available withdraws: "<<max_withdraws-num_of_withdraws<< std::endl;
	}
	Trust_Account(std::string name,double balance=0,double int_rate=5,int num_of_withdraws1=0) 
		:Savings_Account{name,balance,int_rate},num_of_withdraws{num_of_withdraws1}
	{security_number = std::to_string(number_of_account); security_number += "T"; }

	Trust_Account(const Trust_Account&source)
		:Savings_Account{ source.name,source.balance,source.int_rate}
	{
		num_of_withdraws = source.num_of_withdraws;
		security_number = source.security_number;
	}

	virtual bool deposit(double amount)override {
		if (amount >= 5000) {
			amount += bonus_deposit;
		}
		return Savings_Account::deposit(amount);
	}

	virtual bool withdraw(double amount)override {
		if (num_of_withdraws < max_withdraws && amount <= balance * (max_withdraw_percent / 100)) {
			num_of_withdraws++;
			return Savings_Account::withdraw(amount);
		}
		else {
			return false;
		}

	}
	

	virtual std::ostream& print(std::ostream& os)const {
		os << security_number << std::endl;
		os << name << std::endl;
		os<< balance << " " << int_rate << " " << num_of_withdraws;
		return os;
	}

	virtual std::string Account_type() {
		return "T";
	}

	virtual ~Trust_Account() = default;

};
#endif TRUST_ACCOUNT