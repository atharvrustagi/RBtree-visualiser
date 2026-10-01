
compilerunrb:
	g++ -Isrc/include -c rb_visualiser.cpp
	g++ rb_visualiser.o -o rb_visualiser -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system
	rb_visualiser.exe

compilerb:
	g++ -Isrc/include -c rb_visualiser.cpp
	g++ rb_visualiser.o -o rb_visualiser -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

runrb:
	rb_visualiser.exe

compilerunsl:
	g++ -Isrc/include -c sl_visualiser.cpp
	g++ sl_visualiser.o -o sl_visualiser -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system
	sl_visualiser.exe

compilesl:
	g++ -Isrc/include -c sl_visualiser.cpp
	g++ sl_visualiser.o -o sl_visualiser -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system

runsl:
	sl_visualiser.exe

link:
	g++ main.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system 

clean:
	del *.o 

all:
	g++ -Isrc/include -c *.cpp
	g++ main.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system
