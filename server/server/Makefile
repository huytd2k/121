CXX = g++
CXXFLAGS = -Wall -std=c++17 -pthread

# Include directories
INCLUDES = -I./dist/json

# Source files
SOURCES = dist/jsoncpp.cpp server.cpp network.cpp

# Object files
OBJS = $(SOURCES:.cpp=.o)

# Executable name
EXEC = server

# Default build
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(EXEC)
