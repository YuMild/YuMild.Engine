#pragma once

#include "DualGunTurret.h"
#include "FontRender.h"
#include "GameCamera.h"

class Game : public IGameObject
{
public:

	bool Start();
	void Render(RenderContext& renderContext);
	void Update();

	void OperationNormal();
	void OperationSetTurret();

	int GetOperationState() const
	{
		return m_operationState;
	}

private:

	DualGunTurret*				m_dualGunTurret;
	GameCamera*					m_gameCamera;
	
	//レンダー
	ModelRender					m_stageModelRender;
	ModelRender					m_gridModelRender;

	//プレイヤー
	Vector3						m_cursorPosition;

	//ポイントライト
	Vector3						m_pointLightPosition;

	int							m_operationState = 0;
};