#include "stdafx.h"
#include "Game.h"

bool Game::Start()
{
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_leftWindow = NewGO<LeftWindow>(0, "leftWindow");
	m_player = NewGO<Player>(0, "payer");
	m_spawnMananer = NewGO<SpawnManager>(0, "spawnManager");
	m_stage = NewGO<Stage>(0, "stage");
	m_turretManager = NewGO<TurretManager>(0, "turretManager");

	return true;
}

void Game::Update()
{

}

void Game::Render(RenderContext& renderContext)
{

}