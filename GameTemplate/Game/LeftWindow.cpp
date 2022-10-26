#include "stdafx.h"
#include "LeftWindow.h"

#include "Player.h"

bool LeftWindow::Start()
{
	m_player = FindGO<Player>("player");

	//m_frame.Init("Assets/sprite/LeftWindow/LeftWindow_Frame.dds", 720.0f, 720.0f);
	m_turretBackGround.Init("Assets/sprite/LeftWindow/LeftWindow_Frame.dds", 720.0f, 720.0f);

	m_turretBackGroundPosition[0] = { 0.0f,0.0f,0.0f };
	m_turretBackGroundPosition[1] = { 100.0f,0.0f,0.0f };
	m_turretBackGroundPosition[2] = { 200.0f,0.0f,0.0f };
	m_turretBackGroundPosition[3] = { 300.0f,0.0f,0.0f };
	m_turretBackGroundPosition[4] = { 0.0f,-100.0f,0.0f };
	m_turretBackGroundPosition[5] = { 100.0f,-100.0f,0.0f };
	m_turretBackGroundPosition[6] = { 200.0f,-100.0f,0.0f };
	m_turretBackGroundPosition[7] = { 300.0f,-100.0f,0.0f };
	m_turretBackGroundPosition[8] = { 0.0f,-200.0f,0.0f };
	m_turretBackGroundPosition[9] = { 100.0f,-200.0f,0.0f };
	m_turretBackGroundPosition[10] = { 200.0f,-200.0f,0.0f };
	m_turretBackGroundPosition[11] = { 300.0f,-200.0f,0.0f };

	return true;
}

void LeftWindow::CursorMode()
{
	m_turretBackGround.SetPosition(m_turretBackGroundPosition[m_selectTurretNumber]);
	m_turretBackGround.Update();
}

void LeftWindow::Update()
{
	CursorMode();
}

void LeftWindow::Render(RenderContext& renderContext)
{
	//m_frame.Draw(renderContext);
	m_turretBackGround.Draw(renderContext);
}