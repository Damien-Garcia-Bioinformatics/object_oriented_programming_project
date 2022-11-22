#ifndef __USER__
#define __USER__


#include <string>
#include <iostream>


class User {
    private :
        // Attributes :
        std::string name ;
        std::string surname ;
    
    public :
        // Set functions : 
        void set_name(std::string name) {
            this->name = name ;
        }
        void set_surname(std::string surname) {
            this->surname = surname ;
        }

        // Get functions :
        std::string get_name() {
            return this->name ;
        }
        std::string get_surname() {
            return this->surname ;
        }

        // Constructor :
        User(std::string name, std::string surname) {
            set_name(name) ;
            set_surname(surname) ;
        }
} ;


#endif