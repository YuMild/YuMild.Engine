#pragma once

#include "EnemyObject.h"
#include "TurretObject.h"

class EnemyObject;

class DualGunTurret : public TurretObject
{
public:

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

	/// <summary>
	/// ���f���̃|�W�V������ݒ�
	/// </summary>
	/// <param name="position"></param>
	/// <returns></returns>
	void SetModelPosition(const Vector3& position)
	{
		m_modelPosition = position;
	}

	/// <summary>
	/// ���f���̃|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetModelPosition() const
	{
		return m_modelPosition;
	}

	/// <summary>
	/// �摜�̃|�W�V������ݒ�
	/// </summary>
	/// <param name="position"></param>
	void SetSpritePosition(const Vector3& position)
	{
		m_spritePosition = position;
	}

	/// <summary>
	/// �摜�̃|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetSpritePosition() const
	{
		return m_spritePosition;
	}

	/// <summary>
	/// �^���b�g�̏�ԕύX
	/// </summary>
	/// <param name="ready"></param>
	void SetAttackReady(bool ready)
	{
		m_moveReady = ready;
	}

private:

	/// <summary>
	/// �G�t�F�N�g���Đ�
	/// </summary>
	/// <param name="position"></param>
	void EffectPlayHit(const Vector3& position)
	{
		m_hitEF = NewGO<EffectEmitter>(0);
		m_hitEF->Init(2);
		m_hitEF->SetPosition({ position.x,position.y + 200.0f,position.z + 300.0f });
		m_hitEF->SetScale(Vector3::One * 150.0f);
		m_hitEF->Play();
	}

	/// <summary>
	/// �e�����Đ�
	/// </summary>
	void SoundPlayFire()
	{
		m_fireSE = NewGO<SoundSource>(0);
		m_fireSE->Init(6);
		m_fireSE->SetVolume(0.025f);
		m_fireSE->Play(false);
	}

	/// <summary>
	/// �U������
	/// </summary>
	void Move();

	//�U������
	bool							m_moveReady = false;
	std::vector<EnemyObject*>		m_enemys;
	Vector3							m_difference;
	Vector3							m_lockOnPosition;
	float							m_fireRate = 0.0f;
	EffectEmitter*					m_hitEF;
	SoundSource*					m_fireSE;

	//���f��
	ModelRender						m_turretModel;
	ModelRender						m_baseModel;

	//���f��
	Vector3							m_modelPosition;
	Vector3							m_spritePosition;
};