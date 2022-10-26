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
	void OperationSelectTurret();
	void OperationSetTurret();

	int GetOperationState() const
	{
		return m_operationState;
	}

public:

	enum OparationState
	{
		enOparationStateNormal,
		enOparationStateSelectTurret,
		enOparationStateSetTurret
	};

	enum Turret
	{
		enTurretDualGunTurret,
		enTurretLaserTurret,
		enTurretLocketTurret,
		en3,
		en4,
		en5,
		en6,
		en7,
		en8,
		en9,
		en10,
		en11
	};

private:

	DualGunTurret*				m_dualGunTurret;
	UFO*						m_ufo;

	ModelRender					m_gridModelRender;

	Vector3						m_cursorPosition;

	int							m_operationState = enOparationStateNormal;
	int							m_selectTurretNumber = 0;
};