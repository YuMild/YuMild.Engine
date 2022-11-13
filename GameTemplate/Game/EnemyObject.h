#pragma once
class EnemyObject : public IGameObject
{
public:

	/// <summary>
	/// ポジションを取得
	/// </summary>
	/// <returns></returns>
	virtual Vector3 GetPosition() const
	{
		return Vector3::Zero;
	}

	/// <summary>
	/// ステートを取得
	/// </summary>
	/// <returns></returns>
	virtual int GetState() const
	{
		return 0;
	}
};