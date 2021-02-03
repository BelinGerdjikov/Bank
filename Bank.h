#ifndef BANK_H
#define BANK_H
#include "Trust_Account.h"
#include "Checking_Account.h"
#include <vector>
#include <fstream>
#include <algorithm>
class Bank {
public:
	Bank(std::string file){
		std::ifstream fstream(file,std::ios::app);
		getline(fstream,Bank_name);
		std::string sec_number;
		char type;
		Account* temp;
		while (!fstream.eof()) {
			fstream >> sec_number;
			type = sec_number[sec_number.size() - 1];
			if (type == 'T') {
				{
					Trust_Account t1{ "XXXX" };
					fstream >> t1;
					temp = new Trust_Account(t1);
				}
				accounts.push_back(temp);
			}
			else if(type == 'S') {
				{
					Savings_Account t1{ "XXXX" };
					fstream >> t1;
					temp = new Savings_Account(t1);
				}
				accounts.push_back(temp);
			}
			else if(type=='C'){
				{
					Checking_Account t1{ "XXXX" };
					fstream >> t1;
					temp = new Checking_Account(t1);
				}
				accounts.push_back(temp);
			}
			sec_number = " ";
			
		}
	}

	void start() {
		int ans;
		do {
			std::cout << "                  " << Bank_name << std::endl;
			std::cout << "_________________________________________________________________" << std::endl;
			std::cout << "   1.Add Account" << std::endl;
			std::cout << "   2.Deposit to Account" << std::endl;
			std::cout << "   3.Withdraw for Account" << std::endl;
			std::cout << "   4.Remove Account" << std::endl;
			std::cout << "   5.Display" << std::endl;
			std::cout << "   6.Exit" << std::endl;
			//std::cout << "" << std::endl;
			//std::cout << "" << std::endl;
			
			
			validation(ans,6);
			system("cls");
			switch (ans){
			case 1:create_Account();
				break;
			case 2:deposit();
				break;
			case 3:withdraw();
				break;
			case 4:remove();
				break;
			case 5:display();
				break;
			case 0:std::cout << "Exit" << std::endl;
				break;

			}

		} while (ans != 0);
	}

	

	void display() {
		std::cout << "          "<<Bank_name<< std::endl;
		std::cout << "________________________" << std::endl;
		for (auto a : accounts) {
			a->display();
			std::cout << "" << std::endl;
		}
		system("pause");
		system("cls");
	}
private:

	
	std::vector<Account*>accounts;
	std::string Bank_name;


	void status(bool done,std::string temp,Account *acc=0) {
		if (done) {
			if (temp == "deposit") {
				std::cout << "Status of the deposit: Successful" << std::endl;
				std::cout << "Your balance is :" << acc->get_balance() << std::endl;
			}
			else if(temp == "withdraw"){
				std::cout << "Status of the withdraw: Successful" << std::endl;
				std::cout << "Your balance is :" << acc->get_balance() << std::endl;
			}
			else if (temp == "Account creation") {
				std::cout << "Status of the Account creation: Successful" << std::endl;
				std::cout << "Your Account is active and you can deposit" << std::endl;
			}
			else if (temp=="remove") {
				std::cout << "Status of the remove: Successful" << std::endl;
				std::cout << "The Account doesn't exist any more" << std::endl;
			}
			
		}
		else {
			if (temp == "deposit") {
				std::cout << "Status of the deposit: Unsuccessful" << std::endl;
				std::cout << "The Account was not found or you deposit a negative amount" << std::endl;
			}
			else if (temp == "withdraw") {
				std::cout << "Status of the withdraw: Unsuccessful" << std::endl;
				std::cout << "The Account was not found or you can't a withdraw that amount" << std::endl;
			}
			else if (temp == "Account creation") {
				std::cout << "Status of the Account creation: Unsuccessful" << std::endl;
				std::cout << "The Account already exist" << std::endl;
			}
			else if (temp == "remove") {
				std::cout << "Status of the remove: Unsuccessful" << std::endl;
				std::cout << "Account with that name and/or type doesn't exist"<< std::endl;
			}
		}
		system("pause");
		system("cls");
	}

	bool remove() {
		std::string name; int n;
		std::cout << "Type your full name" << std::endl;
		std::cin.ignore(INT_MAX, '\n');
		std::getline(std::cin, name);
		std::string account_type = display_account_types(n);

		int index = if_exist(name, account_type);
		int i = 0;
		if (index != -1) {
			auto it = accounts.begin();
			while (index--) {
				it++;
				i++;
			}
			std::string security;
			security = accounts[i]->get_security();
			delete accounts[i];

			accounts.erase(it);
			remove_from_file(security);
			status(1,"remove");
			return 1;
		}
		else {
			std::cout << "The Account doesn't exist" << std::endl;
			status(0, "remove");
			return 0;
		}
	}

	bool deposit() {
		std::string name; int n;
		std::cout << "Type your full name" << std::endl;
		std::cin.ignore(INT_MAX, '\n');
		std::getline(std::cin, name);
		std::string account_type = display_account_types(n);

		int index = if_exist(name, account_type);
		if (index != -1) {
			double amount;
			std::cout << "The amount you want to deposit" << std::endl;
			std::cin >> amount;

			status(accounts[index]->deposit(amount), "deposit", accounts[index]);
			search_and_replace(accounts[index]);
			return 1;
		}
		else {
			std::cout << "The Account doesn't exist" << std::endl;
			status(0, "deposit");
			return 0;
		}

	}

	bool withdraw() {
		std::string name; int n;
		std::cout << "Type your full name" << std::endl;
		std::cin.ignore(INT_MAX, '\n');
		std::getline(std::cin, name);
		std::string account_type = display_account_types(n);

		int index = if_exist(name, account_type);
		if (index != -1) {
			double amount;
			std::cout << "The amount you want to withdraw" << std::endl;
			std::cin >> amount;

			

			status(accounts[index]->withdraw(amount), "withdraw", accounts[index]);
			search_and_replace(accounts[index]);
			return 1;
		}
		else {
			std::cout << "The Account doesn't exist" << std::endl;
			status(0, "withdraw");
			return 0;
		}
	}

	void info(int num) {
		switch (num)
		{
		case 1:
			do {
				std::cout << "" << std::endl;
				std::cout << "      INFO" << std::endl;
				std::cout << "1.INFO for Trust Account" << std::endl;
				std::cout << "2.INFO for Checking Account" << std::endl;
				std::cout << "3.INFO for Savings Account" << std::endl;
				std::cout << "4.EXIT" << std::endl;
				validation(num, 4);

				switch (num) {
				case 1:std::cout << "      Trust Account" << std::endl;
					   std::cout << "1.In every deposit the bank add intrest rate(%)" << std::endl;
					   std::cout << "2.Every time you deposit 5000$ the back add bonus 50$" << std::endl;
					   std::cout << "3.You can withdraw only 20% of the your balance" << std::endl;
					   std::cout << "4.You can withdraw only 4 times per year" << std::endl;

					   system("pause");
					break;
				case 2:std::cout << "1.With every withdraw you pay a tax(3$)" << std::endl;
					std::cout << "" << std::endl;

					system("pause");
					break;
				case 3:std::cout << "1.In every deposit the bank add intrest rate(%)" << std::endl;
					   std::cout << "" << std::endl;

					   system("pause");
					break;
				case 4:std::cout << "" << std::endl;
					break;
				}
				
				system("cls");

			} while (num!=4);
			
			break;
		case 2:;
			break;
		}
	}

	void create_Account() {

		int num;

		std::cout << "Do you want to get info of the 3 types of Accounts" << std::endl;
		std::cout << "1.Yes" << std::endl;
		std::cout << "2.NO" << std::endl;
		std::cout << "" << std::endl;
		validation(num, 2);
		info(num);
		std::string type = display_account_types(num);
		std::string name;
		std::cout << "Type your full name" << std::endl;
		std::cin.ignore(INT_MAX, '\n');
		std::getline(std::cin, name);

		if (if_exist(name, type) == -1) {
			create(name, num);
			status(1, "Account creation");
		}
		else {
			std::cout << name << " already have that Account " << std::endl;
			status(0, "Account creation");
		}
	}

	int if_exist(std::string name,std::string account_type) {
		int br = 0;
		for (auto a : accounts) {
			if (a->get_name()==name) {
				if(a->Account_type()==account_type){
					return br;
				}
			}
			br++;
		}
		return -1;
	}

	void add_to_file(Account* acc) {

		std::fstream out("backUp.txt",std::ios::app);
		

		out << *acc << std::endl;

		from_backUp_to_test();
	}

	void create(std::string name,int num) {
		Account* acc;
		switch (num)
		{
		case 1:
			std::cout << "Trust Account" << std::endl;
			int int_rate;
			std::cout << "Type the interest rate(%)" << std::endl;
			std::cin >> int_rate;
			acc=new Trust_Account(name,0,int_rate);
			add_to_file(acc);
			accounts.push_back(acc);
			break;
		case 2:
			std::cout << "Checking Account" << std::endl;
			acc = new Checking_Account(name);
			add_to_file(acc);
			accounts.push_back(acc);
			break;
		case 3:
			std::cout << "Savings Account" << std::endl;
			std::cout << "Type the interest rate(%)" << std::endl;
			std::cin >> int_rate;
			acc = new Savings_Account(name, 0, int_rate);
			add_to_file(acc);
			accounts.push_back(acc);
			break;
		}
		system("cls");
	}



	std::string display_account_types(int &num) {
		std::cout << "1.Trust Account" << std::endl;
		std::cout << "2.Checking Account" << std::endl;
		std::cout << "3.Savings Account" << std::endl;
		
		validation(num, 3);
		system("cls");
		switch(num)
		{
		case 1:return "T";
			break;
		case 2:return "C";
			break;
		case 3:return "S";
			break;
		}
	}

	void from_backUp_to_test() {
		std::ifstream in("backUp.txt");
		std::ofstream out("test.txt");
		std::string line;
		while (getline(in, line)) {
			out << line << std::endl;
		}
	}

	void remove_from_file(std::string security) {
		std::ifstream in("test.txt");
		std::ofstream out("backUp.txt");
		std::string line;
		int skip = 0;
		while (getline(in, line)) {
			if (skip != 0) {

				skip--;
			}
			else {
				if (security == line) {
					skip = 2;
				}
				else {
					out << line << std::endl;
				}
			}
		}

		from_backUp_to_test();
	}


	void search_and_replace(const Account* acc) {
		std::ifstream in("test.txt");
		std::ofstream out("backUp.txt");
		std::string line;
		int skip = 0;
		while (getline(in, line)) {
			if (skip != 0) {

				skip--;
			}
			else {
				if (acc->get_security() == line) {
					out << *acc << std::endl;
					skip = 2;
				}
				else {
					out << line << std::endl;
				}
			}
		}

		from_backUp_to_test();
	}

	void validation(int& choice, int vali) {
		std::cin >> choice;
		while (std::cin.good() == false) {
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Letters are not allowed" << std::endl;
			validation(choice, vali);
		}
		while (choice < 1 || choice>vali) {
			std::cout << "You have entered an incorrect number" << std::endl;
			std::cout << "Enter a number from 1 to" << vali << std::endl;;
			validation(choice, vali);
		}
		system("cls");
	}
};

#endif BANK_H