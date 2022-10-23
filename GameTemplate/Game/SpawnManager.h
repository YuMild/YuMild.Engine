#pragma once

#include "UFO.h"

/// <summary>
/// 敵オブジェクトのスポーンを管理するクラス
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