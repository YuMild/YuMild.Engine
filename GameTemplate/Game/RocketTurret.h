#pragma once

#include "TurretObject.h"

class LeftWindow;

class RocketTurret : public TurretObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

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
	Vector3 GetModelPosition() const override
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
	/// �f�o�t��ݒ�
	/// </summary>
	void SetDebuff()
	{

	}

private:

	//�N���X
	LeftWindow*		m_leftWindow;

	//���f��
	ModelRender		m_modelRender;

	//�摜
	SpriteRender	m_spriteRender;

	//���f��
	Vector3			m_modelPosition;
	Quaternion		m_modelRotation;
	Vector3			m_spritePosition;
};