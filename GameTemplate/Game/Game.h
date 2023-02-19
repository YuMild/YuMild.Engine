#pragma once

#include "Container.h"
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
	enGameState_Container,
	enGameState_InGame,
	enGameState_GameOver
};

enum enEffectNumber
{
	enEffectNumber_Barrier,
	enEffectNumber_Energy,
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
	enSoundNumber_ContainerDoor,
	enSoundNumber_ContainerShipMove,
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
/// �N���X�̐����폜���s���N���X
/// </summary>
class Game : public IGameObject
{
public:

	Game();
	~Game();
	bool Start()override;
	void Update()override;

	/// <summary>
	/// �Q�[���X�e�[�g��ݒ�
	/// </summary>
	/// <param name="state"></param>
	const void SetGameState(const int state)
	{
		m_state = state;
	}

	/// <summary>
	/// �Q�[���X�e�[�g���擾
	/// </summary>
	/// <returns></returns>
	const int& GetGameState() const
	{
		return m_state;
	}

private:

	/// <summary>
	/// ������Ǘ�
	/// </summary>
	void Move();

	/// <summary>
	/// �R���e�i�X�e�[�g�̎���NewGO
	/// </summary>
	void ContainerNewGO();

	/// <summary>
	/// �C���Q�[���X�e�[�g�̎���NewGO
	/// </summary>
	void InGameNewGO();

	/// <summary>
	/// �G�t�F�N�g��o�^
	/// </summary>
	void InitEffect();

	/// <summary>
	/// �T�E���h��o�^
	/// </summary>
	void InitSound();

	//�N���X
	Container*					m_container				= nullptr;
	Energy*						m_energy				= nullptr;
	GameCamera*					m_gameCamera			= nullptr;
	GameOver*					m_gameOver				= nullptr;
	Missile*					m_missile				= nullptr;
	LeftWindow*					m_leftWindow			= nullptr;
	LeftWindowDelete*			m_leftWindow_Delete		= nullptr;
	Player*						m_player				= nullptr;
	SkyCube*					m_skyCube				= nullptr;
	SpawnManager*				m_spawnMananer			= nullptr;
	Stage*						m_stage					= nullptr;
	UFO*						m_ufo					= nullptr;
	Title*						m_title					= nullptr;
	TurretManager*				m_turretManager			= nullptr;

	//�X�e�[�g
	int							m_state					= enGameState_Title;
	int							m_isContainerNewGO		= true;
	int							m_isInGameNewGO			= true;
};