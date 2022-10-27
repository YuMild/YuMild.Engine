#include "stdafx.h"
#include "LeftWindow.h"

#include "Player.h"

namespace
{
	float DEFAULT_SPRITE_SIZE = 720.0f;
	float MOVE_X_DEFAULT = 50.0f;
	float MOVE_X_LIMIT = 400.0f;
	Vector3 DEFAULT_POSITION = { -950.0f,0.0f,0.0f };
}

bool LeftWindow::Start()
{
	m_player = FindGO<Player>("player");

	m_turretBackGround.Init("Assets/sprite/LeftWindow/LeftWindow_TurretBackGround.dds", DEFAULT_SPRITE_SIZE, DEFAULT_SPRITE_SIZE);
	m_turretBackGround.SetPosition(DEFAULT_POSITION);
	m_turretBackGround.SetScale({ 1.0f,1.0f,1.0f });
	m_turretBackGround.Update();
	m_frame.Init("Assets/sprite/LeftWindow/LeftWindow_Frame.dds", DEFAULT_SPRITE_SIZE, DEFAULT_SPRITE_SIZE);
	m_frame.SetPosition(DEFAULT_POSITION);
	m_frame.SetScale({ 1.0f,1.0f,1.0f });
	m_frame.Update();

	m_turretBackGroundPosition[0] = { -950.0f,0.0f,0.0f };
	m_turretBackGroundPosition[1] = { -865.0f,0.0f,0.0f };
	m_turretBackGroundPosition[2] = { -780.0f,0.0f,0.0f };
	m_turretBackGroundPosition[3] = { -695.0f,0.0f,0.0f };
	m_turretBackGroundPosition[4] = { -950.0f,-100.0f,0.0f };
	m_turretBackGroundPosition[5] = { -865.0f,-100.0f,0.0f };
	m_turretBackGroundPosition[6] = { -780.0f,-100.0f,0.0f };
	m_turretBackGroundPosition[7] = { -695.0f,-100.0f,0.0f };
	m_turretBackGroundPosition[8] = { -950.0f,-200.0f,0.0f };
	m_turretBackGroundPosition[9] = { -865.0f,-200.0f,0.0f };
	m_turretBackGroundPosition[10] = { -780.0f,-200.0f,0.0f };
	m_turretBackGroundPosition[11] = { -695.0f,-200.0f,0.0f };

	return true;
}

void LeftWindow::NormalMode()
{
	if (m_move_Number >= MOVE_X_DEFAULT)
	{
		m_move_Number -= 50.0f;
	}

	m_turretBackGround.SetPosition({ m_turretBackGroundPosition[m_selectTurretNumber].x + m_move_Number, m_turretBackGroundPosition[m_selectTurretNumber].y, m_turretBackGroundPosition[m_selectTurretNumber].z });
	m_turretBackGround.Update();
	m_frame.SetPosition({ DEFAULT_POSITION.x + m_move_Number, DEFAULT_POSITION.y, DEFAULT_POSITION.z });
	m_frame.Update();
}

void LeftWindow::CursorMode()
{
	if (m_move_Number <= MOVE_X_LIMIT)
	{
		m_move_Number += 50.0f;
	}
	
	m_turretBackGround.SetPosition({ m_turretBackGroundPosition[m_selectTurretNumber].x + m_move_Number, m_turretBackGroundPosition[m_selectTurretNumber].y, m_turretBackGroundPosition[m_selectTurretNumber].z });
	m_turretBackGround.Update();
	m_frame.SetPosition({ DEFAULT_POSITION.x + m_move_Number, DEFAULT_POSITION.y, DEFAULT_POSITION.z });
	m_frame.Update();
}

void LeftWindow::Update()
{
	if (m_operationState == enOparationStateNormal)
	{
		NormalMode();
	}
	else if (m_operationState == enOparationStateSelectTurret)
	{
		CursorMode();
	}
}

void LeftWindow::Render(RenderContext& renderContext)
{
	if (m_move_Number >= MOVE_X_LIMIT)
	{
		m_turretBackGround.Draw(renderContext);
	}
	m_frame.Draw(renderContext);
}