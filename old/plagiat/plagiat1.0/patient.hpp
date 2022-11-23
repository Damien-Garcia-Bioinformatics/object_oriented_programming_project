#ifndef __PATIENT__
#define __PATIENT__


#include <iostream>
#include <string>
#include "user.hpp"


class Patient : public User {
    private :
        // Attribute :
        std::string socialSecurityNumber ;

    public :
        // Set functions :
        void set_socials(std::string socials) {
            this->socialSecurityNumber = socials ;
        }

        // Get functions ;
        std::string get_socials() {
            return this->socialSecurityNumber ;
        }

        // Constructor :
        Patient(std::string name, std::string surname, std::string socials) : User(name, surname) {
            set_socials(socials) ;
        }
} ;


#endif