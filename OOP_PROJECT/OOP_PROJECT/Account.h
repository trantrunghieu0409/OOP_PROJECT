#pragma once
#ifndef _account_h_
#define _account_h_
#include "Libary.h"
class Account {
	std::string username;
	std::string password;
public:
	bool isCorrect(std::string, std::string);
};
#endif // !_account_h_