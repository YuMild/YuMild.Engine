#pragma once

#include "TurretObject.h"

/// <summary>
/// RocketTurret
/// </summary>
class RocketTurret : public TurretObject
{
public:

	bool Start() override;
	void Update() override;
	void Render(RenderContext& renderContext) override;

	/// <summary>
	/// モデルのポジションを設定
	/// </summary>
	/// <param name="position"></param>
	void SetModelPosition(const Vector3& position) override
	{
		m_modelPosition = position;
	}

	/// <summary>
	/// ポジションを取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetModelPosition() const override
	{
		return m_modelPosition;
	}

	/// <summary>
	/// 画像のポジションを設定
	/// </summary>
	/// <param name="position"></param>
	void SetSpritePosition(const Vector3& position) override
	{
		m_spritePosition = position;
	}

	/// <summary>
	/// 画像のポジションを取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetSpritePosition() const override
	{
		return m_spritePosition;
	}

	/// <summary>
	/// モデルの回転を設定
	/// </summary>
	/// <param name="rotation"></param>
	void SetModelRotation(const float rotation) override
	{
		m_modelRotation.AddRotationDegY(rotation);
	}

	/// <summary>
	/// モデルの回転を取得
	/// </summary>
	/// <returns></returns>
	Quaternion GetModelRotation() override
	{
		return m_modelRotation;
	}

	/// <summary>
	/// モデルを時計回りに回転
	/// </summary>
	void ModelRotationTurnRight() override
	{
		m_modelRotation.AddRotationDegY(180.0f);
	}

	/// <summary>
	/// モデルを反時計回りに回転
	/// </summary>
	void ModelRotationTurnLeft() override
	{
		m_modelRotation.AddRotationDegY(-180.0f);
	}

	/// <summary>
	/// タレットの状態を設定
	/// </summary>
	void SetAttackReady(bool ready) override
	{
		m_moveReady = ready;
	}

	/// <summary>
	/// タレットの状態を取得
	/// </summary>
	/// <returns></returns>
	bool GetAttackReady()
	{
		return m_moveReady;
	}

	/// <summary>
	/// デバフを設定
	/// </summary>
	void SetDebuff() override
	{
		m_debuffTimer = 5.0f;
	}

private:

	//攻撃処理
	bool			m_moveReady = false;
	float			m_debuffTimer = 0.0f;

	//モデル
	ModelRender		m_turretMR;
	ModelRender		m_baseMR;
	ModelRender		m_attackRangeMR;

	//画像
	SpriteRender	m_spriteRender;

	//モデル
	Vector3			m_modelPosition;
	Quaternion		m_modelRotation;
	Vector3			m_spritePosition;
};