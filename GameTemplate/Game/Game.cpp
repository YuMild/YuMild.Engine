#include "stdafx.h"
#include "Game.h"

namespace
{
	float SKYCUBE_SCALE = 3000.0f;
}

Game::Game()
{

}

Game::~Game()
{
	const auto& ufos = FindGOs<EnemyObject>("ufo");
	int ufoSize = ufos.size();
	for (int i = 0; i < ufoSize; i++)
	{
		DeleteGO(ufos[i]);
	}
	const auto& dempas = FindGOs<EnemyObject>("dempa");
	int dempaSize = dempas.size();
	for (int i = 0; i < dempaSize; i++)
	{
		DeleteGO(dempas[i]);
	}
	const auto& turrets = FindGOs<TurretObject>("turret");
	int turretSize = turrets.size();
	for (int i = 0; i < turretSize; i++)
	{
		DeleteGO(turrets[i]);
	}
	const auto& leftWindowDeletes = FindGOs<LeftWindowDelete>("leftWindowDelete");
	int leftWindowDeleteSize = leftWindowDeletes.size();
	for (int i = 0; i < turretSize; i++)
	{
		DeleteGO(leftWindowDeletes[i]);
	}
	DeleteGO(m_energy);
	DeleteGO(m_gameCamera);
	DeleteGO(m_gameOver);
	DeleteGO(m_leftWindow);
	DeleteGO(m_player);
	DeleteGO(m_skyCube);
	DeleteGO(m_spawnMananer);
	DeleteGO(m_stage);
	DeleteGO(m_turretManager);
}

bool Game::Start()
{
	m_energy = NewGO<Energy>(0, "energy");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_gameOver = NewGO<GameOver>(0, "gameOver");
	m_leftWindow = NewGO<LeftWindow>(0, "leftWindow");
	m_player = NewGO<Player>(0, "payer");
	m_skyCube = NewGO<SkyCube>(0, "skyCube");
	m_spawnMananer = NewGO<SpawnManager>(0, "spawnManager");
	m_stage = NewGO<Stage>(0, "stage");
	m_turretManager = NewGO<TurretManager>(0, "turretManager");

	m_skyCube->SetScale({ SKYCUBE_SCALE, SKYCUBE_SCALE, SKYCUBE_SCALE });
	m_skyCube->SetType(enSkyCubeType_Night);
	m_skyCube->SetLuminance(0.75f);

	return true;
}

void Game::Update()
{
	if (m_state == enGameState_GameOver&&g_pad[0]->IsTrigger(enButtonA))
	{
		m_title = NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}

void Game::Render(RenderContext& renderContext)
{

}