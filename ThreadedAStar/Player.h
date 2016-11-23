#pragma once

#include "BasicTypes.h"
#include "Tile.h"


class Player
{
private:
	Point2D m_centre;
	Colour m_colour;
	Tile* m_currentTile;
	bool m_isAligned;
	int m_mapPosX;
	int m_mapPosY;
	int m_radius;

	virtual void initializeColour();

public:
	Player();
	Player(Tile* tile);
	void update(unsigned int dt);
	void render(Renderer* renderer) const;
	void setCurrentTile(Tile* tile);
};