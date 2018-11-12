CXX      = g++ #Compiler used
CXX_FILE = $(wildcard *.cpp) #Looks for files that end in .cpp
TARGET   = $(patsubst %.cpp,%,$(CXX_FILE)) #Target name is only going to be test
CXXFLAGS = -g -std=c++11 -Wall -Werror -pedantic-errors -fmessage-length=0 #-g is debug mode / -Wall warn on all things / -Werror Turn all warnings into errors / -pedantic-errors Turn on extra errors

all: #all invokes an instruction / -o means output name
	$(CXX) $(CXXFLAGS) $(CXX_FILE) -o $(TARGET) 
clean:
	rm -f $(TARGET) $(TARGET).exe