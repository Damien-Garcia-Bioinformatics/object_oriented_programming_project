# Object Oriented Programming  (OOP)
# Damien GARCIA, Florian ECHELARD
# M2BB
 

##############################################################################
#                     Makefile for project compilation                       #
##############################################################################


# Ignored if not specificaly called
.PHONY: clean rebuild test_simple test_complex test_semantic1 test_semantic2 test_semantic3 test_semantic4

# Variables
EXE = main
MAIN = main.cpp
CXX = g++
CXXFLAGS = -Wall -O2
OBJECTS = MedicalExamination.o MedicalReport.o Patient.o Radiography.o Snapshot.o


# Creates executable file
all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(MAIN) $(OBJECTS)


# Creation of object files of data generation functions
MedicalExamination.o:
	$(CXX) $(CXXFLAGS) -c MedicalExamination.cpp

MedicalReport.o:
	$(CXX) $(CXXFLAGS) -c MedicalReport.cpp

Patient.o:
	$(CXX) $(CXXFLAGS) -c Patient.cpp

Radiography.o:
	$(CXX) $(CXXFLAGS) -c Radiography.cpp

Snapshot.o:
	$(CXX) $(CXXFLAGS) -c Snapshot.cpp


##############################################################################
#                    Shortcuts (use : "main [shortcut]")                     #
##############################################################################

# Removes all generated files by previous compilations
clean:
	-rm -f *.o *.gch $(EXE)

# Combination of "make clean" and "make all" commands
rebuild:
	$(MAKE) clean all