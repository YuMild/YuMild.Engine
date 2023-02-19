#pragma once

#include "EnemyObject.h"
#include "TurretObject.h"

/// <summary>
/// NormalTurret
/// </summary>
class NormalTurret final : public TurretObject
{
public:

	~NormalTurret();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& renderContext) override;

	/// <summary>
	/// ���f���̃|�W�V������ݒ�
	/// </summary>
	/// <param name="position"></param>
	const void SetModelPosition(const Vector3 position) override
	{
		m_modelPosition = position;
	}

	/// <summary>
	/// �|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetModelPosition() const override
	{
		return m_modelPosition;
	}

	/// <summary>
	/// �摜�̃|�W�V������ݒ�
	/// </summary>
	/// <param name="position"></param>
	const void SetSpritePosition(const Vector3 position) override
	{
		m_spritePosition = position;
	}

	/// <summary>
	/// �摜�̃|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetSpritePosition() const override
	{
		return m_spritePosition;
	}

	/// <summary>
	/// ���f���̉�]��ݒ�
	/// </summary>
	/// <param name="rotation"></param>
	const void SetModelRotation(const float rotation) override
	{
		m_modelRotation.AddRotationDegY(rotation);
	}

	/// <summary>
	/// ���f���̉�]���擾
	/// </summary>
	/// <returns></returns>
	const Quaternion& GetModelRotation() const override
	{
		return m_modelRotation;
	}

	/// <summary>
	/// ���f�������v���ɉ�]
	/// </summary>
	const void SetModelRotationTurnRight() override
	{
		m_modelRotation.AddRotationDegY(180.0f);
	}

	/// <summary>
	/// ���f���𔽎��v���ɉ�]
	/// </summary>
	const void SetModelRotationTurnLeft() override
	{
		m_modelRotation.AddRotationDegY(-180.0f);
	}

	/// <summary>
	/// �^���b�g�̍U���Ԑ���ݒ�
	/// </summary>
	const void SetAttackReady(bool ready) override
	{
		m_moveReady = ready;
	}

	/// <summary>
	/// �^���b�g�̍U���Ԑ����擾
	/// </summary>
	/// <returns></returns>
	const bool& GetAttackReady() const override
	{
		return m_moveReady;
	}

	/// <summary>
	/// �^���b�g�̏�Ԃ��擾
	/// </summary>
	/// <returns></returns>
	const bool& GetAlive() const override
	{
		return m_alive;
	}

	/// <summary>
	/// �^���b�g��HP�����Z����
	/// </summary>
	/// <param name="value"></param>
	const void AddTurretHP(float value) override
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
	const void SubTurretHP(float value) override
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
	const void SetDebuff() override
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

	/// <summary>
	/// �G�t�F�N�g���Đ�
	/// </summary>
	/// <param name="position"></param>
	void EffectPlayHit(const Vector3& position);

	/// <summary>
	/// �e�����Đ�
	/// </summary>
	void SoundPlayFire();

	//���쏈��
	std::vector<EnemyObject*>	m_enemys;
	bool						m_alive				= true;
	bool						m_moveReady			= false;
	float						m_debuffTimer		= 0.0f;
	float						m_fireRate			= 0.0f;
	Vector3						m_difference		= Vector3::Zero;
	Vector3						m_lockOnPosition	= Vector3::Zero;
	//���R�C��
	Vector3						m_recoilPosition	= Vector3::Zero;
	Vector3						m_recoilMoveSpeed	= Vector3::Zero;

	//�G�t�F�N�g
	EffectEmitter*				m_smokeEF			= nullptr;
	EffectEmitter*				m_hitEF				= nullptr;

	//�T�E���h
	SoundSource*				m_fireSE			= nullptr;

	//���f��
	ModelRender					m_turretMR;
	ModelRender					m_turretBaseMR;
	ModelRender					m_baseMR;
	ModelRender					m_base2MR;
	Texture						m_emissionMap;
	ModelRender					m_attackRangeMR;

	//HP
	SpriteRender				m_hpBarSR;
	float						m_hp				= 0.0f;
	float						m_maxHp				= 0.0f;
	Vector2						m_hpBarPosition		= Vector2::Zero;

	//���f��
	Vector3						m_modelPosition		= Vector3::Zero;
	Quaternion					m_modelRotation		= Quaternion::Identity;
	Vector3						m_spritePosition	= Vector3::Zero;
};