#pragma once

#include "EnemyObject.h"
#include "TurretObject.h"

/// <summary>
/// HolyTurret
/// </summary>
class HolyTurret : public TurretObject
{
public:

	~HolyTurret();
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
	void EffectPlayHoly(const Vector3& position);

	/// <summary>
	/// �e�����Đ�
	/// </summary>
	void SoundPlayHoly();

	//�U������
	std::vector<EnemyObject*>		m_enemys;
	bool							m_moveReady = false;
	float							m_debuffTimer = 0.0f;
	float							m_fireRate = 0.0f;

	//�G�t�F�N�g
	EffectEmitter*					m_holyEF;
	Quaternion						m_effectRotation;

	//�T�E���h
	SoundSource*					m_holySE;

	//���f��
	ModelRender						m_turret_BaseMR;
	ModelRender						m_turret_HourHandMR;
	ModelRender						m_turret_MiniteHandMR;
	ModelRender						m_baseMR;

	//���f��
	Vector3							m_modelPosition;
	Quaternion						m_modelRotation;
	Quaternion						m_model_HourHandRotation;
	Quaternion						m_model_MiniteHandRotation;
	Vector3							m_spritePosition;
};