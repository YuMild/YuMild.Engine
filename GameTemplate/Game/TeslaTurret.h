#pragma once

#include "EnemyObject.h"
#include "TurretObject.h"

class EnemyObject;

/// <summary>
/// TeslaTurret
/// </summary>
class TeslaTurret : public TurretObject
{
public:

	bool Start() override;
	void Update() override;
	void Render(RenderContext& renderContext) override;

	/// <summary>
	/// ���f���̃|�W�V������ݒ�
	/// </summary>
	/// <param name="position"></param>
	void SetModelPosition(const Vector3& position) override
	{
		m_modelPosition = position;
	}

	/// <summary>
	/// �|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetModelPosition() const override
	{
		return m_modelPosition;
	}

	/// <summary>
	/// �摜�̃|�W�V������ݒ�
	/// </summary>
	/// <param name="position"></param>
	void SetSpritePosition(const Vector3& position) override
	{
		m_spritePosition = position;
	}

	/// <summary>
	/// �摜�̃|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetSpritePosition() const override
	{
		return m_spritePosition;
	}

	/// <summary>
	/// ���f���̉�]��ݒ�
	/// </summary>
	/// <param name="rotation"></param>
	void SetModelRotation(const float rotation) override
	{
		m_modelRotation.AddRotationDegY(rotation);
	}

	/// <summary>
	/// ���f���̉�]���擾
	/// </summary>
	/// <returns></returns>
	Quaternion GetModelRotation() override
	{
		return m_modelRotation;
	}

	/// <summary>
	/// ���f�������v���ɉ�]
	/// </summary>
	void ModelRotationTurnRight() override
	{
		m_modelRotation.AddRotationDegY(180.0f);
	}

	/// <summary>
	/// ���f���𔽎��v���ɉ�]
	/// </summary>
	void ModelRotationTurnLeft() override
	{
		m_modelRotation.AddRotationDegY(-180.0f);
	}

	/// <summary>
	/// �^���b�g�̏�Ԃ�ݒ�
	/// </summary>
	void SetAttackReady(bool ready) override
	{
		m_moveReady = ready;
	}

	/// <summary>
	/// �^���b�g�̏�Ԃ��擾
	/// </summary>
	/// <returns></returns>
	bool GetAttackReady()
	{
		return m_moveReady;
	}

	/// <summary>
	/// �f�o�t��ݒ�
	/// </summary>
	void SetDebuff() override
	{
		m_debuffTimer = 5.0f;
	}

private:

	/// <summary>
	/// �U������
	/// </summary>
	void Move();

	/// <summary>
	/// �G�t�F�N�g���Đ�
	/// </summary>
	/// <param name="position"></param>
	void EffectPlayHit(const Vector3& position)
	{
		m_hitEF = NewGO<EffectEmitter>(0);
		m_hitEF->Init(7);
		m_hitEF->SetPosition({ position.x,position.y + 200.0f,position.z + 300.0f });
		m_hitEF->SetScale(Vector3::One * 30.0f);
		m_hitEF->Play();
	}

	/// <summary>
	/// �e�����Đ�
	/// </summary>
	void SoundPlayFire()
	{
		m_fireSE = NewGO<SoundSource>(0);
		m_fireSE->Init(12);
		m_fireSE->SetVolume(0.025f);
		m_fireSE->Play(false);
	}

	//�U������
	std::vector<EnemyObject*>		m_enemys;
	bool							m_moveReady = false;
	float							m_debuffTimer = 0.0f;
	float							m_fireRate = 0.0f;
	Vector3							m_difference;
	Vector3							m_lockOnPosition;

	//�G�t�F�N�g
	EffectEmitter*					m_hitEF;

	//�T�E���h
	SoundSource*					m_fireSE;

	//���f��
	ModelRender						m_turretMR;
	ModelRender						m_baseMR;
	ModelRender						m_attackRangeMR;

	//���f��
	Vector3							m_modelPosition;
	Quaternion						m_modelRotation;
	Vector3							m_spritePosition;
};