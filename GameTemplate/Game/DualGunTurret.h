#pragma once

#include <EnemyObject.h>

class EnemyObject;
class LeftWindow;
class TurretManager;

class DualGunTurret : public IGameObject
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
		m_attackReady = ready;
	}

private:

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
	void Attack();

	//�^���b�g�}�l�[�W���[
	TurretManager*					m_turretManager;

	//�U������
	bool							m_attackReady = false;
	std::vector<EnemyObject*>		m_enemys;
	Vector3							m_difference;
	Vector3							m_lockOnPosition;
	float							m_fireRate = 0.0f;
	SoundSource*					m_fireSE;
	
	//�N���X
	LeftWindow*						m_leftWindow;

	//���f��
	ModelRender						m_turretModel;
	ModelRender						m_baseModel;

	//���f��
	Vector3							m_modelPosition;
	Quaternion						m_modelRotation;
	Vector3							m_spritePosition;
};