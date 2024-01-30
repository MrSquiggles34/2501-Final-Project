#include <exception>
#include <iostream>

#include "game.h"

int main() {
	game::Game g;
	
	try {
		g.Init();
		g.Setup();
		g.Run();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}
