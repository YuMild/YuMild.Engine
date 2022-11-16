#pragma once

#include <EnemyObject.h>

class LeftWindow;

class TurretManager;

class EnemyObject;

class DualGunTurret : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

	/// <summary>
	/// エネミーを設定
	/// </summary>
	/// <param name="enemys"></param>
	/// <returns></returns>
	void SetEnemys(std::vector<EnemyObject*> enemys)
	{
		m_enemys = enemys;
	}

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

private:

	/// <summary>
	/// 銃声を再生
	/// </summary>
	void SoundPlayFire()
	{
		m_fireSE = NewGO<SoundSource>(0);
		m_fireSE->Init(6);
		m_fireSE->SetVolume(0.025f);
		m_fireSE->Play(false);
	}

	/// <summary>
	/// 攻撃処理
	/// </summary>
	void Attack();

	//テスト
	FontRender						m_fontRender;

	//タレットマネージャー
	TurretManager*					m_turretManager;

	//攻撃処理
	std::vector<EnemyObject*>		m_enemys;
	Vector3							m_difference;
	Vector3							m_lockOnPosition;
	float							m_fireRate = 0.0f;
	SoundSource*					m_fireSE;
	
	//クラス
	LeftWindow*						m_leftWindow;

	//モデル
	ModelRender						m_turretModel;
	ModelRender						m_baseModel;

	//モデル
	Vector3							m_modelPosition;
	Quaternion						m_modelRotation;
	Vector3							m_spritePosition;
};