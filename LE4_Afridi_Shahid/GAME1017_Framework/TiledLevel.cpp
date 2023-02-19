#include "TiledLevel.h"
#include "RenderManager.h"
#include "TextureManager.h"

TiledLevel::TiledLevel(const unsigned short rows, const unsigned short cols, const int tileWidth, const int tileHeight, 
	const char* tileData, const char* levelData, const char* tileKey) :m_rows(rows), m_cols(cols), m_tileKey(tileKey)
{
	// First build prototype tiles.
	
	// Now construct the level.
	
}

TiledLevel::~TiledLevel()
{
	// Clear the tile clones. This also clears the ones in m_obstacles.
	
	// Clear the original tiles.
	
}

void TiledLevel::Render()
{
	
}

std::vector<Tile*>& TiledLevel::GetObstacles() { return m_obstacles; }