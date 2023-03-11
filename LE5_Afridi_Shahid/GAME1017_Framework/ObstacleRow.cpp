#include "ObstacleRow.h"
#include "RenderManager.h"

ObstacleRow::ObstacleRow():m_gapCtr(0), m_gapMax(3)
{
	// Create the vector now.
	for (int i = 0; i < 9; i++)
	{
		m_obstacles.push_back(new Obstacle({ 128.0f * i, 384.0f, 128.0f, 128.0f }));
	}
	m_obstacles.shrink_to_fit();
}

void ObstacleRow::Update()
{
	// When the first obstacles goes completely off-screen.
	if (m_obstacles[0]->GetPos().x <= -128.0f)
	{
		// Pop the first obstacle off.
		delete m_obstacles[0];
		m_obstacles[0] = nullptr;
		m_obstacles.erase(m_obstacles.begin()); // "Pop_front"
		// Add a new obstacle to the end.
		if (m_gapCtr++ % m_gapMax == 0) // Create obstacle with image.
		{
			m_obstacles.push_back(new Obstacle({ 1024.0f, 384.0f, 128.0f, 128.0f }, true));
			// Note, for LE, you'll need last two parameters of Obstacle constructor.
			// You'll also need to randomize the obstacles (definitely for A2).
		}
		else // Create an "empty" obstacle.
		{
			m_obstacles.push_back(new Obstacle({ 1024.0f, 384.0f, 128.0f, 128.0f }));
		}
		m_obstacles.shrink_to_fit();
	}
	// Scroll the obstacles
	for (const auto obstacle : m_obstacles)
		obstacle->Update();
}

void ObstacleRow::Render()
{
	// Blue line under obstacles.
	SDL_SetRenderDrawColor(REMA::GetRenderer(), 0, 0, 255, 255);
	SDL_RenderDrawLine(REMA::GetRenderer(), 0, 512, 1024, 512);
	// Render the obstacles.
	for (const auto obstacle : m_obstacles)
		obstacle->Render();
}
