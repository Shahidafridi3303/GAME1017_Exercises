#include "Obstacle.h"
#include "RenderManager.h"

Obstacle::Obstacle(const SDL_FRect dst, bool hasImage, const SDL_Rect src, const char* key)
	:m_hasImage(hasImage), m_pImage(nullptr)
{
	m_pos = { dst.x, dst.y };
	if (m_hasImage)
	{
		// Create a new image object and pass the parameters.
		// For you to do for LE5.
	}
}

Obstacle::~Obstacle()
{
	if (m_hasImage)
	{
		delete m_pImage;
		m_pImage = nullptr;
	}
}

void Obstacle::Update()
{
	m_pos.x -= kScrollSpeed;
	if (m_hasImage) // or m_pImage != nullptr
	{
		// Update the Image's destination rect x;
		// m_pImage->GetDst()->x = m_pos.x;
	}
}

void Obstacle::Render()
{
	SDL_FRect m_dst = { m_pos.x, m_pos.y, 128.0f, 128.0f };
	if (m_hasImage)
	{
		// Render the Image.
		// SDL_RenderCopyF(...); // Remember includes!
		// Red box for Week 9 lab...
		SDL_SetRenderDrawColor(REMA::GetRenderer(), 255, 0, 0, 255);
		SDL_RenderFillRectF(REMA::GetRenderer(), &m_dst);
	}
	// Render border for just Week 9 lab.
	SDL_SetRenderDrawColor(REMA::GetRenderer(), 128, 0, 128, 255);
	SDL_RenderDrawRectF(REMA::GetRenderer(), &m_dst);
}
