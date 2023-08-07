#include "Player.h"

Player::Player(): m_directionToMove(Vector2(0,0)), m_jumping(false), m_mM(nullptr), m_timeSinceJumped(0), 
m_ascending(false), m_fallAccelleration(0), m_fallTime(0), m_gravityON(false), m_grounded(true), m_crouching(false), m_isdead(false)
{
}

Player::Player(MetaManager* mM, Screen* screen, ImageLibrary& imageLibrary) : m_trans(Vector2(200, 700-16))
, m_gravityON(false), m_fallAccelleration(50),
m_ascending(false), m_fallTime(0),
m_grounded(true), m_jumping(false), m_directionToMove(Vector2(0, 0)), m_crouching(false), m_isdead(false),
m_jumpPower(600), m_timeSinceJumped(0), m_mM(mM), m_anim(Animator(screen, &mM->rM, imageLibrary)), 
m_collider((int)m_trans.m_position.x,(int)m_trans.m_position.y,8*3,8*2), m_currentAnimation(m_anim.animations[0])
{

}

Player::~Player()
{
}

void Player::Update(float dt, Uint32 time, SceneManager& sceneManager, ImageLibrary& imageLibrary)
{
	ApplyGravity();
	Move(dt);
	if (!m_currentAnimation->Update(time, sceneManager, imageLibrary, m_mM))
	{
		m_currentAnimation = m_anim.animations[0];
		m_mM->gM.ChangePlayState(PlayState::Play_Death);
		sceneManager.ChangeScreen(m_mM->gM, m_mM->rM, m_mM->sdM, imageLibrary);
	}
	if (!m_crouching)
	{
		m_collider.SetPosition((int)m_trans.m_position.x, (int)m_trans.m_position.y);
	}
}

void Player::ApplyGravity()
{
	if (m_gravityON)
	{
		if (m_fallTime > 10)
		{
		}
		else
		{
			m_fallAccelleration = (float)2.85 * (m_fallTime);
		}
		if (m_fallAccelleration > 16)
		{
			m_fallAccelleration = 16;
		}
		m_trans.ChangePosition(0, m_fallAccelleration);

		m_fallTime++;

		if (m_trans.m_position.y > 700 - 16)
		{
			ToggleGravity(false);
			m_grounded = true;
			m_trans.m_position.y = 700 - 16;
		}
	}

}

void Player::ToggleGravity(bool value)
{
	m_ascending = false;
	m_fallTime = 0;
	m_gravityON = value;
}

void Player::Move(float dt)
{
	if (m_jumping)
	{
		Jump();
	}
	m_trans.ChangePosition(0, m_directionToMove.y * m_jumpPower * dt);


	if (!m_grounded && m_gravityON == false)
	{
		m_timeSinceJumped++;
		if (m_timeSinceJumped > 4 && m_jumping)
		{
			m_directionToMove.y += 1.5f / (m_timeSinceJumped);
		}
		else if (!m_jumping)
		{
			m_directionToMove.y += 1.5f / (m_timeSinceJumped / 2);
		}
		if (m_directionToMove.y >= 0)
		{
			ToggleGravity(true);
		}
	}
	else if (!m_grounded && m_gravityON == true)
	{
		m_directionToMove.y = 0;
	}
}

void Player::Jump()
{
	if (m_grounded)
	{
		m_mM->sdM.PlaySound(1, m_mM->sdM.lib.getSound(0), 0);
		m_directionToMove.y = -1;
		m_timeSinceJumped = 0;
		m_grounded = false;
		m_ascending = true;
	}
}

void Player::Crouch()
{
	m_collider.rect.h = 8;
	m_collider.SetPosition(m_collider.rect.x, m_collider.rect.y + m_collider.rect.h + 1);
}

void Player::Render()
{
	m_mM->rM.Render(&m_currentAnimation->GetSprite(), m_trans);
	if (m_mM->gM.GetDebugState() == DebugState::Debug_On)
	{
		m_mM->rM.Render(m_collider.rect);
	}
}

void Player::OnKeyDown(KeyCode key)
{
	if (m_grounded)
	{
		if (key == KeyCode::SPACE || key == KeyCode::UP_ARROW)
		{
			if (!m_crouching)
			{
				m_jumping = true;
			}
		}
		if (key == KeyCode::DOWN_ARROW)
		{
			if (!m_crouching && !m_jumping)
			{
				m_crouching = true;
				m_currentAnimation = m_anim.animations[1];
				Crouch();
			}
		}
	}
}
void Player::OnKeyUp(KeyCode key)
{
	if (key == KeyCode::SPACE || key == KeyCode::UP_ARROW)
	{
		m_timeSinceJumped += 2; m_jumping = false;
	}
	if (key == KeyCode::DOWN_ARROW)
	{
		if (m_crouching)
		{
			m_crouching = false;
			m_currentAnimation = m_anim.animations[0];
			m_collider.SetPosition(m_collider.rect.x, m_collider.rect.y - m_collider.rect.h);
			m_collider.rect.h = 16;
		}
	}
}

void Player::Die()
{
	m_isdead = true;
	m_currentAnimation = m_anim.animations[2];
}
