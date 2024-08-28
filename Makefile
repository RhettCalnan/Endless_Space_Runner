build: include/background.h include/button.h include/figure.h include/input.h include/menu.h include/meteor.h include/meteorStack.h include/object.h include/physics.h include/planet.h include/planetStack.h include/player.h include/properties.h include/textBox.h include/utilities.h main.cpp score.txt
	g++ -Wall main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o test

run: test
	./test

clean:
	clear