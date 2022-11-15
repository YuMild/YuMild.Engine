#pragma once

/// <summary>
/// 敵の基底クラス
/// </summary>
class EnemyObject : public IGameObject
{
public:

	/// <summary>
	/// デストラクタは必ずvirtualで作成する
	/// </summary>
	virtual ~EnemyObject();

	/// <summary>
	/// ポジションを取得
	/// </summary>
	/// <returns></returns>
	virtual Vector3 GetPosition() = 0;

	/// <summary>
	/// サイズを上げる
	/// </summary>
	/// <returns></returns>
	virtual void MulScale() = 0;

private:

	std::vector<EnemyObject*> m_enemyOnObject;
};