#pragma once

#include "UFO.h"

/// <summary>
/// 敵オブジェクトのスポーンを管理するクラス
/// </summary>
class SpawnManager : public IGameObject
{
public:

	//爆破エフェクトを再生
	void EffectPlayExplosion()
	{
		m_explosionEF = NewGO<EffectEmitter>(1);
		m_explosionEF->Init(1);
		m_explosionEF->SetPosition({ 0.0f,0.0f,0.0f });
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

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

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

	//UFOのスポーンタイマー
	float			m_spawnTimer_UFO = 0.0f;
};