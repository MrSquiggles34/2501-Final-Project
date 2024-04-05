#include <stdexcept>
#include <string>
#include <iostream>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp> 
#include <SOIL/SOIL.h>
#include <path_config.h>

#include "game.h"
#include "playerbulletgameobject.h"
#include "enemygameobject.h"

#include "particles.h"
#include "particlesystem.h"

namespace game {
	const char *WINDOW_TITLE = "2501 Final Project";
	const unsigned int WINDOW_WIDTH = 800;
	const unsigned int WINDOW_HEIGHT = 600;
	
	const glm::vec3 BACKGROUND_COLOUR(0.0, 0.0, 1.0);
	
	const std::string RESOURCES_DIR = RESOURCES_DIRECTORY;
	
	Game::Game() {}
	
	Game::~Game() {
		delete sprite_;
		delete particles_;

		for (int i = 0; i < gameObjects_.size(); i++) {
			delete gameObjects_[i];
		}
		
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
		
		// Sprite Geometry
		sprite_ = new Sprite();
		sprite_->CreateGeometry();

		particles_ = new Particles();
		particles_->CreateGeometry();

		// Initialize sprite shader
		spriteShader_.Init((RESOURCES_DIR+std::string("/shader/sprite_vertex_shader.glsl")).c_str(), (RESOURCES_DIR+std::string("/shader/sprite_fragment_shader.glsl")).c_str());

		// Initialize particle shader
		particle_shader_.Init((RESOURCES_DIR + std::string("/shader/particle_vertex_shader.glsl")).c_str(), (RESOURCES_DIR + std::string("/shader/particle_fragment_shader.glsl")).c_str());

		// Initialize time
		currentTime_ = 0.0;
	}
	
	void Game::Setup(void) {
		LoadAllTextures();
		
		player_ = new PlayerGameObject(glm::vec3(0.0f, 0.0f, 0.0f), &textureManager_, 0);
		gameObjects_.push_back(player_);

		gameObjects_.push_back(new EnemyGameObject(glm::vec3(-1.0f, 1.0f, 0.0f), &textureManager_ , 2));

		// This part is probably incorrect
		GameObject* particles = new ParticleSystem(glm::vec3(-0.5f, 0.0f, 0.0f), &textureManager_, 2,player_);
		float pi_over_two = glm::pi<float>() / 2.0f;
		particles->SetDirection(-pi_over_two);
		gameObjects_.push_back(particles);
	}
	
	void Game::SetTexture(GLuint w, const char *fname) {
		// Bind texture buffer
		glBindTexture(GL_TEXTURE_2D, w);

		// Load texture from a file to the buffer
		int width, height;
		unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGBA);
		if (!image){
			std::cout << "Cannot load texture " << fname << std::endl;
		} else {
			std::cout << "Loaded " << width << " by " << height << " texture \"" << fname << "\"" << std::endl;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);

		// Texture Wrapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Texture Filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	
	void Game::LoadAllTextures() {
		const char* textureDir = "/assets/img/";
		const char* textures[] = {"player.png", "bullet.png", "destroyer_green.png"};
		
		int numTextures = (sizeof(textures) / sizeof(char*));
		tex_ = new GLuint[numTextures];
		glGenTextures(numTextures, tex_);
		for (int i = 0; i < numTextures; i++){
			SetTexture(tex_[i], (RESOURCES_DIR + std::string(textureDir) + std::string(textures[i])).c_str());
			textureManager_.AddTexture(sprite_, &spriteShader_, tex_[i]);
		}
		glBindTexture(GL_TEXTURE_2D, tex_[0]);
	} // LoadAllTextures
	
	void Game::Run(void) {
		double prevTime = glfwGetTime();
		while(!glfwWindowShouldClose(window_)) {
			double currTime = glfwGetTime();
			double delta_time = currTime - prevTime;
			prevTime = currTime;
			glfwPollEvents();
			HandleUserInput();
			Update(delta_time);
			Render();
			glfwSwapBuffers(window_);
		}
	} // Run
	
	void Game::Render() {
		glClearColor(BACKGROUND_COLOUR.r, BACKGROUND_COLOUR.g, BACKGROUND_COLOUR.b, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		int width, height;
		glfwGetWindowSize(window_, &width, &height);
		
		glm::mat4 window_scale_matrix;
		if (width > height){
			float aspect_ratio = ((float) width)/((float) height);
			window_scale_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f/aspect_ratio, 1.0f, 1.0f));
		} else {
			float aspect_ratio = ((float) height)/((float) width);
			window_scale_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f/aspect_ratio, 1.0f));
		}
		
		float camera_zoom = 0.25f;
		glm::mat4 camera_zoom_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(camera_zoom, camera_zoom, camera_zoom));
		
		glm::mat4 view_matrix = window_scale_matrix * camera_zoom_matrix;
		
		for (int i = 0; i < gameObjects_.size(); i++) {
			gameObjects_[i]->Render(view_matrix);
		}
	} // Render
	
	void Game::Update(double delta_time) {
		currentTime_ += delta_time;
		
		for (int i = 0; i < gameObjects_.size(); i++) {
			GameObject* currentGameObject = gameObjects_[i];


			for (int i = 0; i < gameObjects_.size(); ) {
				GameObject* currentGameObject = gameObjects_[i];

				currentGameObject->Update(delta_time);

				// Check if the current game object is marked for deletion, delete
				if (currentGameObject->IsMarkedForDeletion()) {
					delete currentGameObject;
					gameObjects_.erase(gameObjects_.begin() + i); 
				}
				else {
					++i; 
				}
			}
			
		}
	} // Update
	
	void Game::HandleUserInput() {
		GameObject* player = gameObjects_[0];

		if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window_, true);
		}
		
		float playerSpeed = 1.0f;
		
		if (glfwGetKey(window_, GLFW_KEY_W) == GLFW_PRESS) {
			player_->AddRelativeMotion(glm::vec3(playerSpeed, 0.0f, 0.0f));
		}
		if (glfwGetKey(window_, GLFW_KEY_S) == GLFW_PRESS) {
			player_->AddRelativeMotion(glm::vec3(-playerSpeed, 0.0f, 0.0f));
		}
		if (glfwGetKey(window_, GLFW_KEY_A) == GLFW_PRESS) {
			player_->AddRelativeMotion(glm::vec3(0.0f, -playerSpeed, 0.0f));
		}
		if (glfwGetKey(window_, GLFW_KEY_D) == GLFW_PRESS) {
			player_->AddRelativeMotion(glm::vec3(0.0f, playerSpeed, 0.0f));
		}
		if (glfwGetKey(window_, GLFW_KEY_SPACE) == GLFW_PRESS && glfwGetTime() - player_->getLastShotTime() > player_->getShootingCooldown())
		{
			std::cout << "fired" << std::endl;
			glm::vec3 curpos = player->GetPosition();
			
			float bulletOffset = 0.5f; // Adjust this value as needed
			glm::vec3 bulletPosition = curpos + glm::vec3(0.0f, bulletOffset, 0.0f);

			PlayerBulletGameObject* bullet = new PlayerBulletGameObject(bulletPosition, &textureManager_, 1);
			gameObjects_.insert(gameObjects_.end(), bullet);

			// Update the last shot time
			player_->setLastShotTime(glfwGetTime());
		}
	}
	
	void Game::ResizeCallback(GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
	}
}
