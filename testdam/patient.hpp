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
        std::vector<Radiography> listRadiographies ;

    public :
        // Set functions :
        void set_ssn(std::string ssn) {
            this->ssn = ssn ;
        }
        void set_listRadiographies(std::vector<Radiography> listRadiograpies) {
            this->listRadiographies = listRadiographies ;
        }

        // Get functions ;
        std::string get_ssn() {
            return this->ssn ;
        }
        std::vector<Radiography> get_listRadiographies() {
            return this->listRadiographies ;
        }
        int get_radiography_by_id(std::string id) {
            for (int i=0 ; i<listRadiographies.size() ; i++) {
                if (this->listRadiographies[i].get_id() == id) {
                    return i ;
                }
            }
            return -1 ;
        }
        Radiography get_radiography_by_index(int index) {
            return this->listRadiographies[index] ;
        }

        // Constructor :
        Patient(std::string name, std::string surname, std::string ssn, std::string password, std::vector<Radiography> listRadiographies) : User(name, surname, password) {
            set_ssn(ssn) ;
            set_listRadiographies(listRadiographies) ;
        }
} ;


#endif