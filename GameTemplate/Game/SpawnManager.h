#pragma once

#include "UFO.h"

/// <summary>
/// �G�̃X�|�[�����Ǘ�����N���X
/// </summary>
class SpawnManager : public IGameObject
{
public:

	/// <summary>
	/// UFO�̃f�t�H���gHP��ݒ�
	/// </summary>
	/// <returns></returns>
	float GetDefaultHP_UFO()
	{
		return m_defaultHP_UFO;
	}

	//���j�G�t�F�N�g���Đ�
	void EffectPlayExplosion(Vector3& position)
	{
		m_explosionEF = NewGO<EffectEmitter>(0);
		m_explosionEF->Init(1);
		m_explosionEF->SetPosition(position);
		m_explosionEF->SetScale(Vector3::One * 50.0f);
		m_explosionEF->Play();
	}

	//���j�������Đ�
	void SoundPlayExplosion()
	{
		m_explosionSE = NewGO<SoundSource>(5);
		m_explosionSE->Init(5);
		m_explosionSE->SetVolume(0.05f);
		m_explosionSE->Play(false);
	}

private:

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

	/// <summary>
	/// ���x���A�b�v
	/// </summary>
	void LevelUp();

	/// <summary>
	/// UFO�̃X�|�[�����Ǘ�
	/// </summary>
	void SpawnUFO();

	//�N���X
	UFO*			m_ufo;

	//�j�󎞂̃G�t�F�N�g
	EffectEmitter*	m_explosionEF;

	//�j�󎞂̉���
	SoundSource*	m_explosionSE;

	//���x�����Ǘ�����^�C�}�[
	float			m_levelTimer = 0.0f;

	//UFO�̃X�|�[���^�C�}�[
	float			m_spawnTime_UFO = 0.0f;
	float			m_spawnTimer_UFO = 0.0f;

	//UFO��HP
	float			m_defaultHP_UFO = 0.0f;
};