#include "Ship.h"
#include "Engine.h"
#include "AsteroidField.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "MathManager.h"
#include "RenderManager.h"
#include "SoundManager.h"
#include "StateManager.h"
#include "TextureManager.h"
#include <iostream>
using namespace std;

Ship::Ship(SDL_Rect src, SDL_FRect dst) :
	AnimatedSprite(src, dst, STATE_IDLING), m_thrust(0.5),
	m_angle(270), m_velMax(6.0), m_radius(38), m_rotSpeed(5.0)
{
	m_dx = m_dy = m_velX = m_velY = 0.0;
	m_center = { (m_dst.x + m_dst.w / 2.0f), (m_dst.y + m_dst.h / 2.0f) };
	SetAnimation(STATE_IDLING, 1, 0, 1);
}

Ship::~Ship()
{
	SOMA::StopSound(15);
}

void Ship::Update()
{
	// Rotate player. State-independent.
	
	// Teleport ship. New requirement for Lab 3.
	if (EVMA::KeyPressed(SDL_SCANCODE_T))
	{
		TeleportShip();
	}
	// Spawn bullet.
	
	// Checking animation states.
	
	// Apply drag and finish movement.
	
	// Wrap on screen.
	
	// Update dest rectangle.
	
	// Invoke the animation.
	Animate();
}

void Ship::Render()
{
	SDL_RenderCopyExF(REMA::GetRenderer(), TEMA::GetTexture("sprites"),
		&m_src, &m_dst, m_angle, nullptr, SDL_FLIP_NONE);
}

const double& Ship::GetRadius()	{ return m_radius; }

void Ship::TeleportShip()
{
	// Get a reference to the asteroids vector from Asteroid Field.
	// Hints: Get the current state, invoke GetChild and get the asteroids
	//		  Search for a new center point, doing a collision check with asteroids with a wider radius
	//		  If you've found a clear center point, move the ship there
}
