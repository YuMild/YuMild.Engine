#pragma once

#include "EnemyObject.h"
#include "TurretObject.h"

/// <summary>
/// LaserTurret
/// </summary>
class LaserTurret : public TurretObject
{
public:

	~LaserTurret();
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
	Quaternion GetModelRotation() const override
	{
		return m_modelRotation;
	}

	/// <summary>
	/// ���f�������v���ɉ�]
	/// </summary>
	void SetModelRotationTurnRight() override
	{
		m_modelRotation.AddRotationDegY(180.0f);
	}

	/// <summary>
	/// ���f���𔽎��v���ɉ�]
	/// </summary>
	void SetModelRotationTurnLeft() override
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
	bool GetAttackReady() const override
	{
		return m_moveReady;
	}

	/// <summary>
	/// �^���b�g��HP�����Z����
	/// </summary>
	/// <param name="value"></param>
	void AddTurretHP(bool value) override
	{
		m_hp += value;
		//�����葝���Ȃ��l��
		if (m_hp >= m_maxHp)
		{
			m_hp = m_maxHp;
		}
	}

	/// <summary>
	/// �^���b�g��HP�����Z����
	/// </summary>
	/// <param name="value"></param>
	void SubTurretHP(bool value) override
	{
		m_hp -= value;
		//�����葝���Ȃ��l��
		if (m_hp >= m_maxHp)
		{
			m_hp = m_maxHp;
		}
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
	void EffectPlayLaser();

	/// <summary>
	/// �e�����Đ�
	/// </summary>
	void SoundPlayFire();

	//���쏈��
	std::vector<EnemyObject*>	m_enemys;
	int							m_hp				= 0;
	int							m_maxHp				= 0;
	bool						m_moveReady			= false;
	bool						m_laserIsPlay		= true;
	float						m_debuffTimer		= 0.0f;
	float						m_fireRate			= 0.0f;
	float						m_laserAliveTimer	= 0.0f;
	Vector3						m_laserPosition		= Vector3::Zero;
	Vector3						m_forward			= Vector3::Zero;

	//���f��
	ModelRender					m_turretMR;
	ModelRender					m_baseMR;
	ModelRender					m_attackRangeMR;

	//�摜
	SpriteRender				m_spriteRender;

	//�G�t�F�N�g
	EffectEmitter*				m_laserEF			= nullptr;

	//�T�E���h
	SoundSource*				m_fireSE			= nullptr;

	//���f��
	Vector3						m_modelPosition		= Vector3::Zero;
	Quaternion					m_modelRotation		= Quaternion::Identity;
	Vector3						m_spritePosition	= Vector3::Zero;
};