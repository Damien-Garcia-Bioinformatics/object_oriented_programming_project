#include <iostream>

#include "patient.hpp"
#include "doctor.hpp"
#include "radiography.hpp"
#include "interface.hpp"
#include "database.hpp"

int main() {
    // Connexion to command line interface of database
    ConnectionPage cli ; 
    cli.connection_menu() ;

    // system("clear") ;

    return 0 ;
}