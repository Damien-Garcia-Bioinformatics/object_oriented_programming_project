#ifndef __RADIOGRAPHY__
#define __RADIOGRAPHY__


#include <iostream>
#include <string>


class Radiography {
    protected :
        typedef enum radiographyType {xRay, ultrasound, MRI} radiographyType ;
        typedef enum radiographyState {done, pending} radiographyState ;
        struct dateFormat {
            size_t day ;
            size_t month ;
            size_t year ;
        } ;

    private :
        // Attributes :
    	radiographyType type ;
		radiographyState state ;
        dateFormat date ;

    public :
        // Set functions :
        void set_type(radiographyType type) {
            this->type = type ;
        }
        void set_state(radiographyState state) {
            this->state = state ;
        }
        void set_day(size_t day) {
            this->date.day = day ;
        }
        void set_month(size_t month) {
            this->date.month = month ;
        }
        void set_year(size_t year) {
            this->date.year = year ;
        }
        void set_date(dateFormat date) {
            set_day(date.day) ;
            set_month(date.month) ;
            set_year(date.year) ;
        }

        // Get functions :
        radiographyType get_type() {
            return this->type ;
        }
        radiographyState get_state() {
            return this->state ;
        }
        size_t get_day() {
            return this->date.day ;
        }
        size_t get_month() {
            return this->date.month ;
        }
        size_t get_year() {
            return this->date.year ;
        }
        dateFormat get_date() {
            return this->date ;
        }

        // Constructor :
        Radiography(radiographyType type, radiographyState state, size_t day, size_t month, size_t year) {
            set_type(type) ;
            set_state(state) ;
            set_day(day) ;
            set_month(month) ;
            set_year(year) ;
        }
        Radiography(radiographyType type, radiographyState state, dateFormat date) {
            set_type(type) ;
            set_state(state) ;
            set_date(date) ;
        }
} ;


#endif