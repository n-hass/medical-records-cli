# the compiler and flags that will be used for default builds
# -g for debugging information
# C++11 standard is enforced
# clang++ is used as the compiler
CXX = clang++
CXXFLAGS = -std=c++17 -g -Wall

# required flags to link the boost library to the binary
BOOST = -Iboost/include -Lboost -lboost_system -lboost_serialization


# All non-driver source code files
SRC = User.cpp Patient.cpp Doctor.cpp Record.cpp TextEditor.cpp termCommands.cpp global.cpp
OBJ = $(SRC:.cpp=.o)

# All test drivers. add here
TESTS = termCommandsTest boostTest usersTest functionsTest serialTest loggerTest ioTest


##################################################################################################################

#					## Build Targets ##

main: $(OBJ) main.cpp
	$(CXX) $(CXXFLAGS) -o recordSystem main.cpp $(OBJ) $(BOOST)

#					# end main


##################################################################################################################

#					## Testing targets ##
tests: $(TESTS) # running this will build all tests

termCommandsTest: testDrivers/termCommandsTest.cpp
	$(CXX) $(CXXFLAGS) -o termCommandsTest testDrivers/termCommandsTest.cpp -I.. -I./ $(BOOST)

usersTest: testDrivers/usersTest.cpp
	$(CXX) $(CXXFLAGS) -o usersTest testDrivers/boostTest.cpp User.cpp Patient.cpp Doctor.cpp Record.cpp -I.. -I./ $(BOOST)

boostTest: testDrivers/boostTest.cpp
	$(CXX) $(CXXFLAGS) -o boostTest testDrivers/boostTest.cpp -I.. -I./ $(BOOST)

serialTest: testDrivers/serialTest.cpp
	$(CXX) $(CXXFLAGS) -o serialTest testDrivers/serialTest.cpp User.cpp Patient.cpp Doctor.cpp Record.cpp TextRecord.cpp TextEditor.cpp termCommands.cpp -I.. -I./ $(BOOST)

functionsTest: testDrivers/functionsTest.cpp
	$(CXX) $(CXXFLAGS) -o functionsTest testDrivers/functionsTest.cpp -I.. -I./

loggerTest: testDrivers/loggerTest.cpp Logger.hpp
	$(CXX) $(CXXFLAGS) -o loggerTest testDrivers/loggerTest.cpp -I.. -I./ $(BOOST)

ioTest: testDrivers/ioTest.cpp
	$(CXX) $(CXXFLAGS) -o ioTest testDrivers/ioTest.cpp -I.. -I./

#					# end tests


##################################################################################################################

#					## Cleans ##
clean: cleanMain cleanTests cleanObjs

cleanMain:
	rm -f recordSystem
	rm -rf recordSystem.dSYM

cleanTests:
	for testFile in ${TESTS}; do\
		rm -f $$testFile;\
		rm -rf $$testFile.dSYM;\
	done
	rm -f archive.dat

cleanObjs:
	rm -f *.o