#ifndef __PATIENT__
#define __PATIENT__


#include <iostream>
#include <string>
#include "user.hpp"
#include "radiography.hpp"


class Patient : public User {
    private :
        // Attribute :
        std::string ssn ; // Social Security Number
        std::vector<std::string> listRadiographies ;

    public :
        // Set functions :
        void set_ssn(std::string ssn) {
            this->ssn = ssn ;
        }

        void set_listRadiographies(std::vector<std::string> listRadiographies) {
            this->listRadiographies = listRadiographies ;
        }

        // Get functions ;
        std::string get_ssn() {
            return this->ssn ;
        }

        std::vector<std::string> get_listRadiographies() {
            return this->listRadiographies ;
        }

        // Constructor :
        Patient(std::string name, std::string surname, std::string ssn, std::string password, std::vector<std::string> listRadiographies) : User(name, surname, password) {
            set_ssn(ssn) ;
            set_listRadiographies(listRadiographies) ;
        }
} ;


#endif