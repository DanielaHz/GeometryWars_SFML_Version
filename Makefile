all: compile link

compile:
	
	g++ -c main.cpp -I"C:\Users\ye-da\Documents\libraries\SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit\SFML-2.5.1\include" -DSFML_STATIC -g
	g++ -c Game.cpp -I"C:\Users\ye-da\Documents\libraries\SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit\SFML-2.5.1\include" -DSFML_STATIC -g
	g++ -c EntityManager.cpp -I"C:\Users\ye-da\Documents\libraries\SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit\SFML-2.5.1\include" -DSFML_STATIC -g
	g++ -c Vec2.cpp -I"C:\Users\ye-da\Documents\libraries\SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit\SFML-2.5.1\include" -DSFML_STATIC -g
	g++ -c Entity.cpp -I"C:\Users\ye-da\Documents\libraries\SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit\SFML-2.5.1\include" -DSFML_STATIC -g



link:
	g++ main.o Game.o EntityManager.o Vec2.o Entity.o -o main -L"C:\Users\ye-da\Documents\libraries\SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit\SFML-2.5.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main -g

clean:
	del main.exe *.o
