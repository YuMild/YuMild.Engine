#pragma once

#include "GameCamera.h"
#include "Player.h"
#include "SpawnManager.h"
#include "Stage.h"

class Game : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

private:

	GameCamera*					m_gameCamera;
	Player*						m_player;
	SpawnManager*				m_spawnMananer;
	Stage*						m_stage;

	ModelRender					m_stageModelRender;

	float						m_ufoSpawnTimer = 0;
};