#ifndef __DOCTOR__
#define __DOCTOR__


#include <string>
#include <iostream>
#include "user.hpp"


class Doctor : public User {
    private :
        // Attributes :
        std::string cnomId ;
        std::vector<Patient> listPatients ;

    public :
        // Set functions :
        void set_cnomId(std::string cnomId) {
            this->cnomId = cnomId ;
        }
        void set_listPatients(std::vector<Patient> listPatients) {
            this->listPatients = listPatients ;
        }

        // Get functions :
        std::string get_cnomId() {
            return this->cnomId ;
        }
        std::vector<Patient> get_listPatients() {
            return this->listPatients ;
        }

        // Constructor :
        Doctor(std::string name, std::string surname, std::string password, std::string cnomId, std::vector<Patient> listPatients) : User(name, surname, password) {
            set_cnomId(cnomId) ;
            set_listPatients(listPatients) ;
        }
} ;


#endif