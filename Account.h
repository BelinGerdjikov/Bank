#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>

class Account {
protected:
	static int number_of_account;
	std::string security_number;
	std::string name;
	double balance;
public:

	std::string get_security() const{ return security_number; }

	

	virtual void display() = 0;

	std::string get_name() { return name; }

	friend std::ostream& operator<<(std::ostream& os,const Account& acc) {
		return acc.print(os);
	}

	virtual std::ostream& print(std::ostream& os)const =0;


	Account(std::string name1, double balance1=0)
		:name{ name1 }, balance{ balance1 }
	{number_of_account++; }

	virtual bool deposit(double amount) = 0 {
		if (amount >= 0) {
			balance += amount;
			return 1;
		}
		else {
			return 0;
		}
	}

	virtual bool withdraw(double amount) = 0 {
		if (balance - amount >= 0) {
			balance -= amount;
			return 1;
		}
		else {
			return 0;
		}
	}

	double get_balance() { return balance; }

	virtual ~Account() {
		number_of_account--;
	}


	virtual std::string Account_type() = 0;
};

#endif ACCOUNT_H
