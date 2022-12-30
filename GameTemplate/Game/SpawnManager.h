#pragma once

#include "UFO.h"
#include "Dempa.h"
#include "SpaceShip.h"

/// <summary>
/// �G�̃X�|�[�����Ǘ�����N���X
/// </summary>
class SpawnManager : public IGameObject
{
public:

	~SpawnManager();
	bool Start()override;
	void Update()override;
	void UpdateOnStop()override;
	void Render(RenderContext& renderContext)override;

	/// <summary>
	/// UFO�̃f�t�H���gHP��ݒ�
	/// </summary>
	/// <returns></returns>
	float GetDefaultHP_UFO()
	{
		return m_defaultHP_UFO;
	}

	/// <summary>
	/// Dempa�̃f�t�H���gHP��ݒ�
	/// </summary>
	/// <returns></returns>
	float GetDefaultHP_Dempa()
	{
		return m_defaultHP_Dempa;
	}

	/// <summary>
	/// SpaceShip�̃f�t�H���gHP��ݒ�
	/// </summary>
	/// <returns></returns>
	float GetDefaultHP_SpaceShip()
	{
		return m_defaultHP_SpaceShip;
	}

	/// <summary>
	/// ���j�G�t�F�N�g���Đ�
	/// </summary>
	/// <param name="position"></param>
	void EffectPlayExplosion(Vector3& position)
	{
		m_explosionEF = NewGO<EffectEmitter>(0);
		m_explosionEF->Init(1);
		m_explosionEF->SetPosition({ position.x,position.y + 200.0f,position.z });
		m_explosionEF->SetScale(Vector3::One * 100.0f);
		m_explosionEF->Play();
	}

	/// <summary>
	/// ���j�������Đ�
	/// </summary>
	void SoundPlayExplosion()
	{
		m_explosionSE = NewGO<SoundSource>(5);
		m_explosionSE->Init(5);
		m_explosionSE->SetVolume(0.05f);
		m_explosionSE->Play(false);
	}

private:

	/// <summary>
	/// ���x���A�b�v
	/// </summary>
	void LevelUp();

	/// <summary>
	/// UFO�̃X�|�[�����Ǘ�
	/// </summary>
	void SpawnUFO();

	/// <summary>
	/// Dempa�̃X�|�[�����Ǘ�
	/// </summary>
	void SpawnDempa();

	/// <summary>
	/// SpaceShip�̃X�|�[�����Ǘ�
	/// </summary>
	void SpawnSpaceShip();

	/// <summary>
	/// �{�X�o�����̉������Đ�
	/// </summary>
	void SoundPlayBossSpawn()
	{
		m_bossSpawnSE = NewGO<SoundSource>(0);
		m_bossSpawnSE->Init(12);
		m_bossSpawnSE->SetVolume(0.05f);
		m_bossSpawnSE->Play(false);
	}

	//�N���X
	Dempa*			m_dempa;
	UFO*			m_ufo;
	SpaceShip*		m_spaceShip;

	//�G�t�F�N�g
	EffectEmitter*	m_explosionEF;

	//����
	SoundSource*	m_explosionSE;
	SoundSource*	m_bossSpawnSE;;

	//�摜
	SpriteRender	m_warningSR;
	SpriteRender	m_warningRightCircleSR;
	SpriteRender	m_warningLeftCircleSR;

	//�A�b�v�f�[�g���~�߂Ă��邩�ۂ�
	bool			m_isStop = false;

	//Warning���Ǘ�����
	bool			m_fade = true;
	float			m_warningTimer = 0.0f;
	float			m_stopTimer = 0.0f;
	Quaternion		m_warningRightCircle_Rotation;
	Quaternion		m_warningLeftCircle_Rotation;
	float			m_warningRightCircle_RotationNumber = 0.0f;
	float			m_warningLeftCircle_RotationNumber = 0.0f;

	//���x�����Ǘ�����^�C�}�[
	float			m_levelTimer = 0.0f;

	//UFO
	float			m_spawnTime_UFO = 0.0f;
	float			m_spawnTimer_UFO = 0.0f;
	float			m_defaultHP_UFO = 0.0f;

	//Dempa
	float			m_spawnTime_Dempa = 0.0f;
	float			m_spawnTimer_Dempa = 0.0f;
	float			m_defaultHP_Dempa = 0.0f;

	//SpaceShip
	float			m_spawnTime_SpaceShip = 0.0f;
	float			m_spawnTimer_SpaceShip = 0.0f;
	float			m_defaultHP_SpaceShip = 0.0f;
};