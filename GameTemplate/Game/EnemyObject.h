#pragma once
class EnemyObject : public IGameObject
{
public:

	/// <summary>
	/// �|�W�V�������擾
	/// </summary>
	/// <returns></returns>
	virtual Vector3 GetPosition() const
	{
		return Vector3::Zero;
	}

	/// <summary>
	/// �X�e�[�g���擾
	/// </summary>
	/// <returns></returns>
	virtual int GetState() const
	{
		return 0;
	}
};