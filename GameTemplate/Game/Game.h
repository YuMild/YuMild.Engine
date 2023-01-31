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

/// <summary>
/// �N���X�̐����폜���s���N���X
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
	/// �Q�[���X�e�[�g��ݒ�
	/// </summary>
	/// <param name="state"></param>
	void SetGameState(const int state)
	{
		m_state = state;
	}

	/// <summary>
	/// �Q�[���X�e�[�g���擾
	/// </summary>
	/// <returns></returns>
	int GetGameState() const
	{
		return m_state;
	}

private:

	//�N���X
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

	//�X�e�[�g
	int							m_state = enGameState_Title;
};