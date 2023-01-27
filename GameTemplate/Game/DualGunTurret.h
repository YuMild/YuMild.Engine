#pragma once

#include "Game.h"

#include "EnemyObject.h"
#include "TurretObject.h"

/// <summary>
/// DualGunTurret
/// </summary>
class DualGunTurret : public TurretObject
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
	Quaternion GetModelRotation() const override
	{
		return m_modelRotation;
	}

	/// <summary>
	/// モデルを時計回りに回転
	/// </summary>
	void SetModelRotationTurnRight() override
	{
		m_modelRotation.AddRotationDegY(180.0f);
	}

	/// <summary>
	/// モデルを反時計回りに回転
	/// </summary>
	void SetModelRotationTurnLeft() override
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
	bool GetAttackReady() const override
	{
		return m_moveReady;
	}

	/// <summary>
	/// タレットのHPを加算する
	/// </summary>
	/// <param name="value"></param>
	void AddTurretHP(int value) override
	{
		m_hp += value;
		//上限より増えない様に
		if (m_hp >= m_maxHp)
		{
			m_hp = m_maxHp;
		}
		//0より減らない様に
		else if (m_hp <= 0)
		{
			m_hp = 0;
		}
	}

	/// <summary>
	/// タレットのHPを減算する
	/// </summary>
	/// <param name="value"></param>
	void SubTurretHP(int value) override
	{
		m_hp -= value;
		//上限より増えない様に
		if (m_hp >= m_maxHp)
		{
			m_hp = m_maxHp;
		}
		//0より減らない様に
		else if (m_hp <= 0)
		{
			m_hp = 0;
		}
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
	/// HPを管理
	/// </summary>
	void HP();

	/// <summary>
	/// エフェクトを再生
	/// </summary>
	/// <param name="position"></param>
	void EffectPlayHit(const Vector3& position);

	/// <summary>
	/// 銃声を再生
	/// </summary>
	void SoundPlayFire();

	//動作処理
	std::vector<EnemyObject*>	m_enemys;
	bool						m_moveReady			= false;
	float						m_debuffTimer		= 0.0f;
	float						m_fireRate			= 0.0f;
	Vector3						m_difference		= Vector3::Zero;
	Vector3						m_lockOnPosition	= Vector3::Zero;
	//リコイル
	Vector3						m_recoilPosition	= Vector3::Zero;
	Vector3						m_recoilDifference	= Vector3::Zero;
	
	//エフェクト
	EffectEmitter*				m_hitEF				= nullptr;

	//サウンド
	SoundSource*				m_fireSE			= nullptr;

	//モデル
	ModelRender					m_turretMR;
	ModelRender					m_turretBaseMR;
	ModelRender					m_baseMR;
	ModelRender					m_base2MR;
	Texture						m_emissionMap;
	ModelRender					m_attackRangeMR;

	//HP
	SpriteRender				m_hpBarSR;
	int							m_hp				= 0;
	int							m_maxHp				= 0;
	Vector2						m_hpBarPosition		= Vector2::Zero;

	//モデル
	Vector3						m_modelPosition		= Vector3::Zero;
	Quaternion					m_modelRotation		= Quaternion::Identity;
	Vector3						m_spritePosition	= Vector3::Zero;
};