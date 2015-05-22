CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp Vector2D.cpp Vector3D.cpp TransformMatrix2D.cpp TransformMatrix3D.cpp Mathtools.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=CGG


all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	

clean:
	rm -rf *o $(EXECUTABLE)
