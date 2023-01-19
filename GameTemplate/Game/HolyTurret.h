#pragma once

#include "EnemyObject.h"
#include "TurretObject.h"

/// <summary>
/// HolyTurret
/// </summary>
class HolyTurret : public TurretObject
{
public:

	~HolyTurret();
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

	/// <summary>
	/// 攻撃処理
	/// </summary>
	void Move();

	/// <summary>
	/// エフェクトを再生
	/// </summary>
	/// <param name="position"></param>
	void EffectPlayHoly(const Vector3& position);

	/// <summary>
	/// 銃声を再生
	/// </summary>
	void SoundPlayHoly();

	//攻撃処理
	std::vector<EnemyObject*>		m_enemys;
	bool							m_moveReady = false;
	float							m_debuffTimer = 0.0f;
	float							m_fireRate = 0.0f;

	//エフェクト
	EffectEmitter*					m_holyEF;
	Quaternion						m_effectRotation;

	//サウンド
	SoundSource*					m_holySE;

	//モデル
	ModelRender						m_turret_BaseMR;
	ModelRender						m_turret_HourHandMR;
	ModelRender						m_turret_MiniteHandMR;
	ModelRender						m_baseMR;

	//モデル
	Vector3							m_modelPosition;
	Quaternion						m_modelRotation;
	Quaternion						m_model_HourHandRotation;
	Quaternion						m_model_MiniteHandRotation;
	Vector3							m_spritePosition;
};