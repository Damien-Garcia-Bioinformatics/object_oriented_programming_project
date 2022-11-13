#include "class.hpp"
#include <string>


void User::set_name(std::string n) {
	this->name = n ;
}

void User::set_surname(std::string s) {
	this->surname = s ;
}

// void User::set_usertype(usertype u) {
// 	this->type = u ;
// }


std::string User::get_name() {
	return this->name ;
}

std::string User::get_surname() {
	return this->surname ;
}

// usertype User::get_usertype() {
// 	return this->type ;
// }


User::User(std::string n, std::string s) {
	set_name(n) ;
	set_surname(s) ;
	// set_usertype(u) ;
}