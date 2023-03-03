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
	virtual const Vector3& GetPosition();

	/// <summary>
	/// �G�l�~�[�̏�Ԃ��擾
	/// </summary>
	/// <returns></returns>
	virtual const bool& GetAlive() const;

	/// <summary>
	/// HP���擾
	/// </summary>
	/// <returns></returns>
	virtual const float& GetDefaultHP() const;

	/// <summary>
	/// HP��ݒ�
	/// </summary>
	/// <param name="setHP"></param>
	virtual const void SetDefaultHP(const int setDefaultHP);

	/// <summary>
	/// HP�����Z
	/// </summary>
	/// <param name="addHP"></param>
	virtual const void AddEnemyHP(const int value);

	/// <summary>
	/// HP�����Z
	/// </summary>
	/// <param name="addHP"></param>
	virtual const void SubEnemyHP(const int value);

	/// <summary>
	/// �S�����Ԃ�ݒ�
	/// </summary>
	/// <param name="bindTime"></param>
	virtual const void SetBind(const float bindTime);
};