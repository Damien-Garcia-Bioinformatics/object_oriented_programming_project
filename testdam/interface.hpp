#ifndef __INTERFACE__
#define __INTERFACE__


#include <iostream>
#include <string>
#include <cstdlib>

#include "user.hpp"
#include "patient.hpp"
#include "doctor.hpp"
#include "radiography.hpp"
#include "report.hpp"
#include "snapshot.hpp"
#include "database.hpp"


class ConnectionPage : public DatabaseHandling {
    public :
        void header() {
            system("clear") ;
            std::cout << "\n" ;
            std::cout << "      ██████╗  █████╗ ████████╗ █████╗     ██████╗  █████╗ ███████╗███████╗\n" ;
            std::cout << "      ██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗    ██╔══██╗██╔══██╗██╔════╝██╔════╝\n" ;
            std::cout << "      ██║  ██║███████║   ██║   ███████║    ██████╔╝███████║███████╗█████╗  \n" ;
            std::cout << "      ██║  ██║██╔══██║   ██║   ██╔══██║    ██╔══██╗██╔══██║╚════██║██╔══╝  \n" ;
            std::cout << "      ██████╔╝██║  ██║   ██║   ██║  ██║    ██████╔╝██║  ██║███████║███████╗\n" ;
            std::cout << "      ╚═════╝ ╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝\n" ;
            std::cout << "     ███████████████████████████████████████████████████████████████████████╗\n" ;
            std::cout << "     ╚══════════════════════════════════════════════════════════════════════╝\n\n" ;
        }

        void display_main() {
            header() ;
            std::cout << "Connection :\n\n" ;
            std::cout << "   [1] Sign in\n" ;
            std::cout << "   [2] Sign up\n" ;
            std::cout << "   [0] Exit\n\n" ;
            std::cout << "Choice : " ;
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


        bool sign_in() {
            std::string login ;
            std::string password ;
            size_t tries {0} ;
            
            header() ;
            std::cout << "Login is your social security number (patients), or cnomId (doctors)\n\n" ;
            do {
                std::cout << "   Login : " ;
                std::cin >> login ;
                std::cout << "Password : " ;
                password = ConnectionPage::password() ;

                int resultDoctor {DatabaseHandling::is_doctor(login)} ;
                int resultPatient {DatabaseHandling::is_patient(login)} ;
                if ((resultDoctor == resultPatient) ||
                    (resultDoctor != -1 && DatabaseHandling::get_doctor(resultDoctor).get_password() != password) ||
                    (resultPatient != -1 && DatabaseHandling::get_patient(resultPatient).get_password() != password)) {
                    std::cout << "Wrong Login and/or password\n\n" ;
                    std::cout << 2 - tries << " attempt(s) left\n\n" ; 
                } else {
                    return true ;
                }

                tries++ ;
            } while (tries < 3) ;
            return false ;
        }


        bool sign_up() {
            size_t tries {0} ;
            std::string name, surname, ssn ;

            header() ;
            std::cout << "Account creation\n\n" ;
            std::cout << "                   Name : " ;
            std::cin >> name ;
            std::cout << "                Surname : " ;
            std::cin >> surname ;
            std::cout << " Social security number : " ;
            std::cin >> ssn ;
            if (DatabaseHandling::is_patient(ssn) != -1) {
                std::cout << "This social security number is already linked to an account.\n" ;
                return false ;
            }

            do {
                std::cout << "               Password : " ;
                std::string password1 {password()} ;
                std::cout << "                  Again : " ;
                std::string password2 {password()} ;
                if (password1 != password2) {
                    std::cout << "\nPassword doesn't match.\n" ;
                } else {
                    DatabaseHandling::add_patient(Patient(name, surname, ssn, password1)) ;
                    DatabaseHandling::update_patients_database(get_listPatients()) ;
                    return true ;
                }
            } while (tries < 2) ;
            return false ;
        }


        void menu() {
            bool menu {true} ;
            while (menu) {
                char c ;
                ConnectionPage::display_main() ;
                std::cin >> c ;
                switch (c) {
                    case '0' : {
                        exit(0) ;
                    }
                    case '1' : {
                        if (ConnectionPage::sign_in()) {
                            
                        }
                        break ;
                    }
                    case '2' : {
                        if (ConnectionPage::sign_up()) {
                            //Go to main interface
                        }
                        break ;
                    }
                    default : {
                        break ;
                    }
                }
                std::cout << menu << std::endl ;
            }
        }
} ;


class MainPage : public ConnectionPage {
    private :

    public :
        void display() {
            header() ;
            std::cout << "Welcome [Name] [Surname]\n\n" ;
            std::cout << "Acces to :\n" ;
            std::cout << "   [1] Search tool\n" ;
            std::cout << "   [2] Radiography list\n" ;
            std::cout << "   [3] Account\n" ;
            std::cout << "   [0] Exit\n" ;
        }
} ;


#endif