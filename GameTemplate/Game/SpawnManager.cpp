#include "stdafx.h"
#include "SpawnManager.h"

bool SpawnManager::Start()
{
	//�G�t�F�N�g��o�^
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/Explosion.efk");

	//����
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/Explosion.wav");

	return true;
}

void SpawnManager::SpawnUFO()
{
	m_spawnTimer_UFO += g_gameTime->GetFrameDeltaTime();

	//UFO�̃X�|�[��
	if (m_spawnTimer_UFO >= 2.75f)
	{
		m_ufo = NewGO<UFO>(0, "ufo");
		m_spawnTimer_UFO = 0.0f;
	}
}

void SpawnManager::Update()
{
	SpawnUFO();
}

void SpawnManager::Render(RenderContext& renderContext)
{

}