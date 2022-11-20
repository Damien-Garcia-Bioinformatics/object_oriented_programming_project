#include <iostream>

#include "patient.hpp"
#include "doctor.hpp"
#include "radiography.hpp"
#include "interface.hpp"
#include "database.hpp"

int main() {
    // Declaration of database object which automatically constructs itself using data in database.
    DatabaseHandling db ;

    // Some patients
    // std::cout << db.get_listPatients()[2].get_ssn() << std::endl ;

    // Declaration and call of command line interface.
    ConnectionPage cli ; 
    cli.menu() ;

    // Updating the database
    // db.update_doctors_database() ;
    // db.update_patients_database() ;

    // system("clear") ;

    return 0 ;
}