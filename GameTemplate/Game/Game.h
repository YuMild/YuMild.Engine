#pragma once

#include "Energy.h"
#include "GameCamera.h"
#include "GameOver.h"
#include "LeftWindow.h"
#include "LeftWindowDelete.h"
#include "Missile.h"
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

enum enEffectNumber
{
	enEffectNumber_Explosion,
	enEffectNumber_CursorAfter,
	enEffectNumber_Smoke,
	enEffectNumber_NormalTurret,
	enEffectNumber_DualGunTurret,
	enEffectNumber_LaserTurret,
	enEffectNumber_TeslaTurret,
	enEffectNumber_HolyTurret
};

enum enSoundNumber
{
	enSoundNumber_NormalBGM,
	enSoundNumber_Alarm,
	enSoundNumber_BossBGM,
	enSoundNumber_Window,
	enSoundNumber_Choice,
	enSoundNumber_CursorAfter,
	enSoundNumber_Explosion,
	enSoundNumber_NotEnoughCost,
	enSoundNumber_SetTurret,
	enSoundNumber_NormalTurret,
	enSoundNumber_DualGunTurret,
	enSoundNumber_LaserTurret,
	enSoundNumber_TeslaTurret,
	enSoundNumber_HolyTurret
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

	/// <summary>
	/// エフェクトを登録
	/// </summary>
	void InitEffect();

	/// <summary>
	/// サウンドを登録
	/// </summary>
	void InitSound();

	//クラス
	Missile*					m_missile				= nullptr;
	Energy*						m_energy				= nullptr;
	GameCamera*					m_gameCamera			= nullptr;
	GameOver*					m_gameOver				= nullptr;
	LeftWindow*					m_leftWindow			= nullptr;
	LeftWindowDelete*			m_leftWindow_Delete		= nullptr;
	Player*						m_player				= nullptr;
	SkyCube*					m_skyCube				= nullptr;
	SpawnManager*				m_spawnMananer			= nullptr;
	Stage*						m_stage					= nullptr;
	UFO*						m_ufo					= nullptr;
	Title*						m_title					= nullptr;
	TurretManager*				m_turretManager			= nullptr;

	//ステート
	int							m_state					= enGameState_Title;
};