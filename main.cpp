#include "header/patient.hpp"
#include "header/doctor.hpp"
#include "header/radiography.hpp"
#include "header/interface.hpp"
#include "header/database.hpp"

int main() {
    // Connexion to Command Line Interface of database
    CommandLineInterface cli ; 
    cli.connection_menu() ;
    return 0 ;
}