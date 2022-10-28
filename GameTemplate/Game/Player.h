#pragma once

#include "DualGunTurret.h"
#include "LaserTurret.h"

class LeftWindow;
class TurretManager;

class Player : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderContext);

	void OperationNormal();
	void OperationSelectTurret();
	void OperationSetTurret();

	void MakeModel();

	/// <summary>
	/// ����X�e�[�g���擾
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


	std::vector<IGameObject>	m_turrets;

	DualGunTurret*				m_dualGunTurret;
	LaserTurret*				m_laserTurret;
	LeftWindow*					m_leftWindow;
	TurretManager*				m_turretManager;

	ModelRender					m_gridModelRender;

	Vector3						m_cursorPosition;

	int							m_operationState = enOparationStateNormal;
};