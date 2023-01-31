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
	/// モデルのポジションを設定
	/// </summary>
	/// <param name="position"></param>
	virtual void SetModelPosition(const Vector3& position);

	/// <summary>
	/// ポジションを取得
	/// </summary>
	/// <returns></returns>
	virtual Vector3 GetModelPosition() const;

	/// <summary>
	/// 画像のポジションを設定
	/// </summary>
	/// <param name="position"></param>
	virtual void SetSpritePosition(const Vector3& position);

	/// <summary>
	/// 画像のポジションを取得
	/// </summary>
	/// <returns></returns>
	virtual Vector3 GetSpritePosition() const;

	/// <summary>
	/// モデルの回転を設定
	/// </summary>
	/// <param name="rotation"></param>
	virtual void SetModelRotation(const float rotation);

	/// <summary>
	/// モデルの回転を取得
	/// </summary>
	/// <returns></returns>
	virtual Quaternion GetModelRotation() const;

	/// <summary>
	/// モデルを時計回りに回転
	/// </summary>
	virtual void SetModelRotationTurnRight();

	/// <summary>
	/// モデルを反時計回りに回転
	/// </summary>
	virtual void SetModelRotationTurnLeft();

	/// <summary>
	/// タレットの攻撃態勢を設定
	/// </summary>
	virtual void SetAttackReady(bool ready);

	/// <summary>
	/// タレットの攻撃態勢を取得
	/// </summary>
	/// <returns></returns>
	virtual bool GetAttackReady() const;

	/// <summary>
	/// タレットの状態を取得
	/// </summary>
	/// <returns></returns>
	virtual bool GetAlive() const;

	/// <summary>
	/// タレットのHPを加算する
	/// </summary>
	/// <param name="value"></param>
	virtual void AddTurretHP(float value);

	/// <summary>
	/// タレットのHPを減算する
	/// </summary>
	/// <param name="value"></param>
	virtual void SubTurretHP(float value);

	/// <summary>
	/// デバフを設定
	/// </summary>
	virtual void SetDebuff();
};