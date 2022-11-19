#include <iostream>

#include "patient.hpp"
#include "doctor.hpp"
#include "radiography.hpp"
#include "interface.hpp"
#include "database.hpp"

int main() {
    DatabaseHandling db ;

    // Patient p1("Stephane", "Teletchea", "756123") ;
    // Patient p2("Bernard", "Offmann", "1234533015") ;
    // Doctor d1("Emmanuel", "Charpentier", "55487632") ;
    // db.add_patient(p1) ;
    // db.add_patient(p2) ;
    // db.add_doctor(d1) ;


    // Some patients
    std::cout << db.get_listPatients()[2].get_ssn() << std::endl ;


    // // Some radiographies 
    // Radiography r1(xRay, pending, 3, 2, 2023) ;
    // Radiography r2(ultrasound, done, 4, 3, 2021) ;
    // r2.add_snap("554468", "path/to/file1.txt") ;
    // r2.add_snap("115654", "path/to/file2.txt") ;
    // r2.add_snap("654813", "path/to/file3.txt") ;
    // r2.add_report("This is a report you shoudl take seriously...", "dontLookMyPassword") ;

    ConnectionPage cli ; //Command Line Interface
    cli.menu() ;

    db.update_doctors_database() ;
    db.update_patients_database() ;

    system("clear") ;

    return 0 ;
}