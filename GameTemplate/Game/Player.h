#pragma once

#include "DualGunTurret.h"

class LeftWindow;

class Player : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

	void OperationNormal();
	void OperationSelectTurret();
	void OperationSetTurret();

	/// <summary>
	/// 操作ステートを取得
	/// </summary>
	/// <returns></returns>
	int GetOperationState() const
	{
		return m_operationState;
	}

private:

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

	DualGunTurret*				m_dualGunTurret;
	LeftWindow*					m_leftWindow;

	ModelRender					m_gridModelRender;

	Vector3						m_cursorPosition;

	int							m_operationState = enOparationStateNormal;
};