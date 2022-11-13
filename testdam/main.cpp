#include <iostream>
#include "user.hpp"
#include "patient.hpp"
#include "doctor.hpp"


int main() {
    // User u1("DAMIEN", "GARCIA") ;
    Patient p1("Damien", "Garcia", "123456789") ;

    // std::cout << u1.get_name() << std::endl ;
    std::cout << p1.get_name() << std::endl ;
    std::cout << p1.get_surname() << std::endl ;
    std::cout << p1.get_socials() << std::endl ;

    return 0 ;
}