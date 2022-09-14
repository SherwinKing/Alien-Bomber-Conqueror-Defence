#include "Mode.hpp"

#include "Scene.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>
#include <random>
#include<cmath>


const int32_t init_hp = 30000;

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//other methods
	void restart_game();
	void reset_bomb_position(Scene::Transform &transform);
	void bomb_explode(Scene::Transform &bomb_transform, float bomb_distance);

	//----- game state -----

	// game status
	enum GameStatus : uint32_t{
		STOPPED,
		ACTIVE
	};
	GameStatus game_status = STOPPED;

	// HP
	int32_t hp = init_hp;
	// score
	uint32_t score = 0;
	// bomb speed
	float bomb_speed = 0.1f;

	//random generator
	std::mt19937 mt; 

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} left, right, down, up, key_r, left_click;

	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;

	//bomb_transforms
	Scene::Transform* bomb_init_transform;
	std::vector<Scene::Transform*> bomb_transforms;

	//hexapod leg to wobble:
	Scene::Transform *hip = nullptr;
	Scene::Transform *upper_leg = nullptr;
	Scene::Transform *lower_leg = nullptr;
	glm::quat hip_base_rotation;
	glm::quat upper_leg_base_rotation;
	glm::quat lower_leg_base_rotation;
	float wobble = 0.0f;
	
	//camera:
	Scene::Camera *camera = nullptr;

};
