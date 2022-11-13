#pragma once

#include "UFO.h"

/// <summary>
/// �G�I�u�W�F�N�g�̃X�|�[�����Ǘ�����N���X
/// </summary>
class SpawnManager : public IGameObject
{
public:

	//���j�G�t�F�N�g���Đ�
	void EffectPlayExplosion()
	{
		m_explosionEF = NewGO<EffectEmitter>(1);
		m_explosionEF->Init(1);
		m_explosionEF->SetPosition({ 0.0f,0.0f,0.0f });
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

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

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

	//UFO�̃X�|�[���^�C�}�[
	float			m_spawnTimer_UFO = 0.0f;
};