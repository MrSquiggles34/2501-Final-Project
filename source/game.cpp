#include <stdexcept>
#include <string>
#include <iostream>

#include "game.h"

namespace game {
	const char *WINDOW_TITLE = "2501 Final Project";
	const unsigned int WINDOW_WIDTH = 800;
	const unsigned int WINDOW_HEIGHT = 600;
	
	Game::Game() {}
	
	Game::~Game() {
		glfwDestroyWindow(window_);
		glfwTerminate();
	}
	
	void Game::Init(void) {
		if (!glfwInit()) throw(std::runtime_error(std::string("Failed to initialize the GLFW library")));
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		window_ = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
		if (!window_) {
			glfwTerminate();
			throw(std::runtime_error(std::string("Failed to create window")));
		}
		glfwMakeContextCurrent(window_);
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK) {
			throw(std::runtime_error(std::string("Could not initialize the GLEW library: ") + std::string((const char *)glewGetErrorString(err))));
		}
		glfwSetFramebufferSizeCallback(window_, ResizeCallback);
	}
	
	void Game::Setup(void) {
		
	}
	
	void Game::Run(void) {
		while(!glfwWindowShouldClose(window_)) {
			glfwPollEvents();
			HandleUserInput();
		}
	}
	
	void Game::HandleUserInput() {
		if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window_, true);
		}
	}
	
	void Game::ResizeCallback(GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
	}
}
