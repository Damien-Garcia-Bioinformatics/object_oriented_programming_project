#ifndef __SNAPSHOT__
#define __SNAPSHOT__


#include <iostream>
#include <string>


class Snapshot {
    private :
        // Attributes :
        std::string id ;
        std::string path ;

    public :
        // Set functions :
        void set_id(std::string id) {
            this->id = id ;
        }
        void set_path(std::string path) {
            this->path = path ;
        }

        // Get functions :
        std::string get_id() {
            return this->id ;
        }
        std::string get_path() {
            return this->path ;
        }

        // Constructor :
        Snapshot(std::string id, std::string path) {
            set_id(id) ;
            set_path(path) ;
        }
        Snapshot() {
            set_id("") ;
            set_path("") ;
        }
        ~Snapshot() { }
} ;


#endif