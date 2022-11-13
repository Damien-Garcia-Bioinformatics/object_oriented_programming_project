#include "class.hpp"
#include <iostream>
#include <string>

void Patient::set_socials(std::string s) {
    this->socialSecurity = s ;
}

std::string Patient::get_socials() {
    return this->socialSecurity ;
}


Patient(std::string name, std::string surname, std::string socials) : User::User(name, surname) {
    set_socials(socials) ;
}