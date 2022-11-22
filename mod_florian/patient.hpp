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

        void add_radiography_to_listRadiographies(std::string radioID) {
            this->listRadiographies.push_back(radioID) ;
        }

        void remove_radiography_from_listRadiographies(std::string radioID) {
            for (size_t i=0 ; i<this->listRadiographies.size() ; i++ ) {
                if (this->listRadiographies[i] == radioID) {
                    this->listRadiographies.erase(this->listRadiographies.begin() + i) ;
                }
            }
            
        }

        // Constructor :
        Patient(std::string name, std::string surname, std::string ssn, std::string password, std::vector<std::string> listRadiographies) : User(name, surname, password) {
            set_ssn(ssn) ;
            set_listRadiographies(listRadiographies) ;
        }
        Patient() : User() {
            set_ssn("[unspecified") ;
            std::vector<std::string> listRadio ;
            set_listRadiographies(listRadio) ;
        }
} ;


#endif