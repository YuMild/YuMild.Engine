#include "stdafx.h"
#include "SpawnManager.h"

#include "Game.h"

namespace
{
	//HP
	const float DEFAULT_HP_UFO					= 100.0f;
	const float DEFAULT_HP_DEMPA				= 100.0f;
	const float DEFAULT_HP_SPACESHIP			= 5000.0f;

	//スポーンタイマー
	const float DEFAULT_SPAWNTIME_UFO			= 3.0f;
	const float DEFAULT_SPAWNTIME_DEMPA			= 10.0f;
	const float DEFAULT_SPAWNTIME_SPACESHIP		= 30.0f;

	//初スポーンまでの時間
	const float DELAY_UFO						= 67.0f;
	const float DELAY_DEMPA						= 60.0f;
	const float DELAY_SPACESHIP					= 0.0f;

	//レベルアップ
	const float LEVELUP_TIME					= 10.0f;

	//WARNING
	const float CIRCLE_ROTATION_NUMBER			= 75.0f;
}

SpawnManager::~SpawnManager()
{
	
}

bool SpawnManager::Start()
{
	//エフェクトを登録
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/Explosion.efk");

	//画像を作成
	m_warningSR.Init("Assets/sprite/Warning/WARNING.dds", 1600.0f, 900.0f);
	m_warningSR.SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	m_warningSR.Update();
	m_warningRightCircleSR.Init("Assets/sprite/Warning/WARNING_CIRCLE.dds", 900.0f, 900.0f);
	m_warningRightCircleSR.SetPosition({ 612.0f,0.0f,0.0f });
	m_warningRightCircleSR.SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	m_warningRightCircleSR.Update();
	m_warningLeftCircleSR.Init("Assets/sprite/Warning/WARNING_CIRCLE.dds", 900.0f, 900.0f);
	m_warningLeftCircleSR.SetPosition({ -612.0f,0.0f,0.0f });
	m_warningLeftCircleSR.SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	m_warningLeftCircleSR.Update();

	//音声
	g_soundEngine->ResistWaveFileBank(enSoundNumber_Explosion, "Assets/sound/Explosion.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_Alarm, "Assets/sound/Alarm.wav");

	//HP
	m_defaultHP_UFO = DEFAULT_HP_UFO;
	m_defaultHP_Dempa = DEFAULT_HP_DEMPA;
	m_defaultHP_SpaceShip = DEFAULT_HP_SPACESHIP;

	//ディレイ
	m_spawnTimer_UFO = -DELAY_UFO;
	m_spawnTimer_Dempa = -DELAY_DEMPA;
	m_spawnTimer_SpaceShip = -DELAY_SPACESHIP;

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
			m_defaultHP_UFO *= 1.2f;
		}
		if (m_defaultHP_Dempa < 5000.0f)
		{
			m_defaultHP_Dempa *= 1.2f;
		}
		m_levelTimer = 0.0f;
	}
}

void SpawnManager::SpawnUFO()
{
	m_spawnTimer_UFO += g_gameTime->GetFrameDeltaTime();

	//UFOのスポーン
	if (m_spawnTimer_UFO >= DEFAULT_SPAWNTIME_UFO)
	{
		m_ufo = NewGO<UFO>(0, "normal");
		m_spawnTimer_UFO = 0.0f;
	}
}

void SpawnManager::SpawnDempa()
{
	m_spawnTimer_Dempa += g_gameTime->GetFrameDeltaTime();

	//Dempaのスポーン
	if (m_spawnTimer_Dempa >= DEFAULT_SPAWNTIME_DEMPA)
	{
		m_dempa = NewGO<Dempa>(0, "normal");
		m_spawnTimer_Dempa = 0.0f;
	}
}

void SpawnManager::SpawnSpaceShip()
{
	m_spawnTimer_SpaceShip += g_gameTime->GetFrameDeltaTime();

	//SpaceShipのスポーン
	if (m_spawnTimer_SpaceShip >= DEFAULT_SPAWNTIME_SPACESHIP)
	{
		SoundPlayBossSpawn();
		m_spaceShip = NewGO<SpaceShip>(0, "normal");
		m_spawnTimer_SpaceShip = 0.0f;
		GameObjectManager::GetInstance()->SetStop(true);
		m_isStop = true;
	}
}

void SpawnManager::Update()
{
	LevelUp();
	SpawnUFO();
	SpawnDempa();
	SpawnSpaceShip();
}

void SpawnManager::UpdateOnStop()
{
	m_stopTimer += g_gameTime->GetFrameDeltaTime();
	if (m_stopTimer >= 3.75f && m_warningTimer <= 0.01f)
	{
		GameObjectManager::GetInstance()->SetStop(false);
		m_isStop = false;

		//リセット
		m_warningTimer = 0.0f;
		m_stopTimer = 0.0f;
	}

	//フェード
	if (m_fade == true)
	{
		m_warningTimer += g_gameTime->GetFrameDeltaTime() * 1.5f;
		if (m_warningTimer >= 1.1f)
		{
			m_fade = false;
		}
	}
	else
	{
		m_warningTimer -= g_gameTime->GetFrameDeltaTime() * 1.5f;
		if (m_warningTimer <= 0.01f)
		{
			m_fade = true;
		}
	}

	m_warningRightCircle_RotationNumber += g_gameTime->GetFrameDeltaTime() * CIRCLE_ROTATION_NUMBER;
	m_warningRightCircle_Rotation.SetRotationDegZ(m_warningRightCircle_RotationNumber);
	m_warningRightCircleSR.SetRotation(m_warningRightCircle_Rotation);
	m_warningRightCircleSR.SetMulColor({ 1.0f, 1.0f, 1.0f, m_warningTimer });
	m_warningRightCircleSR.Update();
	m_warningLeftCircle_RotationNumber -= g_gameTime->GetFrameDeltaTime() * CIRCLE_ROTATION_NUMBER;
	m_warningLeftCircle_Rotation.SetRotationDegZ(m_warningLeftCircle_RotationNumber);
	m_warningLeftCircleSR.SetRotation(m_warningLeftCircle_Rotation);
	m_warningLeftCircleSR.SetMulColor({ 1.0f, 1.0f, 1.0f, m_warningTimer });
	m_warningLeftCircleSR.Update();
	m_warningSR.SetMulColor({ 1.0f, 1.0f, 1.0f, m_warningTimer});
	m_warningSR.Update();
}

void SpawnManager::Render(RenderContext& renderContext)
{
	if (m_isStop == true)
	{
		m_warningRightCircleSR.Draw(renderContext);
		m_warningLeftCircleSR.Draw(renderContext);
		m_warningSR.Draw(renderContext);
	}
}