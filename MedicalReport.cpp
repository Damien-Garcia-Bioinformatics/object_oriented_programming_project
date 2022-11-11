#include <string>
#include "class.hpp"

// --- Get functions --- //

std::string MedicalReport::get_content() {
	return this->content ;
} 
std::string MedicalReport::get_password() {
	return this->password ;
}

// --- Set functions --- //

void MedicalReport::set_content(std::string content) {
	this->content = content ;
}
void MedicalReport::set_password(std::string password) {
	this->password = password ;
}

// --- Constructor --- //

MedicalReport::MedicalReport(std::string content, std::string password) {
	set_content(this->content) ;
	set_password(this->password) ;
}

// --- Other functions --- //

bool MedicalReport::isValidPassword(std::string password) {
	if (this->password == password) {
		return true ;
	}
	return false ;
}