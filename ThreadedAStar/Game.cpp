#include "Game.h"
#include <time.h>
#include <algorithm>


Game::Game() :
	m_pathGenerator(PathGenerator()),
	m_player(Player()),
	m_running(true)
{ 
	srand(time(NULL));
	m_renderer = Renderer(m_settings.windowSize, "Astar");
	m_tileMap = TileMap(m_settings.mapSize);

	cout << "WORKING!" << endl;
}

Game::~Game() { }



void Game::initialize()
{
	m_prevTime = LTimer::gameTime();
	m_running = m_renderer.initialize();
	//unsigned int totalTime;

	if (m_running)
	{
		m_tileMap.initializeZones(m_settings.playerZoneAsPercentage, m_settings.npcZoneAsPercentage);
		m_tileMap.initializeWalls(m_settings.wallsAsPercentage);
		m_tileMap.initializeTiles(m_settings.windowSize);
		m_pathGenerator.setTileMap(&m_tileMap);
		initializeNPCs();
		/*unsigned int previousTime = LTimer::gameTime();
		m_pathGenerator.generatePath(m_tileMap.getTile(0, 0), m_tileMap.getTile(999, 999));
		unsigned int afterTime = LTimer::gameTime();
		unsigned int totalTime = afterTime - previousTime;
		cout << totalTime << " ticks" << endl;*/
		m_pathGenerator.generatePath(m_tileMap.getRandomTileOfType(TileTypes::FLOOR), m_tileMap.getRandomTileOfType(TileTypes::FLOOR));
	}
}

void Game::initializeNPCs()
{
	vector<Tile*> startingTiles;

	for (int i = 0; i < m_settings.numNPCs; i++)
	{
		Tile* tile;

		do
		{
			tile = m_tileMap.getRandomTileOfType(TileTypes::NPCZONE);
		} while (find(startingTiles.begin(), startingTiles.end(), tile) != startingTiles.end());

		startingTiles.push_back(tile);
		m_NPCs.push_back(NPC(tile));
	}
}



void Game::loop()
{
	while (m_running)
	{
		unsigned int currentTime = LTimer::gameTime();
		unsigned int deltaTime = currentTime - m_prevTime;
		m_prevTime = currentTime;

		update(deltaTime);
		render(&m_renderer);
	}
}

void Game::update(unsigned int dt)
{
	m_tileMap.update(dt);
	updateNPCs(dt);
}

void Game::updateNPCs(unsigned int dt)
{
	const int npcCount = m_NPCs.size();

	for (int i = 0; i < npcCount; i++)
	{
		m_NPCs[i].update(dt);
	}
}



void Game::render(Renderer* renderer) const
{
	renderer->clear(Colour(160, 150, 235));
	m_tileMap.render(renderer);
	renderNPCs(renderer);
	renderer->present();
}

void Game::renderNPCs(Renderer* renderer) const
{
	const int npcCount = m_NPCs.size();

	for (int i = 0; i < npcCount; i++)
	{
		m_NPCs[i].render(renderer);
	}
}