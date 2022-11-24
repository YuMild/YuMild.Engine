#pragma once

#include <EnemyObject.h>

class Energy;
class LeftWindow;
class TurretManager;

class GenerationTurret : public IGameObject
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
	/// ���f���̉�]��ݒ�
	/// </summary>
	/// <param name="rotation"></param>
	/// <returns></returns>
	void SetModelRotation(const float rotation)
	{
		m_modelRotation.AddRotationDegY(rotation);
	}

	/// <summary>
	/// ���f���̉�]���擾
	/// </summary>
	/// <returns></returns>
	Quaternion GetModelRotation()
	{
		return m_modelRotation;
	}

	/// <summary>
	/// ���f�������v���ɉ�]
	/// </summary>
	/// <param name="rotation"></param>
	/// <returns></returns>
	void ModelRotationTurnRight()
	{
		m_modelRotation.AddRotationDegY(180.0f);
	}

	/// <summary>
	/// ���f���𔽎��v���ɉ�]
	/// </summary>
	/// <param name="rotation"></param>
	/// <returns></returns>
	void ModelRotationTurnLeft()
	{
		m_modelRotation.AddRotationDegY(-180.0f);
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
	/// �U������
	/// </summary>
	void Move();

	//�^���b�g�}�l�[�W���[
	TurretManager*					m_turretManager;

	//�U������
	bool							m_moveReady = false;
	bool							m_addGenerationTurret = false;

	//�N���X
	Energy*							m_energy;
	LeftWindow*						m_leftWindow;

	//���f��
	ModelRender						m_turretBaseModel;
	ModelRender						m_turretModel;
	ModelRender						m_baseModel;

	//���f��
	Vector3							m_modelPosition;
	Quaternion						m_modelRotation;
	Vector3							m_spritePosition;
};