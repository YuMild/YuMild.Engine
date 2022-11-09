#include "stdafx.h"
#include "SpawnManager.h"

bool SpawnManager::Start()
{
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/Explosion.efk");

	return true;
}

void SpawnManager::SpawnUFO()
{
	m_spawnTimer_UFO += g_gameTime->GetFrameDeltaTime();

	if (m_spawnTimer_UFO >= 1.0f)
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