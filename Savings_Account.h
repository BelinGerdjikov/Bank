#ifndef SAVING_ACCOUNT
#define SAVING_ACCOUNT
#include "Account.h"
class Savings_Account:public Account {
protected:
	double int_rate;
public:

	friend std::istream& operator>>(std::istream& is,Savings_Account& acc) {
		std::string line;
		getline(is, line);
		getline(is, acc.name);
		is>> acc.balance >> acc.int_rate;
		return is;
	}

	virtual void display() {
		std::cout << "Account owner: " << name << "  Account type: Savings Account" << std::endl;
		std::cout << "Security number " << security_number << std::endl;
		std::cout << "Balance: " << balance << std::endl;
		std::cout << "Intrest rate: " << int_rate << "%" << std::endl;
	}

	Savings_Account(std::string name, double balance = 0, double int_rate1 = 5)
		:Account(name, balance),int_rate{int_rate1}
	{security_number = std::to_string(number_of_account); security_number += "S"; }

	Savings_Account(const Savings_Account& source)
		:Account{source.name,source.balance}
	{
		int_rate = source.int_rate;
		security_number = source.security_number;
	}


	virtual bool deposit(double amount)override {
		amount +=(amount* (int_rate/100));

		return Account::deposit(amount);
	}

	virtual bool withdraw(double amount)override {
		return Account::withdraw(amount);
	}

	
	virtual std::ostream& print(std::ostream& os) const {
		os << security_number << std::endl;
		os << name << std::endl;
		os << balance << " " << int_rate;
		return os;
	}

	virtual std::string Account_type() {
		return "S";
	}

	virtual ~Savings_Account() = default;
};
#endif SAVING_ACCOUNT
