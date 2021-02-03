#ifndef CHEACKING_ACCOUNT
#define CHEACKING_ACCOUNT
#include "Account.h"
class Checking_Account:public Account {
private:
	const double cheacking_tax = 3.00;
public:
	friend std::istream& operator>>(std::istream& is, Checking_Account& acc) {
		std::string line;
		getline(is, line);
		getline(is, acc.name);
		is >> acc.balance;
		return is;
	}

	virtual void display() {
		std::cout << "Account owner: " << name << "  Account type: Savings Account" << std::endl;
		std::cout << "Security number " << security_number << std::endl;
		std::cout << "Balance: " << balance << std::endl;
	}

	Checking_Account(std::string name,double amount=0)
		:Account(name,amount)
	{security_number = std::to_string(number_of_account); security_number += "C";}

	Checking_Account(const Checking_Account& source)
		:Account{ source.name,source.balance}
	{
		security_number = source.security_number;
	}

	virtual bool deposit(double amount)override {
		return Account::deposit(amount);
	}

	virtual bool withdraw(double amount)override {
		amount += cheacking_tax;
		return Account::withdraw(amount);
	}
	

	virtual std::ostream& print(std::ostream& os)const {
		os << security_number << std::endl;
		os << name << std::endl; 
		os << " " << balance;
		return os;
	}

	virtual std::string Account_type() {
		return "C";
	}

	virtual ~Checking_Account() = default;
};

#endif CHEAKING_ACCOUNT
