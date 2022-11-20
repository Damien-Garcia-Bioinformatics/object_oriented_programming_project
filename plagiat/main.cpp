#include <iostream>
#include <fstream>

//#include "patient.hpp"
//#include "doctor.hpp"
#include "radiography.hpp"
//#include "interface.cpp"
//#include "database.hpp"

int main() {
	List_Radiography test("data.txt");
	test.get_test();
    

	return 0 ;
}
