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
	virtual const Vector3& GetPosition() = 0;

	/// <summary>
	/// HPを取得
	/// </summary>
	/// <returns></returns>
	virtual const float& GetDefaultHP() = 0;

	/// <summary>
	/// HPを設定
	/// </summary>
	/// <param name="setHP"></param>
	virtual const void SetDefaultHP(const int setDefaultHP) = 0;

	/// <summary>
	/// HPを加算
	/// </summary>
	/// <param name="addHP"></param>
	virtual const void AddEnemyHP(const int value) = 0;

	/// <summary>
	/// HPを除算
	/// </summary>
	/// <param name="addHP"></param>
	virtual const void SubEnemyHP(const int value) = 0;

	/// <summary>
	/// 拘束時間を設定
	/// </summary>
	/// <param name="bindTime"></param>
	virtual const void SetBind(const float bindTime) = 0;
};