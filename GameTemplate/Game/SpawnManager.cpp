#include "stdafx.h"
#include "SpawnManager.h"

namespace
{
	//HP
	float DEFAULT_HP_DEMPA = 500.0f;
	float DEFAULT_HP_UFO = 100.0f;

	//スポーンタイマー
	float DEFAULT_SPAWNTIME_DEMPA = 10.0f;
	float DEFAULT_SPAWNTIME_UFO = 3.0f;

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
	//Dempa
	m_defaultHP_Dempa = DEFAULT_HP_DEMPA;

	//UFO
	m_defaultHP_UFO = DEFAULT_HP_UFO;

	//敵の初期スポーンタイム
	//Dempa
	m_spawnTime_Dempa = DEFAULT_SPAWNTIME_DEMPA;

	//UFO
	m_spawnTime_UFO = DEFAULT_SPAWNTIME_UFO;

	return true;
}

void SpawnManager::LevelUp()
{
	m_levelTimer += g_gameTime->GetFrameDeltaTime();

	//レベルアップ
	if (m_levelTimer > LEVELUP_TIME)
	{
		if (m_defaultHP_UFO < 1000.0f)
		{
			m_defaultHP_UFO *= 1.1f;
		}
		if (m_defaultHP_Dempa < 5000.0f)
		{
			m_defaultHP_Dempa *= 1.1f;
		}
		m_levelTimer = 0.0f;
	}
}

void SpawnManager::SpawnDempa()
{
	m_spawnTimer_Dempa += g_gameTime->GetFrameDeltaTime();

	//Dempaのスポーン
	if (m_spawnTimer_Dempa >= m_spawnTime_Dempa)
	{
		m_dempa = NewGO<Dempa>(0, "dempa");
		m_spawnTimer_Dempa = 0.0f;
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
	SpawnDempa();
	SpawnUFO();
}

void SpawnManager::Render(RenderContext& renderContext)
{

}