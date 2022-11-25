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
	/// HPを取得
	/// </summary>
	/// <returns></returns>
	virtual float GetDefaultHP() = 0;

	/// <summary>
	/// HPを設定
	/// </summary>
	/// <param name="setHP"></param>
	virtual void SetDefaultHP(const float setDefaultHP) = 0;

	/// <summary>
	/// HPを加算
	/// </summary>
	/// <param name="addHP"></param>
	virtual void AddHP(const float addHP) = 0;

	/// <summary>
	/// HPを除算
	/// </summary>
	/// <param name="addHP"></param>
	virtual void SubHP(const float subHP) = 0;
};