#include <iostream>
#include <string>
#include <cstdlib>


#include "user.hpp"
#include "patient.hpp"
#include "doctor.hpp"
#include "radiography.hpp"
#include "report.hpp"
#include "snapshot.hpp"



int instant_selection() {
    system("stty raw") ;
    int c {getchar()} ;
    system("stty cooked") ;
    system("clear") ;
    if(c == '.') {
        system("stty cooked");
        exit(0);
    }
    return c ;
}


std::string password() {
    std::string pw ;
    system("stty -echo") ;
    std::cin >> pw ;
    system("stty echo") ;

    std::string output(pw.size(), '*') ;
    std::cout << output << "\n" ;
    return pw ;
}


void header() {
    std::cout << "   +------------------------------------------------------------------+\n" ;
    std::cout << "   |                      Radiographies Data Base                     |\n" ;
    std::cout << "   +------------------------------------------------------------------+\n\n" ;
}


void first_page() {
    header() ;
    std::cout << "You need to have an account to access the database.\n" ;
    std::cout << "   [1] I already have an account\n" ;
    std::cout << "   [2] Create my account\n" ;
}


void login() {
    std::string login ;
    std::string password ;
    
    header() ;
    std::cout << "Login    : " ;
    std::cin >> login ;
    std::cout << "Password : " ;
    std::cin >> password ;
}


void create_account() {
    bool match {false} ;
    std::string login ;
    std::string password1 ;
    std::string password2 ;
    header() ;
    std::cout << "Account creation\n\n" ;
    std::cout << "   Login : " ;
    std::cin >> login ;    
    do {
        std::cout << "Password : " ;
        std::string password1 {password()} ;
        std::cout << "   Again : " ;
        std::string password2 {password()} ;
        if (password1 != password2) {
            std::cout << "Password doesn't match.\n" ;
        } else {
            match = true ;
        }
    } while (!match) ;
}


void menu() {
    system("clear") ;
    bool menu {true} ;
    // do {
        first_page() ;

        int c {instant_selection()} ;
        switch (c) {
            case int('1') :
                login() ;
                break ;
            case int('2') :
                create_account() ;
                break ;
            default :
                break ;
        }

    // } while (menu) ;
}
