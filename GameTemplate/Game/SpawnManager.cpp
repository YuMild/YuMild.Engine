#include "stdafx.h"
#include "SpawnManager.h"

namespace
{
	//HP
	float DEFAULT_HP_DEMPA = 500.0f;
	float DEFAULT_HP_UFO = 100.0f;

	//�X�|�[���^�C�}�[
	float DEFAULT_SPAWNTIME_DEMPA = 10.0f;
	float DEFAULT_SPAWNTIME_UFO = 3.0f;

	//���x���A�b�v
	float LEVELUP_TIME = 10.0f;
}

bool SpawnManager::Start()
{
	//�G�t�F�N�g��o�^
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/Explosion.efk");

	//����
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/Explosion.wav");

	//HP
	m_defaultHP_Dempa = DEFAULT_HP_DEMPA;
	m_defaultHP_UFO = DEFAULT_HP_UFO;

	//�X�|�[���^�C��
	m_spawnTime_Dempa = DEFAULT_SPAWNTIME_DEMPA;
	m_spawnTime_UFO = DEFAULT_SPAWNTIME_UFO;

	return true;
}

void SpawnManager::LevelUp()
{
	m_levelTimer += g_gameTime->GetFrameDeltaTime();

	//���x���A�b�v
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

	//Dempa�̃X�|�[��
	if (m_spawnTimer_Dempa >= m_spawnTime_Dempa)
	{
		m_dempa = NewGO<Dempa>(0, "normal");
		m_spawnTimer_Dempa = 0.0f;
	}
}

void SpawnManager::SpawnUFO()
{
	m_spawnTimer_UFO += g_gameTime->GetFrameDeltaTime();

	//UFO�̃X�|�[��
	if (m_spawnTimer_UFO >= m_spawnTime_UFO)
	{
		m_ufo = NewGO<UFO>(0, "normal");
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