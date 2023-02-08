#pragma once

#include "TurretObject.h"

class Energy;

/// <summary>
/// GeneratorTurret
/// </summary>
class GeneratorTurret : public TurretObject
{
public:

	~GeneratorTurret();
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
	/// �^���b�g�̏�Ԃ��擾
	/// </summary>
	/// <returns></returns>
	virtual bool GetAlive() const override
	{
		return m_alive;
	}

	/// <summary>
	/// �^���b�g��HP�����Z����
	/// </summary>
	/// <param name="value"></param>
	void AddTurretHP(float value) override
	{
		m_hp += value;
		//�����葝���Ȃ��l��
		if (m_hp >= m_maxHp)
		{
			m_hp = m_maxHp;
		}
		//0��茸��Ȃ��l��
		else if (m_hp <= 0)
		{
			m_hp = 0;
		}
	}

	/// <summary>
	/// �^���b�g��HP�����Z����
	/// </summary>
	/// <param name="value"></param>
	void SubTurretHP(float value) override
	{
		m_hp -= value;
		//�����葝���Ȃ��l��
		if (m_hp >= m_maxHp)
		{
			m_hp = m_maxHp;
		}
		//0��茸��Ȃ��l��
		else if (m_hp <= 0)
		{
			m_hp = 0;
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
	/// HP���Ǘ�
	/// </summary>
	void HP();

	/// <summary>
	/// �G�t�F�N�g���Đ�
	/// </summary>
	/// <param name="position"></param>
	void EffectPlaySmoke(const Vector3& position);

	//���쏈��
	bool						m_alive					= true;
	bool						m_moveReady				= false;
	bool						m_addGeneratorTurret	= false;
	float						m_debuffTimer			= 0.0f;

	//�N���X
	Energy*						m_energy				= nullptr;

	//�G�t�F�N�g
	EffectEmitter*				m_smokeEF				= nullptr;

	//���f��
	ModelRender					m_turretMR;
	ModelRender					m_baseMR;
	ModelRender					m_base2MR;
	Texture						m_emissionMap;

	//HP
	SpriteRender				m_hpBarSR;
	float						m_hp					= 0.0f;
	float						m_maxHp					= 0.0f;
	Vector2						m_hpBarPosition			= Vector2::Zero;

	//���f��
	Vector3						m_modelPosition			= Vector3::Zero;
	Quaternion					m_modelRotation			= Quaternion::Identity;
	Vector3						m_spritePosition		= Vector3::Zero;
};