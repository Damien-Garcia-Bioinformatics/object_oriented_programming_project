#ifndef __INTERFACE__
#define __INTERFACE__


#include <iostream>
#include <string>
#include <cstdlib>

#include "patient.hpp"
#include "doctor.hpp"
#include "radiography.hpp"
#include "database.hpp"



class CommandLineInterface : public DatabaseHandling {
    private :
        std::string user ;
        std::string id ;

    public :
        // --- Simple prints --- //

        void header() {
            system("clear") ;
            std::cout << "\n" ;
            std::cout << "   ╔═════════════════════════════════════════════════════════════════════════╗\n" ;
            std::cout << "   ║  ██████╗  █████╗ ████████╗ █████╗     ██████╗  █████╗ ███████╗███████╗  ║\n" ;
            std::cout << "   ║  ██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗    ██╔══██╗██╔══██╗██╔════╝██╔════╝  ║\n" ;
            std::cout << "   ║  ██║  ██║███████║   ██║   ███████║    ██████╔╝███████║███████╗█████╗    ║\n" ;
            std::cout << "   ║  ██║  ██║██╔══██║   ██║   ██╔══██║    ██╔══██╗██╔══██║╚════██║██╔══╝    ║\n" ;
            std::cout << "   ║  ██████╔╝██║  ██║   ██║   ██║  ██║    ██████╔╝██║  ██║███████║███████╗  ║\n" ;
            std::cout << "   ║  ╚═════╝ ╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝  ║\n" ;
            std::cout << "   ╚═════════════════════════════════════════════════════════════════════════╝\n" ;
            std::cout << "\n" ;
        }

        void display_main() {
            header() ;
            std::cout << "   ╔════════════════╗\n" ;
            std::cout << "   ║   Connection   ║\n" ;
            std::cout << "   ╚════════════════╝\n\n" ;
            std::cout << "   Options :\n" ;
            std::cout << "      [1] Sign in\n" ;
            std::cout << "      [2] Sign up\n" ;
            std::cout << "      [0] Exit\n\n" ;
            std::cout << "   Selection : " ;
        }

        std::string add_tabulation(std::string text, int maxSize) {
            int sizeText {(int)(text.size())} ;
            int sizeTab {maxSize - sizeText} ;
            if (sizeTab >= 0) {
                std::string tab(sizeTab, ' ') ;
                return tab ;
            } else {
                return "" ;
            }
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
            std::cout << "   ╔═════════════╗\n" ;
            std::cout << "   ║   Sign in   ║\n" ;
            std::cout << "   ╚═════════════╝\n\n" ;
            std::cout << "   Login is your social security number (patients), or cnomId (doctors)\n\n" ;
            do {
                std::cout << "      Login : " ; std::cin >> login ;
                std::cout << "   Password : " ; password = CommandLineInterface::password() ;

                int resultDoctor {DatabaseHandling::is_doctor(login)} ;
                int resultPatient {DatabaseHandling::is_patient(login)} ;
                if ((resultDoctor == resultPatient) ||
                    (resultDoctor != -1 && DatabaseHandling::get_doctor(resultDoctor).get_password() != password) ||
                    (resultPatient != -1 && DatabaseHandling::get_patient(resultPatient).get_password() != password)) {
                    std::cout << "   Wrong Login and/or password\n\n" ;
                    std::cout << "   " << 2 - tries << " attempt(s) left\n\n" ; 
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
            std::cout << "   ╔═════════════╗\n" ;
            std::cout << "   ║   Sign up   ║\n" ;
            std::cout << "   ╚═════════════╝\n\n" ;
            std::cout << "                      Name : " ; std::cin >> name ;
            std::cout << "                   Surname : " ; std::cin >> surname ;
            std::cout << "    Social security number : " ; std::cin >> ssn ;

            if (DatabaseHandling::is_patient(ssn) != -1) {
                std::cout << "   This social security number is already linked to an account.\n" ;
                return false ;
            }

            do {
                std::cout << "                  Password : " ; std::string password1 {password()} ;
                std::cout << "                     Again : " ; std::string password2 {password()} ;
                if (password1 != password2) {
                    std::cout << "\n   Password doesn't match.\n" ;
                } else {
                    std::vector<std::string> listRadiographies ;
                    DatabaseHandling::add_patient(Patient(name, surname, ssn, password1, listRadiographies)) ;
                    DatabaseHandling::update_patients_database() ;
                    return true ;
                }
            } while (tries < 2) ;
            return false ;
        }


        void connection_menu() {
            bool menu {true} ;
            while (menu) {
                char c ;
                CommandLineInterface::display_main() ;
                std::cin >> c ;
                switch (c) {
                    case '0' : {
                        header() ;
                        DatabaseHandling::save_progress() ;
                        menu = false ; ;
                        break ;
                    }
                    case '1' : {
                        if (CommandLineInterface::sign_in(id, user)) {
                            if (user == "patient") {
                                display_patient_interface() ;
                            } else {
                                display_doctor_interface() ;
                            }
                        }
                        break ;
                    }
                    case '2' : {
                        CommandLineInterface::sign_up() ;
                        break ;
                    }
                    default : {
                        break ;
                    }
                }
            }
        }

        // --- Doctor interface --- //

        void display_add_patient(Doctor &doc) {
            std::string name, surname, ssn, password ;
            std::vector<std::string> listRadio ;
            header() ;
            std::cout << "   ╔═════════════════════════════╗\n" ;
            std::cout << "   ║   Add patient to database   ║\n" ;
            std::cout << "   ╚═════════════════════════════╝\n\n" ;
            std::cout << "                     name : " ; std::cin >> name ;
            std::cout << "                  surname : " ; std::cin >> surname ;
            std::cout << "   Social security number : " ; std::cin >> ssn ;
            std::cout << "                 password : " ; password = CommandLineInterface::password() ;
            DatabaseHandling::add_patient(Patient(name, surname, ssn, password, listRadio)) ;
            DatabaseHandling::add_patient_to_listPatients(doc.get_cnomId(), ssn) ;
        }

        void display_delete_patient(Doctor &doc) {
            bool again {true} ;
            size_t tries {0} ;
            std::string patientID ;
            header() ;
            std::cout << "   ╔══════════════════════════════════╗\n" ;
            std::cout << "   ║   Delete patient from database   ║\n" ;
            std::cout << "   ╚══════════════════════════════════╝\n\n" ;
            while (tries < 3 && again) {
                std::cout << "   Enter patient ID : " ; std::cin >> patientID ;
                if (DatabaseHandling::get_patient_by_ssn(patientID) == -1) {
                    std::cout << "   Patient doesn't exist in database.\n" ;
                    continue ;
                } else {
                    again = false ;
                    Patient p {DatabaseHandling::get_patient(get_patient_by_ssn(patientID))} ;
                    std::cout << "   Do you really want to delete this patient? (y/n)\n\n" ;
                    std::cout << "                     Name : " << p.get_name() << "\n" ;
                    std::cout << "                  Surname : " << p.get_surname() << "\n" ;
                    std::cout << "   Social Security Number : " << p.get_ssn() << "\n\n" ;
                    std::cout << "   Selection : " ; char c ; std::cin >> c ;
                    if (c == 'y' || c == 'Y') {
                        DatabaseHandling::delete_patient(get_patient_by_ssn(patientID)) ;
                        DatabaseHandling::delete_patient_from_listPatients(doc.get_cnomId(), patientID) ;
                    }
                }
            }
        }

        void display_doctor_interface() {
            header() ;
            bool menu {true} ;

            while (menu) {
                Doctor doc {DatabaseHandling::get_doctor(get_doctor_by_cnomId(id))} ;

                // DatabaseHandling::load_progress() ;
                std::cout << "   Welcome " << doc.get_name() << " " << doc.get_surname() << "!\n\n\n" ;
                std::cout << "      Table of Patients :\n\n" ;
                std::cout << "   ╔═══════════════════════════════════════════════════════════════════════╗\n" ;
                std::cout << "   ║id               ║Name             ║Surname          ║Exams            ║\n" ;
                std::cout << "   ╚═══════════════════════════════════════════════════════════════════════╝\n" ;
                std::cout << "   ╔═══════════════════════════════════════════════════════════════════════╗\n" ;
                for (size_t i=0 ; i<doc.get_listPatients().size() ; i++) {
                    Patient p {get_patient(get_patient_by_ssn(doc.get_listPatients()[i]))} ;
                    std::cout << "   ║" ;
                    std::cout << p.get_ssn() << add_tabulation(p.get_ssn(), 17) << "║" ;
                    std::cout << p.get_name() << add_tabulation(p.get_name(), 17) << "║" ;
                    std::cout << p.get_surname() << add_tabulation(p.get_surname(), 17) << "║" ;
                    std::cout << p.get_listRadiographies().size() << add_tabulation(std::to_string(p.get_listRadiographies().size()), 17) << "║\n" ;
                }
                std::cout << "   ╚═══════════════════════════════════════════════════════════════════════╝\n\n" ;
                std::cout << "   Options :\n" ;
                std::cout << "      [0] Exit\n" ;
                std::cout << "      [1] Search patient\n" ;
                std::cout << "      [2] Add patient\n" ;
                std::cout << "      [3] Delete patient\n" ;
                std::cout << "      [4] Access patient by id\n\n" ;
                std::cout << "   Selection : " ;
                char c ;
                std::cin >> c ;
                switch (c) {
                    case '0' : {
                        menu = false ;
                        break ;
                    }
                    case '1' : {
                        header() ;
                        std::cout << "   ╔══════════════════════════╗\n" ;
                        std::cout << "   ║   Search patient by id   ║\n" ;
                        std::cout << "   ╚══════════════════════════╝\n\n" ;
                        break ;
                    }
                    case '2' : {
                        display_add_patient(doc) ;
                        break ;
                    }
                    case '3' : {
                        display_delete_patient(doc) ;
                        break ;
                    }
                    case 4 : {
                        // Access patient by id
                    }
                    default : {
                        menu = false ;
                        break ;
                    }
                }
            }
        }


        // --- Patient interface --- //

        void display_patient_interface() {
            header() ;
            Patient pat {DatabaseHandling::get_patient(get_patient_by_ssn(id))} ;
            bool menu {true} ;

            while (menu) {
                std::cout << "   Welcome " << pat.get_name() << " " << pat.get_surname() << "!\n\n\n" ;
                
                std::cout << "      Table of radiographies :\n\n" ;
                std::cout << "   ╔═══════════════════════════════════════════════════════════════════════════════════╗\n" ;
                std::cout << "   ║id           ║Type         ║State        ║Day          ║Month        ║Year         ║\n" ;
                std::cout << "   ╚═══════════════════════════════════════════════════════════════════════════════════╝\n" ;
                std::cout << "   ╔═══════════════════════════════════════════════════════════════════════════════════╗\n" ;
                // Loop to print all radiographies
                for (size_t i=0 ; i<pat.get_listRadiographies().size() ; i++) {
                    Radiography radio {get_radiography(pat.get_listRadiographies()[i])} ;
                    std::cout << "   ║" ;
                    std::cout << radio.get_id() << add_tabulation(radio.get_id(), 13) << "║" ;
                    if (radio.get_type() == xRay) {
                        std::cout << "xRay" << add_tabulation("xRay", 13) << "║" ;
                    } else if (radio.get_type() == MRI) {
                        std::cout << "MRI" << add_tabulation("MRI", 13) << "║" ;
                    } else {
                        std::cout << "ultrasound" << add_tabulation("ultrasound", 13) << "║" ;
                    }
                    if (radio.get_state() == done) {
                        std::cout << "done" << add_tabulation("done", 13) << "║" ;
                    } else {
                        std::cout << "pending" << add_tabulation("pending", 13) << "║" ;
                    }
                    std::cout << radio.get_day() << add_tabulation(std::to_string(radio.get_day()), 13) << "║" ;
                    std::cout << radio.get_month() << add_tabulation(std::to_string(radio.get_month()), 13) << "║" ;
                    std::cout << radio.get_year() << add_tabulation(std::to_string(radio.get_year()), 13) << "║\n" ;
                }
                std::cout << "   ╚═══════════════════════════════════════════════════════════════════════════════════╝\n\n" ;
                std::cout << "   Options :\n" ;
                std::cout << "      [0] Exit\n" ;
                std::cout << "      [1] Search by date\n" ;
                std::cout << "      [2] Access by id\n\n" ;
                std::cout << "   Selection : " ;
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
                        std::cout << "   ╔══════════════════════════════════╗\n" ;
                        std::cout << "   ║   Search radiographies by date   ║\n" ;
                        std::cout << "   ╚══════════════════════════════════╝\n\n" ;
                        std::cout << "     Day : " ; std::cin >> day ;
                        std::cout << "   Month : " ; std::cin >> month ;
                        std::cout << "    Year : " ; std::cin >> year ;
                        break ;
                    }
                    case '2' : {
                        header() ;
                        std::string id ;
                        std::cout << "   ╔════════════════════════════════╗\n" ;
                        std::cout << "   ║   Search radiographies by id   ║\n" ;
                        std::cout << "   ╚════════════════════════════════╝\n\n" ;
                        std::cout << "   Radiography id : " ; std::cin >> id ;
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