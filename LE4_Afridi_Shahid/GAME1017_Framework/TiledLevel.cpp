#include "TiledLevel.h"
#include "RenderManager.h"
#include "TextureManager.h"
#include <iostream>

TiledLevel::TiledLevel(const unsigned short rows, const unsigned short cols, const int tileWidth, const int tileHeight, 
	const char* tileData, const char* levelData, const char* tileKey) :m_rows(rows), m_cols(cols), m_tileKey(tileKey)
{
	// First build prototype tiles.
	std::ifstream inFile(tileData);
	if (inFile.is_open())
	{
		char key;
		int x, y;
		bool obs, haz;
		while (!inFile.eof())  // Continue until the end of the file.
		{
			inFile >> key >> x >> y >> obs >> haz;
			m_tiles.emplace(key, new Tile({ x * tileWidth, y * tileHeight, tileWidth, tileHeight },
				{ 0.0f, 0.0f, (float)tileWidth, (float)tileHeight }, obs, haz) );
		}
		inFile.close();
	}
	else
	{
		std::cout << "Error opening tileData file!" << std::endl;
		return;
	}
	inFile.close();
	// Now construct the level.
	inFile.open(levelData);
	if (inFile.is_open())
	{
		char key;
		m_level.resize(m_rows);  // Resize or we cannot use subscripts.
		for (unsigned row =  0; row < m_rows; row++)
		{
			m_level[row].resize(m_cols);
			for (unsigned col = 0; col < m_cols; col++)
			{
				inFile >> key;
				m_level[row][col] = m_tiles[key]->Clone();
				m_level[row][col]->SetXY((float)(col * tileWidth), (float)(row * tileHeight));
				if (m_level[row][col]->IsObstacle())
					m_obstacles.push_back(m_level[row][col]);
			}
		}

	}
	else
	{
		std::cout << "Error opening levelData file!" << std::endl;
		return;
	}
}

TiledLevel::~TiledLevel()
{
	// Clear the tile clones. This also clears the ones in m_obstacles.
	
	// Clear the original tiles.
	
}

void TiledLevel::Render()
{
	for (unsigned row = 0; row < m_rows; row++)
	{
		for (unsigned col = 0; col < m_cols; col++)
		{
			SDL_RenderCopyF(REMA::GetRenderer(), TEMA::GetTexture(m_tileKey),
				m_level[row][col]->GetSrc(), m_level[row][col]->GetDst());
		}
	}
}

std::vector<Tile*>& TiledLevel::GetObstacles() { return m_obstacles; }