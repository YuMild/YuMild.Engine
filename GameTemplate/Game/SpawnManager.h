#pragma once

#include "UFO.h"

/// <summary>
/// �G�I�u�W�F�N�g�̃X�|�[�����Ǘ�����N���X
/// </summary>
class SpawnManager : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

	void SpawnUFO();

private:

	UFO*			m_ufo;

	float			m_spawnTimer_UFO = 0.0f;
};