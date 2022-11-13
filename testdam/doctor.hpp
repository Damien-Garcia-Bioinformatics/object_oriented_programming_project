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
        void set_cnomId(std::string id) {
            this->cnomId = id ;
        }

        // Get functions :
        std::string get_cnomId() {
            return this->cnomId ;
        }

        // Constructor :
        Doctor(std::string name, std::string surname, std::string id) : User(name, surname) {
            set_cnomId(id) ;
        }
} ;


#endif