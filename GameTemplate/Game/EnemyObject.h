#pragma once

/// <summary>
/// �G�̊��N���X
/// </summary>
class EnemyObject : public IGameObject
{
public:

	/// <summary>
	/// �f�X�g���N�^�͕K��virtual�ō쐬����
	/// </summary>
	virtual ~EnemyObject();

	/// <summary>
	/// �|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	virtual Vector3 GetPosition() = 0;

	/// <summary>
	/// �T�C�Y���グ��
	/// </summary>
	/// <returns></returns>
	virtual void MulScale() = 0;

private:

	std::vector<EnemyObject*> m_enemyOnObject;
};