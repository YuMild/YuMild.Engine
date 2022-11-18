#include "stdafx.h"
#include "SpawnManager.h"

namespace
{
	//HP
	float DEFAULT_HP_UFO = 100.0f;

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
	m_defaultHP_UFO = DEFAULT_HP_UFO;

	//�G�̏����X�|�[���^�C��
	m_spawnTime_UFO = 3.0f;

	return true;
}

void SpawnManager::LevelUp()
{
	m_levelTimer += g_gameTime->GetFrameDeltaTime();

	//���x���A�b�v
	if (m_levelTimer > LEVELUP_TIME && m_defaultHP_UFO < 1000.0f)
	{
		m_defaultHP_UFO *= 1.2f;
		m_levelTimer = 0.0f;
	}
}

void SpawnManager::SpawnUFO()
{
	m_spawnTimer_UFO += g_gameTime->GetFrameDeltaTime();

	//UFO�̃X�|�[��
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