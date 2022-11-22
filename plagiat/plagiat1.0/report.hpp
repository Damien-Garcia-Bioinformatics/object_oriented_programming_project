#ifndef __REPORT__
#define __REPORT__


#include <iostream>
#include <string>


class Report {
    private :
        // Attributes :
        std::string content ;
        std::string password ;

    public :
        // Set functions : 
        void set_content(std::string content) {
            this->content = content ;
        }
        void set_password(std::string password) {
            this->password = password ;
        }

        // Get functions :
        std::string get_content(std::string password) {
            if (password == this->password) {
                return this->content ;
            }
            std::cout << "Wrong password" << std::endl ;
        }

        // Constructor :
        Report(std::string content, std::string password) {
            set_content(content) ;
            set_password(password) ;
        }
        Report() {
            set_content("") ;
            set_password("") ;
        }

        // Destructor :
        ~Report() { }
} ;


#endif