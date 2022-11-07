#pragma once

#include "GameCamera.h"
#include "LeftWindow.h"
#include "LeftWindow_Delete.h"
#include "Player.h"
#include "SpawnManager.h"
#include "Stage.h"
#include "TurretManager.h"

/// <summary>
/// クラスの生成削除を行うクラス
/// </summary>
class Game : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

private:

	GameCamera*					m_gameCamera;
	LeftWindow*					m_leftWindow;
	LeftWindow_Delete*			m_leftWindow_Delete;
	Player*						m_player;
	SpawnManager*				m_spawnMananer;
	Stage*						m_stage;
	TurretManager*				m_turretManager;

	ModelRender					m_stageModelRender;

	float						m_ufoSpawnTimer = 0;
};