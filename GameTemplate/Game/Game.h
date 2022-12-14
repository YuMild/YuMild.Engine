#pragma once

#include "Dempa.h"
#include "Energy.h"
#include "GameCamera.h"
#include "GameOver.h"
#include "LeftWindow.h"
#include "LeftWindowDelete.h"
#include "Player.h"
#include "SpawnManager.h"
#include "Stage.h"
#include "UFO.h"
#include "Title.h"
#include "TurretManager.h"

enum enGameState
{
	enGameState_Title,
	enGameState_InGame,
	enGameState_GameOver
};

/// <summary>
/// クラスの生成削除を行うクラス
/// </summary>
class Game : public IGameObject
{
public:

	Game();
	~Game();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

	/// <summary>
	/// ゲームステートを設定
	/// </summary>
	/// <param name="state"></param>
	void SetGameState(const int state)
	{
		m_state = state;
	}

	/// <summary>
	/// ゲームステートを取得
	/// </summary>
	/// <returns></returns>
	int GetGameState() const
	{
		return m_state;
	}

private:

	//クラス
	Dempa*						m_dempa;
	Energy*						m_energy;
	GameCamera*					m_gameCamera;
	GameOver*					m_gameOver;
	LeftWindow*					m_leftWindow;
	LeftWindowDelete*			m_leftWindow_Delete;
	Player*						m_player;
	SkyCube*					m_skyCube;
	SpawnManager*				m_spawnMananer;
	Stage*						m_stage;
	UFO*						m_ufo;
	Title*						m_title;
	TurretManager*				m_turretManager;

	//ステート
	int							m_state = enGameState_Title;
};