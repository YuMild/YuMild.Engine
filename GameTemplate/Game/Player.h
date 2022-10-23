#pragma once

#include "DualGunTurret.h"
#include "UFO.h"

class Player : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

	void OperationNormal();
	void OperationSetTurret();

	int GetOperationState() const
	{
		return m_operationState;
	}

public:

	enum OparationState
	{
		enOparationStateNormal,
		enOparationStateSetTurret
	};

private:

	DualGunTurret*				m_dualGunTurret;
	UFO*						m_ufo;

	ModelRender					m_gridModelRender;

	Vector3						m_cursorPosition;

	int							m_operationState = enOparationStateNormal;
};