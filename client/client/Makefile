# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -Wall -std=c++17 -pthread

# Define the include directory for SFML. Modify as needed.
SFML_INCLUDE = /usr/include/SFML

# Define the SFML libraries path. Modify as needed.
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

# Source files
SOURCES = alert.cpp client.cpp formAddRoom.cpp tetris.cpp tetris2.cpp network.cpp

# Include directories
INCLUDES = -I$(SFML_INCLUDE) -I./

# Object files
OBJS = $(SOURCES:.cpp=.o)

# Executable name
EXEC = client

# Build all targets
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(SFML_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS) $(EXEC)
