#include "PlatformPlayer.h"
#include "Engine.h"
#include "DebugManager.h"
#include "EventManager.h"
#include "RenderManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include <cmath>
#include <iostream>
using namespace std;

PlatformPlayer::PlatformPlayer(SDL_Rect src, SDL_FRect dst) :AnimatedSprite(src, dst, STATE_JUMPING),
	m_grounded(false), m_facingLeft(false), m_maxVelX(9.0),
	m_maxVelY(kJumpForce), m_grav(kGrav), m_drag(0.8)
{
	m_accelX = m_accelY = m_velX = m_velY = 0.0;
	SetAnimation(m_state, 0, 0, 0); // Initialize jump animation.
}

void PlatformPlayer::Update()
{
	// Checking states.
	switch (m_state)
	{
	case STATE_IDLING:
		// Transition to run.
		if (EVMA:: KeyHeld(SDL_SCANCODE_A) || EVMA::KeyHeld(SDL_SCANCODE_D))
		{
			SetAnimation(STATE_RUNNING, 0, 0, 0);
		}
			// Transition to jump.
		if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && m_grounded)
		{
			m_accelY = -kJumpForce; // SetAccelY(-JUMPFORCE);
			m_grounded = false; // SetGrounded(false);
			SOMA::PlaySound("jump");
			SetAnimation(STATE_JUMPING, 0, 0, 0);
		}
		break;
	case STATE_RUNNING:
		// Fill in run state for LE4
		// Move left and right.
		if (EVMA::KeyHeld(SDL_SCANCODE_A))
		{
			m_accelX = -1.5;
			// Change character facing for animation.
		}
		else if (EVMA::KeyHeld(SDL_SCANCODE_D))
		{
			m_accelX = 1.5;
		}
		// Transition to jump.
		if (EVMA::KeyPressed(SDL_SCANCODE_SPACE) && m_grounded)
		{
			m_accelY = -kJumpForce; // SetAccelY(-JUMPFORCE);
			m_grounded = false; // SetGrounded(false);
			SOMA::PlaySound("jump");
			SetAnimation(STATE_JUMPING, 0, 0, 0);
		}
		// TRansition to idle.
		if (!EVMA::KeyHeld(SDL_SCANCODE_A) && !EVMA::KeyHeld(SDL_SCANCODE_D))
		{
			SetAnimation(STATE_IDLING, 0, 0, 0);   // Set actual parameters for animation.
		}
		break;
	case STATE_JUMPING:
		// Move in mid-air.
		if (EVMA::KeyHeld(SDL_SCANCODE_A))
		{
			m_accelX = -1.5;
			// Change character facing for animation.
		}
		else if (EVMA::KeyHeld(SDL_SCANCODE_D))
		{
			m_accelX = 1.5;
		}
		// Hit the ground, transition to run.
		if (m_grounded)
		{
			SetAnimation(STATE_RUNNING, 0, 0, 0);
		}
		break;
	}
	// Player movement. X axis first.
	m_velX += m_accelX; // Acceleration.
	m_velX *= (m_grounded ? m_drag : 1.0); // Deceleration.
	m_velX = std::min(std::max(m_velX, -m_maxVelX), m_maxVelY);
	m_dst.x += (float)m_velX;
	// Y axis now.
	m_velY += m_accelY + m_grav;
	m_velY = std::min(std::max(m_velY, -m_maxVelY), m_maxVelY);
	m_dst.y += (float)m_velY;
	// Resetting accel every frame.
	m_accelX = m_accelY = 0.0; 
	// Invoke the animation.
	Animate();
}

void PlatformPlayer::Render()
{
	DEMA::DrawRect(*GetDst(), true, { 255, 0, 0, 255 });
}

void PlatformPlayer::Stop()
{
	StopX();
	StopY();
}

void PlatformPlayer::StopX() { m_velX = 0.0; }

void PlatformPlayer::StopY() { m_velY = 0.0; }

void PlatformPlayer::SetAccelX(double accel) { m_accelX = accel; }

void PlatformPlayer::SetAccelY(double accel) { m_accelY = accel; }

bool PlatformPlayer::IsGrounded() { return m_grounded; }

void PlatformPlayer::SetGrounded(bool grounded) { m_grounded = grounded; }

double PlatformPlayer::GetVelX() { return m_velX; }

double PlatformPlayer::GetVelY() { return m_velY; }

void PlatformPlayer::SetX(float x) { m_dst.x = x; }

void PlatformPlayer::SetY(float y) { m_dst.y = y; }