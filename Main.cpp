#include "Bank.h"
int Account::number_of_account = 0;

void main(){
	Bank bank("test.txt");
	bank.start();
}