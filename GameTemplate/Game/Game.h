#pragma once

#include "Energy.h"
#include "GameCamera.h"
#include "GameOver.h"
#include "LeftWindow.h"
#include "Player.h"
#include "SpawnManager.h"
#include "Stage.h"
#include "TurretManager.h"

/// <summary>
/// �N���X�̐����폜���s���N���X
/// </summary>
class Game : public IGameObject
{
public:

private:

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

	Energy*						m_energy;
	GameCamera*					m_gameCamera;
	GameOver*					m_gameOver;
	LeftWindow*					m_leftWindow;
	Player*						m_player;
	SkyCube*					m_skyCube;
	SpawnManager*				m_spawnMananer;
	Stage*						m_stage;
	TurretManager*				m_turretManager;

	Quaternion					m_skyCubeRotation = g_quatIdentity;
};