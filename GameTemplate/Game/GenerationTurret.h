#pragma once

#include <EnemyObject.h>

class Energy;
class LeftWindow;
class TurretManager;

class GenerationTurret : public IGameObject
{
public:

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

	/// <summary>
	/// モデルのポジションを設定
	/// </summary>
	/// <param name="position"></param>
	/// <returns></returns>
	void SetModelPosition(const Vector3& position)
	{
		m_modelPosition = position;
	}

	/// <summary>
	/// モデルのポジションを取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetModelPosition() const
	{
		return m_modelPosition;
	}

	/// <summary>
	/// 画像のポジションを設定
	/// </summary>
	/// <param name="position"></param>
	void SetSpritePosition(const Vector3& position)
	{
		m_spritePosition = position;
	}

	/// <summary>
	/// 画像のポジションを取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetSpritePosition() const
	{
		return m_spritePosition;
	}

	/// <summary>
	/// モデルの回転を設定
	/// </summary>
	/// <param name="rotation"></param>
	/// <returns></returns>
	void SetModelRotation(const float rotation)
	{
		m_modelRotation.AddRotationDegY(rotation);
	}

	/// <summary>
	/// モデルの回転を取得
	/// </summary>
	/// <returns></returns>
	Quaternion GetModelRotation()
	{
		return m_modelRotation;
	}

	/// <summary>
	/// モデルを時計回りに回転
	/// </summary>
	/// <param name="rotation"></param>
	/// <returns></returns>
	void ModelRotationTurnRight()
	{
		m_modelRotation.AddRotationDegY(180.0f);
	}

	/// <summary>
	/// モデルを反時計回りに回転
	/// </summary>
	/// <param name="rotation"></param>
	/// <returns></returns>
	void ModelRotationTurnLeft()
	{
		m_modelRotation.AddRotationDegY(-180.0f);
	}

	/// <summary>
	/// タレットの状態変更
	/// </summary>
	/// <param name="ready"></param>
	void SetAttackReady(bool ready)
	{
		m_moveReady = ready;
	}

private:

	/// <summary>
	/// 攻撃処理
	/// </summary>
	void Move();

	//タレットマネージャー
	TurretManager*					m_turretManager;

	//攻撃処理
	bool							m_moveReady = false;
	bool							m_addGenerationTurret = false;

	//クラス
	Energy*							m_energy;
	LeftWindow*						m_leftWindow;

	//モデル
	ModelRender						m_turretBaseModel;
	ModelRender						m_turretModel;
	ModelRender						m_baseModel;

	//モデル
	Vector3							m_modelPosition;
	Quaternion						m_modelRotation;
	Vector3							m_spritePosition;
};