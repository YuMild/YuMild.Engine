#include "stdafx.h"
#include "SpawnManager.h"

namespace
{
	//HP
	float DEFAULT_HP_UFO = 100.0f;

	//レベルアップ
	float LEVELUP_TIME = 10.0f;
}

bool SpawnManager::Start()
{
	//エフェクトを登録
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/Explosion.efk");

	//音声
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/Explosion.wav");

	//HP
	m_defaultHP_UFO = DEFAULT_HP_UFO;

	//敵の初期スポーンタイム
	m_spawnTime_UFO = 3.0f;

	return true;
}

void SpawnManager::LevelUp()
{
	m_levelTimer += g_gameTime->GetFrameDeltaTime();

	//レベルアップ
	if (m_levelTimer > LEVELUP_TIME && m_defaultHP_UFO < 1000.0f)
	{
		m_defaultHP_UFO *= 1.2f;
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