#ifndef __PATIENT__
#define __PATIENT__


#include <iostream>
#include <string>
#include "user.hpp"


class Patient : public User {
    private :
        // Attribute :
        std::string ssn ; // Social Security Number

    public :
        // Set functions :
        void set_ssn(std::string ssn) {
            this->ssn = ssn ;
        }

        // Get functions ;
        std::string get_ssn() {
            return this->ssn ;
        }

        // Constructor :
        Patient(std::string name, std::string surname, std::string ssn, std::string password) : User(name, surname, password) {
            set_ssn(ssn) ;
        }
} ;


#endif