#pragma once

/// <summary>
/// タレットの基底クラス
/// </summary>
class TurretObject : public IGameObject
{
public:

	/// <summary>
	/// デストラクタは必ずvirtualで作成する
	/// </summary>
	virtual ~TurretObject();

	/// <summary>
	/// ポジションを取得
	/// </summary>
	/// <returns></returns>
	virtual Vector3 GetModelPosition() const = 0;
};