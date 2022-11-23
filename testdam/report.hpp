#ifndef __REPORT__
#define __REPORT__


#include <iostream>
#include <string>


class Report {
    private :
        // Attributes :
        std::string content ;

    public :
        // Set functions : 
        void set_content(std::string content) {
            this->content = content ;
        }

        // Get functions :
        std::string get_content() {
            return this->content ;
        }

        // Constructor :
        Report(std::string content) {
            set_content(content) ;
        }
        Report() {
            set_content("") ;
        }

        // Destructor :
        ~Report() { }
} ;


#endif