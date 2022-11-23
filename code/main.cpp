#include "patient.hpp"
#include "doctor.hpp"
#include "radiography.hpp"
#include "interface.hpp"
#include "database.hpp"

int main() {
    // Connexion to Command Line Interface of database
    CommandLineInterface cli ; 
    cli.connection_menu() ;
    return 0 ;
}