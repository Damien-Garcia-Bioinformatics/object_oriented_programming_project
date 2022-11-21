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
    private :
        std::string user ;
        std::string id ;

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


        bool sign_in(std::string &id, std::string &user) {
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
                    user = "patient" ;
                    if (resultDoctor != -1) {
                        user = "doctor" ;
                    }
                    id = login ;
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


        void connection_menu() {
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
                        if (ConnectionPage::sign_in(id, user)) {
                            display_interface() ;
                        }
                        break ;
                    }
                    case '2' : {
                        ConnectionPage::sign_up() ;
                        break ;
                    }
                    default : {
                        break ;
                    }
                }
            }
        }


        // ------------------------------------------------------------------- //

        void display_interface() {
            std::string name, surname ;
            if (ConnectionPage::user == "doctor") {
                int index {get_doctor_by_cnomId(id)} ;
                name = get_doctor(index).get_name() ;
                surname = get_doctor(index).get_surname() ;
            } else {
                int index {get_patient_by_ssn(id)} ;
                name = get_patient(index).get_name() ;
                surname = get_patient(index).get_surname() ;
            }

            header() ;
            bool menu {true} ;
            while (menu) {
                std::cout << "Welcome " << name << " " << surname << ".\n\n" ;
                std::cout << "   Options :       [0] Exit       [1] Search by date       [2] Search by id\n\n" ;
                std::cout << "   Radiographies :\n\n" ;
                std::cout << "   Radiography id    | Day     | Month   | Year    | Path\n" ;
                // Loop to print all radiographies

                std::cout << "\nChoice : " ;
                char c ;
                std::cin >> c ;
                switch (c) {
                    case '0' : {
                        menu = false ;
                        break ;
                    }
                    case '1' : {
                        header() ;
                        size_t day, month, year ;
                        std::cout << "  Day : " ; std::cin >> day ;
                        std::cout << "Month : " ; std::cin >> month ;
                        std::cout << " Year : " ; std::cin >> year ;
                        break ;
                    }
                    case '2' : {
                        header() ;
                        std::string id ;
                        std::cout << "Radiography id : " ; std::cin >> id ;
                        break ;
                    }
                    default : {
                        menu = false ;
                        break ;
                    }
                }
            }
        }
} ;


#endif