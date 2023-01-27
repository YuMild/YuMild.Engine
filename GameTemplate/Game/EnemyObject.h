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
	virtual void SetDefaultHP(const int setDefaultHP) = 0;

	/// <summary>
	/// HPを加算
	/// </summary>
	/// <param name="addHP"></param>
	virtual void AddEnemyHP(const int value) = 0;

	/// <summary>
	/// HPを除算
	/// </summary>
	/// <param name="addHP"></param>
	virtual void SubEnemyHP(const int value) = 0;

	/// <summary>
	/// 減速時間を設定
	/// </summary>
	/// <param name="bindTime"></param>
	virtual void SetSlow(const float bindTime) = 0;

	/// <summary>
	/// 拘束時間を設定
	/// </summary>
	/// <param name="bindTime"></param>
	virtual void SetBind(const float bindTime) = 0;
};