CXX = g++
CPPFLAGS = -w -std=c++17
LIBS = -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image -lSDL2_net

SOURCES=Main.cpp Maze.cpp Texture.cpp Timer.cpp Droid.cpp
OBJECTS=Main.o Maze.o Texture.o Timer.o Droid.o
EXECUTABLE=simulate

all: 
	$(CXX) -c $(CPPFLAGS) $(LIBS) $(SOURCES) 
	$(CXX) $(LIBS)  $(OBJECTS) -o $(EXECUTABLE)

clean:
	rm -f $(OBJECTS)
	rm -f $(EXECUTABLE)