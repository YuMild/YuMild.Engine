#include "stdafx.h"
#include "SpawnManager.h"

bool SpawnManager::Start()
{
	//エフェクトを登録
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/Explosion.efk");

	//音声
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/Explosion.wav");

	//レベルアップする時間
	m_levelTime = 5.0f;

	//敵の初期スポーンタイム
	m_spawnTime_UFO = 3.0f;

	return true;
}

void SpawnManager::LevelUp()
{
	m_levelTimer += g_gameTime->GetFrameDeltaTime();

	if (m_levelTimer > m_levelTime && m_spawnTime_UFO > 0.5f)
	{
		m_spawnTime_UFO -= 0.3f;
		m_levelTimer = 0.0f;
	}
}

void SpawnManager::SpawnUFO()
{
	m_spawnTimer_UFO += g_gameTime->GetFrameDeltaTime();

	//UFOのスポーン
	if (m_spawnTimer_UFO >= m_spawnTime_UFO)
	{
		m_ufo = NewGO<UFO>(0, "ufo");
		m_spawnTimer_UFO = 0.0f;
	}
}

void SpawnManager::Update()
{
	LevelUp();
	SpawnUFO();
}

void SpawnManager::Render(RenderContext& renderContext)
{

}