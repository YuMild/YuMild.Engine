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
	/// HP���擾
	/// </summary>
	/// <returns></returns>
	virtual float GetDefaultHP() = 0;

	/// <summary>
	/// HP��ݒ�
	/// </summary>
	/// <param name="setHP"></param>
	virtual void SetDefaultHP(const int setDefaultHP) = 0;

	/// <summary>
	/// HP�����Z
	/// </summary>
	/// <param name="addHP"></param>
	virtual void AddEnemyHP(const int value) = 0;

	/// <summary>
	/// HP�����Z
	/// </summary>
	/// <param name="addHP"></param>
	virtual void SubEnemyHP(const int value) = 0;

	/// <summary>
	/// �������Ԃ�ݒ�
	/// </summary>
	/// <param name="bindTime"></param>
	virtual void SetSlow(const float bindTime) = 0;

	/// <summary>
	/// �S�����Ԃ�ݒ�
	/// </summary>
	/// <param name="bindTime"></param>
	virtual void SetBind(const float bindTime) = 0;
};