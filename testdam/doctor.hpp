#ifndef __DOCTOR__
#define __DOCTOR__


#include <string>
#include <iostream>
#include "user.hpp"


class Doctor : public User {
    private :
        // Attributes :
        std::string cnomId ;

    public :
        // Set functions :
        void set_cnomId(std::string cnomId) {
            this->cnomId = cnomId ;
        }

        // Get functions :
        std::string get_cnomId() {
            return this->cnomId ;
        }

        // Constructor :
        Doctor(std::string name, std::string surname, std::string password, std::string cnomId) : User(name, surname, password) {
            set_cnomId(cnomId) ;
        }
} ;


#endif