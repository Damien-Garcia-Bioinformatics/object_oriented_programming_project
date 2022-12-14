// Object Oriented Programming - TP Project
// GARCIA Damien
// ECHELARD Florian
// M2BB

#ifndef __DOCTOR__
#define __DOCTOR__


#include <string>
#include <vector>

#include "user.hpp"


class Doctor : public User {
    private :
        // Attributes :
        std::string cnomId ;
        std::vector<std::string> listPatients ;

    public :
        // Set functions :
        void set_cnomId(std::string cnomId) {
            this->cnomId = cnomId ;
        }
        void set_listPatients(std::vector<std::string> listPatients) {
            this->listPatients = listPatients ;
        }

        // Get functions :
        std::string get_cnomId() {
            return this->cnomId ;
        }
        std::vector<std::string> get_listPatients() {
            return this->listPatients ;
        }

        // Constructor :
        Doctor(std::string name, std::string surname, std::string password, std::string cnomId, std::vector<std::string> listPatients) : User(name, surname, password) {
            set_cnomId(cnomId) ;
            set_listPatients(listPatients) ;
        }

        // Other methods

        // Adds a patient ID in doctor attribute listPatients.
        void add_patient(std::string patientId) {
            this->listPatients.push_back(patientId) ;
        }

        // Search for specified patient ID in Doctor attribute and removes it if found.
        void delete_patient(std::string patientId) {
            for (size_t i=0 ; i<this->listPatients.size() ; i++) {
                if (this->listPatients[i] == patientId) {
                    this->listPatients.erase(this->listPatients.begin() + (i)) ;
                }
            }
        }
} ;


#endif