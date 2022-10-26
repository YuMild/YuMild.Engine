#include "stdafx.h"
#include "LeftWindow.h"

bool LeftWindow::Start()
{
	m_frame.Init("Assets/sprite/LeftWindow/LeftWindow_Frame.dds", 720.0f, 720.0f);
	m_turretBackGround.Init("Assets/sprite/LeftWindow/LeftWindow_TurretBackGround.dds", 720.0f, 720.0f);
	return true;
}

void LeftWindow::Update()
{

}

void LeftWindow::Render(RenderContext& renderContext)
{
	m_frame.Draw(renderContext);
	m_turretBackGround.Draw(renderContext);
}