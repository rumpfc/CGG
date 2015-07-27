CC=g++
CFLAGS=-c -Wall -std=c++0x -Wno-reorder
LDFLAGS=
SOURCES=Camera2D.cpp Camera3D.cpp Color.cpp Cube3D.cpp Ellipse2D.cpp Image.cpp Line2D.cpp main.cpp Material.cpp Mathtools.cpp Object2D.cpp Object3D.cpp Painter.cpp Rectangle2D.cpp Renderer.cpp Renderer2D.cpp Renderer3D.cpp Renderer3DRasterization.cpp RendererSimpleDrawing.cpp Scene2D.cpp Scene3D.cpp Sphere3D.cpp Surface2D.cpp Surface3D.cpp Texture.cpp TransformMatrix2D.cpp TransformMatrix3D.cpp Vector2D.cpp Vector3D.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=CGG


all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
	

clean:
	rm -rf *o $(EXECUTABLE)
