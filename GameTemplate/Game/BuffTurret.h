#pragma once

#include "TurretObject.h"

class Energy;
class LeftWindow;
class TurretManager;

/// <summary>
/// BuffTurret
/// </summary>
class BuffTurret : public TurretObject
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

	//�^���b�g�}�l�[�W���[
	TurretManager* m_turretManager;

	//�U������
	bool							m_moveReady = false;
	float							m_debuffTimer = 0.0f;
	bool							m_addGenerationTurret = false;

	//�N���X
	Energy*							m_energy;
	LeftWindow*						m_leftWindow;

	//���f��
	ModelRender						m_turretBaseMR;
	ModelRender						m_turretMR;
	ModelRender						m_baseMR;

	//���f��
	Vector3							m_modelPosition;
	Quaternion						m_modelRotation;
	Vector3							m_spritePosition;
};