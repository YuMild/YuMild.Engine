#pragma once

#include "EnemyObject.h"
#include "TurretObject.h"

/// <summary>
/// LaserTurret
/// </summary>
class LaserTurret : public TurretObject
{
public:

	LaserTurret();
	~LaserTurret();
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
	/// 銃声を再生
	/// </summary>
	void SoundPlayFire()
	{
		m_fireSE = NewGO<SoundSource>(0);
		m_fireSE->Init(10);
		m_fireSE->SetVolume(0.025f);
		m_fireSE->Play(false);
	}

	//攻撃処理
	std::vector<EnemyObject*>	m_enemys;
	bool						m_moveReady = false;
	bool						m_laserIsPlay = true;
	float						m_debuffTimer = 0.0f;
	float						m_fireRate = 0.0f;
	float						m_laserAliveTimer = 0.0f;
	Vector3						m_laserPosition;
	Vector3						m_forward;

	//モデル
	ModelRender					m_turretMR;
	ModelRender					m_baseMR;
	ModelRender					m_attackRangeMR;

	//画像
	SpriteRender				m_spriteRender;

	//エフェクト
	EffectEmitter*				m_laserEF;

	//サウンド
	SoundSource*				m_fireSE;

	//モデル
	Vector3						m_modelPosition;
	Quaternion					m_modelRotation;
	Vector3						m_spritePosition;
};