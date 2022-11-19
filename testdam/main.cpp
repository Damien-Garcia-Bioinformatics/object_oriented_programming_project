#include <iostream>
#include "user.hpp"
#include "patient.hpp"
#include "doctor.hpp"
#include "radiography.hpp"
#include "report.hpp"
#include "snapshot.hpp"
#include "interface.cpp"
#include "database.hpp"

int main() {
    DatabaseHandling db ;

    // Some patients
    Patient p1("Damien", "Garcia", "123456789") ;
    Patient p2("Florian", "Echelard", "987654321") ;
    db.add_patient(p1) ;
    db.add_patient(p2) ;

    // Some doctors
    Doctor d1("Lucas", "David", "748159263") ;
    Doctor d2("Cédric", "Guerineau", "326159487") ;
    db.add_doctor(d1) ;
    db.add_doctor(d2) ;

    // // Some radiographies 
    // Radiography r1(xRay, pending, 3, 2, 2023) ;
    // Radiography r2(ultrasound, done, 4, 3, 2021) ;
    // r2.add_snap("554468", "path/to/file1.txt") ;
    // r2.add_snap("115654", "path/to/file2.txt") ;
    // r2.add_snap("654813", "path/to/file3.txt") ;
    // r2.add_report("This is a report you shoudl take seriously...", "dontLookMyPassword") ;

    // menu() ;

    db.update_doctors_database() ;
    db.update_patients_database() ;

    return 0 ;
}