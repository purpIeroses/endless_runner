#ifndef PLAYER_H_DEFINED
#define PLAYER_H_DEFINED

#include "Animator.h"
#include "Transform.h"
#include "Keycode.h"
#include "Collider.h"
#include "ManagerManager.h"
#include "SceneManager.h"

class Player
{
public:
	MetaManager* m_mM;

	Transform m_trans;
	Collider m_collider;

	Animator m_anim;
	Animation* m_currentAnimation;

	bool m_jumping;
	bool m_grounded;
	bool m_crouching;
	bool m_isdead;

	float m_jumpPower;

	Vector2 m_directionToMove;

	bool m_gravityON;
	bool m_ascending;
	int m_fallTime;
	float m_fallAccelleration;
	int m_timeSinceJumped;

	Player();
	Player(MetaManager* mM, Screen* screen, ImageLibrary& imageLibrary);
	~Player();

	void Update(float dt, Uint32 time, SceneManager& sceneManager, ImageLibrary& imageLibrary);
	
	void ApplyGravity();
	void ToggleGravity(bool value);

	void Move(float dt);
	void Jump();
	void Crouch();

	void Render();

	void OnKeyDown(KeyCode key);
	void OnKeyUp(KeyCode key);
	void Die();
};

#endif