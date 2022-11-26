// Object Oriented Programming - TP Project
// GARCIA Damien
// ECHELARD Florian
// M2BB

#ifndef __USER__
#define __USER__


#include <string>


class User {
    private :
        // Attributes :
        std::string name ;
        std::string surname ;
        std::string password ;
    
    public :
        // Set functions : 
        void set_name(std::string name) {
            this->name = name ;
        }
        void set_surname(std::string surname) {
            this->surname = surname ;
        }
        void set_password(std::string password) {
            this->password = password ;
        }

        // Get functions :
        std::string get_name() {
            return this->name ;
        }
        std::string get_surname() {
            return this->surname ;
        }
        std::string get_password() {
            return this->password ;
        }

        // Constructor :
        User(std::string name, std::string surname, std::string password) {
            set_name(name) ;
            set_surname(surname) ;
            set_password(password) ;
        }

        User() {
            set_name("[unspecified]") ;
            set_surname("[unspecified]") ;
            set_password("[unspecified]") ;
        }
} ;


#endif