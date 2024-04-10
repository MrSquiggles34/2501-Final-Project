#include "spawnergameobject.h"

namespace game {
    SpawnerGameObject::SpawnerGameObject(glm::vec3 position, TextureManager* textureManager)
        : GameObject(position, textureManager) {}

    SpawnerGameObject::~SpawnerGameObject() {}

    void SpawnerGameObject::AddSpawnParameters(int objectType, double spawnInterval, glm::vec3 spawnLocation) {
        lastSpawnTimes_[objectType] = 0.0; // Initialize last spawn time for the object type
        spawnIntervals_[objectType] = spawnInterval; // Set the spawn interval for the object type
        spawnLocations_[objectType] = spawnLocation; // Set the spawn location for the object type
    }

    void SpawnerGameObject::Update(double delta_time) {
        // Call base class Update method
        GameObject::Update(delta_time);

        // Check if it's time to spawn each object type
        double currentTime = glfwGetTime();
        for (auto& pair : spawnIntervals_) {
            int objectType = pair.first;
            double spawnInterval = pair.second;
            double& lastSpawnTime = lastSpawnTimes_[objectType];

            // Check if it's time to spawn an object of this type
            if (currentTime - lastSpawnTime >= spawnInterval) {
                // Spawn the object
                SpawnObject(objectType);

                // Update the last spawn time
                lastSpawnTime = currentTime;
            }
        }
    }

    void SpawnerGameObject::SpawnObject(int objectType) {
        // Get the spawn location for the object type
        glm::vec3 spawnLocation = spawnLocations_[objectType];

        // Create the object based on the objectType
        switch (objectType) {
            // Add cases for different types of objects to spawn
        case 1: // Example case
            // Spawn the object at the specified location
            // GameObject* object = new SomeGameObject(spawnLocation, textureManager_, ...);
            // gameObjects_.push_back(object);
            break;
            // Add more cases as needed
        }
    }
}
