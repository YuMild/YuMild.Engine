#pragma once

#include "UFO.h"

/// <summary>
/// 敵オブジェクトのスポーンを管理するクラス
/// </summary>
class SpawnManager : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

	//爆破エフェクトを再生
	void EffectPlayExplosion()
	{
		m_explosionEF = NewGO<EffectEmitter>(1);
		m_explosionEF->Init(1);
		m_explosionEF->SetPosition({ 0.0f,0.0f,0.0f });
		m_explosionEF->SetScale(Vector3::One * 100.0f);
		m_explosionEF->Play();
	}

private:

	void SpawnUFO();

	UFO*			m_ufo;

	EffectEmitter*	m_explosionEF;

	float			m_spawnTimer_UFO = 0.0f;
};