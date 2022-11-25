# Object Oriented Programming  (OOP)
# Damien GARCIA, Florian ECHELARD
# M2BB
 

##############################################################################
#                     Makefile for project compilation                       #
##############################################################################


# Ignored if not specificaly called
.PHONY: clean rebuild 

# Variables
EXE = main
MAIN = main.cpp
CXX = g++
CXXFLAGS = -Wall -O2
OBJECTS = header/database.hpp header/doctor.hpp header/interface.hpp header/patient.hpp header/radiography.hpp header/report.hpp header/snapshot.hpp header/user.hpp


# Creates executable file
all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(MAIN) $(OBJECTS)

main:
	$(CXX) -o $(EXE) $(MAIN)

# Creation of precompiled object files
database:
	$(CXX) $(CXXFLAGS) -c header/database.hpp

interface:
	$(CXX) $(CXXFLAGS) -c header/interface.hpp

user:
	$(CXX) $(CXXFLAGS) -c header/user.hpp

doctor:
	$(CXX) $(CXXFLAGS) -c header/doctor.hpp

patient:
	$(CXX) $(CXXFLAGS) -c header/patient.hpp

radiography:
	$(CXX) $(CXXFLAGS) -c header/radiography.hpp

report:
	$(CXX) $(CXXFLAGS) -c header/report.hpp

snapshot:
	$(CXX) $(CXXFLAGS) -c header/snapshot.hpp


##############################################################################
#                    Shortcuts (use : "main [shortcut]")                     #
##############################################################################

# Removes all generated files by previous compilations
clean:
	-rm -f *.o *.gch $(EXE)

# Combination of "make clean" and "make all" commands
rebuild:
	$(MAKE) clean all