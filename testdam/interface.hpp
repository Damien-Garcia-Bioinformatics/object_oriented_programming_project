#ifndef __INTERFACE__
#define __INTERFACE__


#include <iostream>
#include <string>
#include <cstdlib>

#include "patient.hpp"
#include "doctor.hpp"
#include "radiography.hpp"
#include "database.hpp"



class ConnectionPage : public DatabaseHandling {
    private :
        std::string user ;
        std::string id ;

    public :
        // --- Simple prints --- //

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


        // --- Tool functions --- //

        std::string password() {
            std::string pw ;
            system("stty -echo") ;
            std::cin >> pw ;
            system("stty echo") ;

            std::string output(pw.size(), '*') ;
            std::cout << output << "\n" ;
            return pw ;
        }


        // --- Connection menus --- //

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
                    std::vector<Radiography> listRadiographies ;
                    DatabaseHandling::add_patient(Patient(name, surname, ssn, password1, listRadiographies)) ;
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
                            if (user == "patient") {
                                display_patient_interface() ;
                            } else {
                                //display_doctor_interface() ;
                            }
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


        // --- Patient interface --- //

        void display_patient_interface() {
            // this->p = get_patient(get_patient_by_ssn(id)) ;
            Patient pat {DatabaseHandling::get_patient(get_patient_by_ssn(id))} ;
            header() ;
            bool menu {true} ;
            while (menu) {
                std::cout << pat.get_listRadiographies().size() ;
                std::cout << "Welcome " << pat.get_name() << " " << pat.get_surname() << ".\n\n" ;
                std::cout << "   Options :       [0] Exit       [1] Search by date       [2] Search by id\n\n" ;
                std::cout << "   Radiographies :\n\n" ;
                std::cout << "   id        | Type     | State    | Day      | Month    | Year     | Path     \n" ;
                // Loop to print all radiographies
                std::vector<Radiography> listRadiographies = pat.get_listRadiographies() ;
                for (int i=0 ; i<listRadiographies.size() ; i++) {
                    std::cout << listRadiographies[i].get_id() << "  " ;
                    std::cout << listRadiographies[i].get_type() << "  " ;
                    std::cout << listRadiographies[i].get_state() << "  " ;
                    std::cout << listRadiographies[i].get_day() << "  " ;
                    std::cout << listRadiographies[i].get_month() << "  " ;
                    std::cout << listRadiographies[i].get_year() << "  \n" ;
                }

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