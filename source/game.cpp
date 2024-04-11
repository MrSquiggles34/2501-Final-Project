#include <stdexcept>
#include <string>
#include <iostream>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp> 
#include <SOIL/SOIL.h>
#include <path_config.h>

#include "game.h"
#include "playerbulletgameobject.h"
#include "enemybulletgameobject.h"
#include "enemygameobject.h"
#include "hazardenemygameobject.h"
#include "shooterenemygameobject.h"
#include "chaserenemygameobject.h"

#include "projectilegameobject.h"
#include "collectablegameobject.h"
#include "coingameobject.h"
#include "powerupgameobject.h"
#include "heartgameobject.h"

#include "particles.h"
#include "particlesystem.h"
#include "textgameobject.h"
using namespace std;

namespace game {
	const char *WINDOW_TITLE = "2501 Final Project";
	const unsigned int WINDOW_WIDTH = 600;
	const unsigned int WINDOW_HEIGHT = 900;
	
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
		particleShader_.Init((RESOURCES_DIR+std::string("/shader/particle_vertex_shader.glsl")).c_str(), (RESOURCES_DIR+std::string("/shader/particle_fragment_shader.glsl")).c_str());

		// Initialize text shader
		textShader_.Init((RESOURCES_DIR + std::string("/shader/sprite_vertex_shader.glsl")).c_str(), (RESOURCES_DIR + std::string("/shader/text_fragment_shader.glsl")).c_str());

		// Initialize time
		currentTime_ = 0.0;
	}
	
	void Game::Setup(void) {
		LoadAllTextures();

		player_ = new PlayerGameObject(glm::vec3(0.0f, 0.0f, 0.0f), &textureManager_, 0);
		gameObjects_.push_back(player_);

		// Set up text quad
		livesHudText_ = new TextGameObject(glm::vec3(-3.35f, 5.4f, 0.0f), &textureManager_, 7);
		livesHudText_->SetText("Lives: 3");
		gameObjects_.push_back(livesHudText_);

		scoreHudText_ = new TextGameObject(glm::vec3(-3.35f, 4.2f, 0.0f), &textureManager_, 7);
		scoreHudText_->SetText("Score: 10");
		gameObjects_.push_back(scoreHudText_);

		bulletHudText_ = new TextGameObject(glm::vec3(-3.35f, 3.0f, 0.0f), &textureManager_, 7);
		bulletHudText_->SetText("Weapon A");
		gameObjects_.push_back(bulletHudText_);

		gameObjects_.push_back(new ChaserEnemyGameObject(glm::vec3(-1.0f, 1.0f, 0.0f), &textureManager_ , 2, player_));

		GameObject *background = new GameObject(glm::vec3(0.0f, -5.0f, 0.0f), &textureManager_, 8);
		background->SetTileTexture(true);
		background->SetScaleX(8);
		background->SetTextureWrap(GL_REPEAT);
		gameObjects_.push_back(background);
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
		const char* textures[] = {"player.png", "bullet.png", "destroyer_green.png", "orb.png", "coin.png", "star.png", "heart.png", "font.png", "water.png"};
		
		int geomShaderMode[] = {0, 0, 0, 2, 0, 0, 0, 1, 0};
		Shader* shaders[] = { &spriteShader_, &textShader_, &particleShader_};
		Geometry* geometries[] = { sprite_, sprite_, particles_};

		int numTextures = (sizeof(textures) / sizeof(char*));
		tex_ = new GLuint[numTextures];
		glGenTextures(numTextures, tex_);
		for (int i = 0; i < numTextures; i++){
			SetTexture(tex_[i], (RESOURCES_DIR + std::string(textureDir) + std::string(textures[i])).c_str());
			textureManager_.AddTexture(geometries[geomShaderMode[i]], shaders[geomShaderMode[i]], tex_[i]);
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
			gameObjects_[i]->Render(view_matrix, currentTime_);
		}
	} // Render
	
	void Game::Update(double delta_time) {
		currentTime_ += delta_time;
		UpdateHUDText();
		
		if (currentTime_ - lastEnemySpawnTime_ >= enemySpawnInterval_) {
			SpawnEnemy();
			lastEnemySpawnTime_ = currentTime_;
		}
		
		// Spawn powerups periodically
		if (currentTime_ - lastCoinSpawnTime_ >= coinSpawnInterval_) {
			SpawnCoin();
			lastCoinSpawnTime_ = currentTime_;
		} 
		
		if (currentTime_ - lastPowerSpawnTime_ >= powerSpawnInterval_) {
			SpawnPower();
			lastPowerSpawnTime_ = currentTime_;
		} 
		
		if (currentTime_ - lastHeartSpawnTime_ >= heartSpawnInterval_) {
			SpawnHeart();
			lastHeartSpawnTime_ = currentTime_;
		}

		// Iterate through gameObjects_
		GameObject* background = gameObjects_.back();
		
		for (int i = 0; i < gameObjects_.size(); ++i) {
			GameObject* currentGameObject = gameObjects_[i];

			// Update each game object
			currentGameObject->Update(delta_time);
			
			ShootingGameObject* shooter = dynamic_cast<ShootingGameObject*>(currentGameObject);
			if (shooter && shooter->GetIsShooting() && shooter->GetCanShoot(currentTime_)) {
				gameObjects_.insert(gameObjects_.end(), shooter->CreateProjectile());
				shooter->SetIsShooting(false);
				shooter->SetLastShotTime(currentTime_);
			}
			
			// Iterate through all the other already-updated objects.
			for (int j = 0; j < i; j++) {
				GameObject* otherGameObject = gameObjects_[j];
				// Calculate collisions between objects
				// Calculate before applying to make sure no issues arise (e.g: object is marked for deletion before calculating the reverse collision)
				bool collisionAffectsOther = currentGameObject->IsCollidingWith(otherGameObject);
				bool collisionAffectsCurrent = otherGameObject->IsCollidingWith(currentGameObject);
				// Apply collision effects if necessary
				if (collisionAffectsOther) otherGameObject->OnCollisionWith(currentGameObject);
				if (collisionAffectsCurrent) currentGameObject->OnCollisionWith(otherGameObject);
			}

			// Check if the current game object is marked for deletion and delete it if necessary
			if (currentGameObject->IsMarkedForDeletion()) {
				std::cout << "Deleting object #" << i << std::endl;
				delete currentGameObject;
				gameObjects_.erase(gameObjects_.begin() + i);
				--i; // Decrement i to account for the removed object
			}
		}
	} // Update
	
	void Game::HandleUserInput() {
		GameObject* player = gameObjects_[0];

		if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window_, true);
		}
		
		float playerSpeed = 20.0f;
		
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
		if (glfwGetKey(window_, GLFW_KEY_SPACE) == GLFW_PRESS && player_->GetCanShoot(glfwGetTime())) {
			player_->SetIsShooting(true);
		}
		if (!cycleWeaponButtonPressed_ && glfwGetKey(window_, GLFW_KEY_TAB) == GLFW_PRESS) {
			player_->CycleCurrentWeapon();
			cycleWeaponButtonPressed_ = true;
		}
		if (glfwGetKey(window_, GLFW_KEY_TAB) == GLFW_RELEASE) {
			cycleWeaponButtonPressed_ = false;
		}
	}
	
	void Game::ResizeCallback(GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	void Game::UpdateHUDText() {
		// Update HUD text to display remaining lives
		int lives = player_->GetLives();
		if (lives > 0) {
			std::string livesText = "Lives: " + std::to_string(player_->GetLives());
			livesHudText_->SetText(livesText);
			std::string scoreText = "Score: " + std::to_string(player_->GetScore());
			scoreHudText_->SetText(scoreText);
			std::string weaponText = "Weapon: " + std::to_string(player_->GetCurrentWeapon() + 1);
			bulletHudText_->SetText(weaponText);
		}
		else {
			livesHudText_->SetText("Lives: 0");
		}
		

		
	}
}
