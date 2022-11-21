#include <iostream>

#include "patient.hpp"
#include "doctor.hpp"
#include "radiography.hpp"
#include "interface.hpp"
#include "database.hpp"

int main() {
    // Connexion to command line interface of database
    CommandLineInterface cli ; 
    cli.connection_menu() ;

    system("clear") ;
    cli.header() ;
    std::cout << "   Thanks for using our database. All modifications were successfully saved.\n\n" ;
    std::cout << "   Created for Object Oriented Programming For Biologists Project.\n\n" ;
    std::cout << "   Authors :\n" ;
    std::cout << "      - Damien  GARCIA   (M2BB)\n" ;
    std::cout << "      - Florian ECHELARD (M2BB)\n\n" ;

    return 0 ;
}