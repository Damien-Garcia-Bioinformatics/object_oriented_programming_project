#ifndef __INTERFACE__
#define __INTERFACE__


#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h> 
#include <stdio.h>
#include <filesystem>

#include "patient.hpp"
#include "doctor.hpp"
#include "radiography.hpp"
#include "database.hpp"


class CommandLineInterface : public DatabaseHandling {
    private :
        std::string user ;
        std::string id ;

    public :
        // ---------------------- //
        // --- Tool functions --- //
        // ---------------------- //

        // Prints the header.
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

        // Method used to hide password field for privacy purpose.
        std::string password() {
            std::string pw ;
            system("stty -echo") ;
            std::cin >> pw ;
            system("stty echo") ;

            std::string output(pw.size(), '*') ;
            std::cout << output << "\n" ;
            return pw ;
        }

        // Method adding tabulataions for tables to have a nice columns/lines format.
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



        // ------------------------ //
        // --- Connection menus --- //
        // ------------------------ //

        // Displays the connection menu.
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

        // Displays the sign in menu, checks if user identifier and password exist in database and are from the same account.
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


        // Displays the sign up menu and allows creation of new patients account.
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

        // Allows user interaction with connection menu.
        void connection_menu() {
            bool menu {true} ;
            while (menu) {
                char c ;
                CommandLineInterface::display_main() ;
                std::cin >> c ;
                switch (c) {
                    case '0' : {
                        CommandLineInterface::header() ;
                        DatabaseHandling::save_and_quit() ;
                        menu = false ; ;
                        break ;
                    }
                    case '1' : {
                        if (CommandLineInterface::sign_in(id, user)) {
                            if (user == "patient") {
                                display_radiographies_interface() ;
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



        // ------------------------ //
        // --- Doctor interface --- //
        // ------------------------ //

        // Displays the menu to add a patient in database
        void display_add_patient(Doctor &doc) {
            std::string name, surname, ssn, password ;
            std::vector<std::string> listRadio ;
            std::cout << "\n\n" ;
            std::cout << "   ╔═════════════════════════════╗\n" ;
            std::cout << "   ║   Add patient to database   ║\n" ;
            std::cout << "   ╚═════════════════════════════╝\n\n" ;
            std::cout << "                     name : " ; std::cin >> name ;
            std::cout << "                  surname : " ; std::cin >> surname ;
            std::cout << "   Social security number : " ; std::cin >> ssn ;
            std::cout << "                 password : " ; password = CommandLineInterface::password() ;
            if (is_patient(ssn) != -1) {
                std::cout << "\n /!\\ This patient already exists in database /!\\ \n" ;
                sleep(2) ;
                
            } else {
                DatabaseHandling::add_patient(Patient(name, surname, ssn, password, listRadio)) ;
                DatabaseHandling::add_patient_to_listPatients(doc.get_cnomId(), ssn) ;
            }
        }

        // Displays the menu to delete a patient in database
        void display_delete_patient(Doctor &doc) {
            std::string patientID ;
            std::cout << "\n\n" ;
            std::cout << "   ╔══════════════════════════════════╗\n" ;
            std::cout << "   ║   Delete patient from database   ║\n" ;
            std::cout << "   ╚══════════════════════════════════╝\n\n" ;
            std::cout << "   Enter patient ID : " ; std::cin >> patientID ;
            if (DatabaseHandling::get_patient_by_ssn(patientID) == -1) {
                std::cout << "   Patient doesn't exist in database.\n" ;
            } else {
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

        // Displays the general doctor interface
        void display_doctor_interface() {
            bool menu {true} ;
            while (menu) {
                header() ;
                Doctor doc {DatabaseHandling::get_doctor(get_doctor_by_cnomId(id))} ;
                std::cout << "   Doctor : " << doc.get_name() << " " << doc.get_surname() << "!\n\n\n" ;
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
                std::cout << "      [1] Access patient by id\n" ;
                std::cout << "      [2] Add patient\n" ;
                std::cout << "      [3] Delete patient\n" ;
                std::cout << "   Selection : " ;
                char c ;
                std::cin >> c ;
                switch (c) {
                    case '0' : {
                        menu = false ;
                        break ;
                    }
                    case '1' : {
                        display_radiographies_interface() ;
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
                    default : {
                        menu = false ;
                        break ;
                    }
                }
            }
        }



        // ------------------------------- //
        // --- Radiographies interface --- //
        // ------------------------------- //

        void display_search_by_date(size_t &day, size_t &month, size_t &year) {
            std::cout << "\n\n" ;
            std::cout << "   ╔════════════════════════════════╗\n" ;
            std::cout << "   ║   Search radiography by date   ║\n" ;
            std::cout << "   ╚════════════════════════════════╝\n\n" ;
            std::cout << "     Day : " ; std::cin >> day ;
            std::cout << "   Month : " ; std::cin >> month ;
            std::cout << "    Year : " ; std::cin >> year ;
        }

        void display_add_radiography(std::string patientID) {
            std::cout << "\n\n" ;
            std::cout << "   ╔═════════════════════════════════╗\n" ;
            std::cout << "   ║   Add radiography to database   ║\n" ;
            std::cout << "   ╚═════════════════════════════════╝\n\n" ;
            std::string id, type, state ;
            size_t day, month, year ;
            std::cout << "                             ID : " ; std::cin >> id ;
            std::cout << "   Type (xRay, MRI, ultrasound) : " ; std::cin >> type ;
            std::cout << "          State (done, pending) : " ; std::cin >> state ;
            std::cout << "                            day : " ; std::cin >> day ;
            std::cout << "                          month : " ; std::cin >> month ;
            std::cout << "                           year : " ; std::cin >> year ;
            DatabaseHandling::add_radiography(Radiography(id, type, state, day, month, year)) ;
            DatabaseHandling::add_radiography_to_patient(patientID, id) ;
        }


        void display_delete_radiography(std::string patientID) {
            std::string radioID ;
            std::cout << "\n\n" ;
            std::cout << "   ╔══════════════════════════════════════╗\n" ;
            std::cout << "   ║   Delete radiography from database   ║\n" ;
            std::cout << "   ╚══════════════════════════════════════╝\n\n" ;
            std::cout << "   Radiography ID : " ; std::cin >> radioID ;
            if (DatabaseHandling::get_radiography_by_id(radioID) == -1) {
                std::cout << "This radiography doesn't exist in database.\n" ;
                sleep(3) ;
            } else {
                Patient pat {get_patient(get_patient_by_ssn(patientID))} ;
                for (size_t i=0 ; i<pat.get_listRadiographies().size() ; i++) {
                    if (pat.get_listRadiographies()[i] == radioID) {
                        DatabaseHandling::delete_radiography_from_patient(patientID, radioID) ;
                        DatabaseHandling::delete_radiography(radioID) ;
                    }
                }
            }            
        }


        void display_radiographies_interface() {
            //searchByDate data :
            bool dateSearch {false} ;
            size_t day, month, year ;
            
            bool patient ;
            bool access {false} ;
            std::string patientID ;
            Patient pat ;
            if (user == "patient") {
                patient = true ;
                access = true ;
            } else {
                Doctor doc {DatabaseHandling::get_doctor(get_doctor_by_cnomId(id))} ;
                std::cout << "\n\n" ;
                std::cout << "   ╔══════════════════════════╗\n" ;
                std::cout << "   ║   Search patient by id   ║\n" ;
                std::cout << "   ╚══════════════════════════╝\n\n" ;
                std::cout << "   Enter patient ID : " ; std::cin >> patientID ;
                if (DatabaseHandling::is_patient(patientID) != -1) {
                    for (size_t i=0 ; i<doc.get_listPatients().size() ; i++) {
                        if (doc.get_listPatients()[i] == patientID) {
                            patient = false ;
                            access = true ;
                        }
                    }
                }
            }
            
            bool menu ;
            if (access) {
                menu = true ;
            } else {
                menu = false ;
                std::cout << "   Patient ID doesn't exist in database.\n" ;
                sleep(3) ;
            }
            while (menu) {
                if (patient) {
                    pat = DatabaseHandling::get_patient(get_patient_by_ssn(id)) ;
                } else {
                    pat = DatabaseHandling::get_patient(get_patient_by_ssn(patientID)) ;
                }
                DatabaseHandling::upload_patients_database() ;
                header() ;
                std::cout << "   Patient : " << pat.get_name() << " " << pat.get_surname() << "\n\n\n" ;
                
                std::cout << "      Table of radiographies :\n\n" ;
                std::cout << "   ╔═══════════════════════════════════════════════════════════════════════════════════╗\n" ;
                std::cout << "   ║id           ║Type         ║State        ║Day          ║Month        ║Year         ║\n" ;
                std::cout << "   ╚═══════════════════════════════════════════════════════════════════════════════════╝\n" ;
                std::cout << "   ╔═══════════════════════════════════════════════════════════════════════════════════╗\n" ;
                // Loop to print all radiographies
                std::vector<std::string> radios ;
                if (!dateSearch) {
                    radios = pat.get_listRadiographies() ;
                } else {
                    radios = search_by_date(day, month, year, pat.get_listRadiographies()) ;
                } 
                for (size_t i=0 ; i<radios.size() ; i++) {
                    Radiography radio {get_radiography(radios[i])} ;
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
                dateSearch = false ;
                std::cout << "   ╚═══════════════════════════════════════════════════════════════════════════════════╝\n\n" ;
                if (this->user == "patient") {
                    // For patients :
                    std::cout << "   Options :\n" ;
                    std::cout << "      [0] Exit\n" ;
                    std::cout << "      [1] Access by id\n" ;
                    std::cout << "      [2] Search by date\n" ;
                    std::cout << "   Selection : " ; char c ; std::cin >> c ;
                    switch (c) {
                        case '0' : {
                            menu = false ;
                            break ;
                        }
                        case '1' : {
                            display_snapshotReport_interface() ;
                            break ;
                        }
                        case '2' : {
                            display_search_by_date(day, month, year) ;
                            dateSearch = true ;
                            break ;
                        }
                        default : {
                            break ;
                        }
                    }
                } else {
                    // For doctors :
                    std::cout << "   Options :\n" ;
                    std::cout << "      [0] Exit\n" ;
                    std::cout << "      [1] Access by id\n" ;
                    std::cout << "      [2] Search by date\n" ;
                    std::cout << "      [3] Add radiography\n" ;
                    std::cout << "      [4] Delete radiography\n" ;
                    std::cout << "   Selection : " ; char c ; std::cin >> c ;
                    switch (c) {
                        case '0' : {
                            menu = false ;
                            break ;
                        }
                        case '1' : {
                            display_snapshotReport_interface() ;
                            break ;
                        }
                        case '2' : {
                            dateSearch = true ;
                            display_search_by_date(day, month, year) ;
                            break ;
                        }
                        case '3' : {
                            display_add_radiography(pat.get_ssn()) ;
                            break ;
                        }
                        case '4' : {
                            display_delete_radiography(pat.get_ssn()) ;
                            break ;
                        }
                        default : {
                            break ;
                        }
                    }
                }
            }
        }



        // ------------------------------------- //
        // --- Snapshot and report interface --- //
        // ------------------------------------- //

        void display_add_snapshot(Radiography radio) {
            std::string id, path ;
            std::cout << "\n\n" ;
            std::cout << "   ╔═════════════════════════════╗\n" ;
            std::cout << "   ║   Add snapshot to database  ║\n" ;
            std::cout << "   ╚═════════════════════════════╝\n\n" ;
            std::cout << "     Snapshot id : " ; std::cin >> id ;
            std::cout << "   Snapshot path : " ; std::cin >> path ;
            if (radio.get_snap_index(id) != -1) {
                std::cout << "\n   Snapshot id already in database.\n" ;
                sleep(3) ;
            } else {
                DatabaseHandling::add_snapshot_to_radiography(radio.get_id(), Snapshot(id,path)) ;
            }
        }

        void display_delete_snapshot(Radiography radio) {
            std::string snapID ;
            std::cout << "\n\n" ;
            std::cout << "   ╔═══════════════════════════════════╗\n" ;
            std::cout << "   ║   Delete snapshot from database   ║\n" ;
            std::cout << "   ╚═══════════════════════════════════╝\n\n" ;
            std::cout << "     Snapshot id : " ; std::cin >> snapID ;
            if (radio.get_snap_index(snapID) == -1) {
                std::cout << "\n   Snapshot id does'nt exist in database.\n" ;
                sleep(3) ;
            } else {
                DatabaseHandling::delete_snapshot_from_radiography(radio.get_id(), snapID) ;
            }
        }

        void display_add_report(Radiography radio) {
            int c {getchar()} ;
            std::string rep ;
            std::cout << "\n\n" ;
            std::cout << "   ╔═══════════════════════════╗\n" ;
            std::cout << "   ║   Add report to database  ║\n" ;
            std::cout << "   ╚═══════════════════════════╝\n\n" ;
            std::cout << "   Report content : (Press enter to save)\n" ;
            do {
                c = getchar() ;
                rep += char(c) ;
            } while (c != '\n') ;
            DatabaseHandling::add_report_to_radiography(radio.get_id(), rep) ;
        }

        void display_delete_report(Radiography radio) {
            std::cout << "\n\n" ;
            std::cout << "   ╔════════════════════════════════╗\n" ;
            std::cout << "   ║   Delete report from database  ║\n" ;
            std::cout << "   ╚════════════════════════════════╝\n\n" ;
            std::cout << "   Are you sure you want to delete this report ? (y/n) : " ; char c ; std::cin >> c ;
            if (c == 'y' || c == 'Y') {
                DatabaseHandling::delete_report_from_radiography(radio.get_id()) ;
            }
        }

        // void display_open_snapshot(Radiography radio) {
        //     std::cout << "\n\n" ;
        //     std::cout << "   ╔══════════════════════════════╗\n" ;
        //     std::cout << "   ║   Open snapshot file by id   ║\n" ;
        //     std::cout << "   ╚══════════════════════════════╝\n\n" ;
        //     std::cout << "   Snapshot id : " ; std::string id ; std::cin >> id ;
        //     size_t index {radio.get_snap_index(id)} ;
        //     if (index != -1) {
        //         Snapshot snap {radio.get_snap(index)} ;
        //         std::string path {snap.get_path()} ;
        //         std::string command {"xdg-open" + path} ;
        //         system(command) ;
        //     }
        // }

        void display_snapshotReport_interface() {
            std::cout << "\n\n" ;
            std::string radioID ;
            std::cout << "   ╔════════════════════════════════╗\n" ;
            std::cout << "   ║   Access radiographies by id   ║\n" ;
            std::cout << "   ╚════════════════════════════════╝\n\n" ;
            std::cout << "   Radiography id : " ; std::cin >> radioID ;
            if (DatabaseHandling::get_radiography_by_id(radioID) == -1) {
                std::cout << "\n   Radiography id not in database.\n" ;
                sleep(3) ;
            } else {
                bool menu {true} ;
                while (menu) {
                    DatabaseHandling::upload_radiographies_database() ;
                    Radiography radio {get_radiography(radioID)} ;
                    header() ;
                    std::cout << "   Radiography informations :\n\n" ;
                    std::cout << "        Radiography id : " << radio.get_id() << "\n" ;
                    std::cout << "      Radiography type : " ;
                    if (radio.get_type() == xRay) {
                        std::cout << "xRay\n" ;
                    } else if (radio.get_type() == MRI) {
                        std::cout << "MRI\n" ;
                    } else {
                        std::cout << "Ultrasound\n" ;
                    }
                    std::cout << "     Radiography state : " ;
                    if (radio.get_state() == done) {
                        std::cout << "Done\n" ; 
                    } else {
                        std::cout << "Pending\n" ;
                    }
                    std::cout << "   Date of radiography : " << radio.get_day() << "/" << radio.get_month() << "/" << radio.get_year() << "\n\n\n" ;
                    std::cout << "   Report :\n\n" ;
                    std::cout << radio.get_report().get_content() ;
                    std::cout << "\n\n\n" ;
                    std::cout << "      Table of snapshot :\n\n" ;
                    std::cout << "   ╔════════════════════════════════════════════════════════════════════════════════╗\n" ;
                    std::cout << "   ║id                    ║Path                                                     ║\n" ;
                    std::cout << "   ╚════════════════════════════════════════════════════════════════════════════════╝\n" ;
                    std::cout << "   ╔════════════════════════════════════════════════════════════════════════════════╗\n" ;
                    for (size_t i=0 ; i<radio.get_snaps().size() ; i++) {
                        std::cout << "   ║" << radio.get_snap(i).get_id() << add_tabulation(radio.get_snap(i).get_id(), 22) << "║" ;
                        std::cout << radio.get_snap(i).get_path() << add_tabulation(radio.get_snap(i).get_path(), 57) << "║\n" ;
                    }
                    std::cout << "   ╚════════════════════════════════════════════════════════════════════════════════╝\n\n\n" ;
                    
                    if (user == "patient") {
                        std::cout << "   Options :\n" ;
                        std::cout << "      [0] Exit\n" ;
                        std::cout << "   Selection : " ; char c ; std::cin >> c ;
                        menu = false ;
                    }

                    if (user == "doctor") {
                        std::cout << "   Options :\n" ;
                        std::cout << "      [0] Exit\n" ;
                        std::cout << "      [1] Add snapshot\n" ;
                        std::cout << "      [2] Delete snapshot\n" ;
                        std::cout << "      [3] Add Report\n" ;
                        std::cout << "      [4] Delete Report\n" ;
                        std::cout << "      [5] Change state\n" ;
                        // std::cout << "      [6] Open snapshot file\n" ;
                        std::cout << "   Selection : " ; char c ; std::cin >> c ;

                        switch (c) {
                            case '0' : {
                                menu = false ;
                                break ;
                            }
                            case '1' : {
                                display_add_snapshot(radio) ;
                                break ;
                            }
                            case '2' : {
                                display_delete_snapshot(radio) ;
                                break ;
                            }
                            case '3' : {
                                display_add_report(radio) ;
                                break ;
                            }
                            case '4' : {
                                display_delete_report(radio) ;
                                break ;
                            }
                            case '5' : {
                                DatabaseHandling::change_radiography_state(radio.get_id()) ;
                                break ;
                            }
                            // case '6' : {
                            //     display_open_snapshot(radio) ;
                            //     break ;
                            // }
                            default : {
                                break ;
                            }
                        }
                    }
                }           
            }
        }
} ;


#endif