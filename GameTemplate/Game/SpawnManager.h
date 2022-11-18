#pragma once

#include "UFO.h"

/// <summary>
/// 敵のスポーンを管理するクラス
/// </summary>
class SpawnManager : public IGameObject
{
public:

	/// <summary>
	/// UFOのデフォルトHPを設定
	/// </summary>
	/// <returns></returns>
	float GetDefaultHP_UFO()
	{
		return m_defaultHP_UFO;
	}

	//爆破エフェクトを再生
	void EffectPlayExplosion(Vector3& position)
	{
		m_explosionEF = NewGO<EffectEmitter>(0);
		m_explosionEF->Init(1);
		m_explosionEF->SetPosition(position);
		m_explosionEF->SetScale(Vector3::One * 50.0f);
		m_explosionEF->Play();
	}

	//爆破音声を再生
	void SoundPlayExplosion()
	{
		m_explosionSE = NewGO<SoundSource>(5);
		m_explosionSE->Init(5);
		m_explosionSE->SetVolume(0.05f);
		m_explosionSE->Play(false);
	}

private:

	bool Start()override;
	void Update()override;
	void Render(RenderContext& renderContext)override;

	/// <summary>
	/// レベルアップ
	/// </summary>
	void LevelUp();

	/// <summary>
	/// UFOのスポーンを管理
	/// </summary>
	void SpawnUFO();

	//クラス
	UFO*			m_ufo;

	//破壊時のエフェクト
	EffectEmitter*	m_explosionEF;

	//破壊時の音声
	SoundSource*	m_explosionSE;

	//レベルを管理するタイマー
	float			m_levelTimer = 0.0f;

	//UFOのスポーンタイマー
	float			m_spawnTime_UFO = 0.0f;
	float			m_spawnTimer_UFO = 0.0f;

	//UFOのHP
	float			m_defaultHP_UFO = 0.0f;
};