#include "stdafx.h"
#include "Game.h"

namespace
{
	float SKYCUBE_SCALE = 3000.0f;
}

Game::Game()
{

}

Game::~Game()
{
	const auto& enemys = FindGOs<EnemyObject>("normal");
	int enemySize = enemys.size();
	for (int i = 0; i < enemySize; i++)
	{
		DeleteGO(enemys[i]);
	}
	const auto& turrets = FindGOs<TurretObject>("turret");
	int turretSize = turrets.size();
	for (int i = 0; i < turretSize; i++)
	{
		DeleteGO(turrets[i]);
	}
	const auto& leftWindowDeletes = FindGOs<LeftWindowDelete>("leftWindowDelete");
	int leftWindowDeleteSize = leftWindowDeletes.size();
	for (int i = 0; i < turretSize; i++)
	{
		DeleteGO(leftWindowDeletes[i]);
	}
	DeleteGO(m_energy);
	DeleteGO(m_gameCamera);
	DeleteGO(m_gameOver);
	DeleteGO(m_leftWindow);
	DeleteGO(m_player);
	DeleteGO(m_skyCube);
	DeleteGO(m_spawnMananer);
	DeleteGO(m_stage);
	DeleteGO(m_turretManager);
}

bool Game::Start()
{
	m_energy		= NewGO<Energy>(0, "energy");
	m_gameCamera	= NewGO<GameCamera>(0, "gameCamera");
	m_gameOver		= NewGO<GameOver>(0, "gameOver");
	m_leftWindow	= NewGO<LeftWindow>(0, "leftWindow");
	m_player		= NewGO<Player>(0, "payer");
	m_skyCube		= NewGO<SkyCube>(0, "skyCube");
	m_spawnMananer	= NewGO<SpawnManager>(0, "spawnManager");
	m_stage			= NewGO<Stage>(0, "stage");
	m_turretManager = NewGO<TurretManager>(0, "turretManager");

	m_skyCube->SetScale({ SKYCUBE_SCALE, SKYCUBE_SCALE, SKYCUBE_SCALE });
	m_skyCube->SetType(enSkyCubeType_Night);
	m_skyCube->SetLuminance(0.5f);

	InitEffect();
	InitSound();

	return true;
}

void Game::Update()
{
	if (m_state == enGameState_GameOver&&g_pad[0]->IsTrigger(enButtonA))
	{
		m_title = NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}

void Game::Render(RenderContext& renderContext)
{

}

void Game::InitEffect()
{
	EffectEngine::GetInstance()->ResistEffect(enEffectNumber_Explosion, u"Assets/effect/Explosion.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectNumber_CursorAfter, u"Assets/effect/CursorAfter.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectNumber_Smoke, u"Assets/effect/Smoke.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectNumber_NormalTurret, u"Assets/effect/NormalTurret.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectNumber_DualGunTurret, u"Assets/effect/DualGunTurret.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectNumber_LaserTurret, u"Assets/Effect/LaserTurret.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectNumber_TeslaTurret, u"Assets/effect/TeslaTurret.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectNumber_HolyTurret, u"Assets/effect/HolyTurret.efk");
}

void Game::InitSound()
{
	g_soundEngine->ResistWaveFileBank(enSoundNumber_NormalBGM, "Assets/sound/NormalBGM.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_Alarm, "Assets/sound/Alarm.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_BossBGM, "Assets/sound/BossBGM.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_Window, "Assets/sound/Window.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_Choice, "Assets/sound/Choice.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_CursorAfter, "Assets/sound/CursorAfter.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_Explosion, "Assets/sound/Explosion.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_NormalTurret, "Assets/sound/NormalTurret.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_DualGunTurret, "Assets/sound/DualGunTurret.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_LaserTurret, "Assets/sound/LaserTurret.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_TeslaTurret, "Assets/sound/TeslaTurret.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_HolyTurret, "Assets/sound/HolyTurret.wav");
}