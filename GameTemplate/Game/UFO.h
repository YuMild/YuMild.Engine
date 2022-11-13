#pragma once

#include "EnemyObject.h"

class SpawnManager;

/// <summary>
/// UFO
/// </summary>
class UFO : public EnemyObject
{
public:

	UFO();
	~UFO();
	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

	/// <summary>
	/// �|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition() const override
	{
		return m_position;
	}

private:

	/// <summary>
	/// ������Ǘ�
	/// </summary>
	void Move();

	//�N���X
	SpawnManager*			m_spawnManager;

	//���f��
	ModelRender				m_modelRender;

	//UFO
	Vector3					m_position;
	Quaternion				m_rotation;

	//�p�X�ړ�
	std::vector<Vector3>	m_pointList;
	Vector3					m_target;
	int						m_pointNum;
};