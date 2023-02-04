#pragma once

#include "UFO.h"
#include "Missile.h"
#include "Game.h"
#include "SpaceShip.h"

class Game;

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
	/// Missile�̃f�t�H���gHP��ݒ�
	/// </summary>
	/// <returns></returns>
	float GetDefaultHP_Missile()
	{
		return m_defaultHP_Missile;
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
	void EffectPlayExplosion(Vector3& position);

	/// <summary>
	/// ���j�������Đ�
	/// </summary>
	void SoundPlayExplosion();

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
	/// Missile�̃X�|�[�����Ǘ�
	/// </summary>
	void SpawnMissile();

	/// <summary>
	/// SpaceShip�̃X�|�[�����Ǘ�
	/// </summary>
	void SpawnSpaceShip();

	/// <summary>
	/// �{�X�o�����̉������Đ�
	/// </summary>
	void SoundPlayBossSpawn();

	//�N���X
	Missile*		m_missile;
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

	//Missile
	float			m_spawnTime_Missile = 0.0f;
	float			m_spawnTimer_Missile = 0.0f;
	float			m_defaultHP_Missile = 0.0f;

	//SpaceShip
	float			m_spawnTime_SpaceShip = 0.0f;
	float			m_spawnTimer_SpaceShip = 0.0f;
	float			m_defaultHP_SpaceShip = 0.0f;
};