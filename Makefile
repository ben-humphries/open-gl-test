files = main.cpp

release:
	g++ $(files) -o open-gl-test -lsfml-graphics -lsfml-system -lsfml-window -lGL
debug:
	g++ $(files) -o open-gl-test -lsfml-graphics -lsfml-system -lsfml-window -lGL -g
