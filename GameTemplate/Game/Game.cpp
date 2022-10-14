#include "stdafx.h"
#include "Game.h"

namespace
{
	Vector3 STAGE_FIRST_POSITION = { 0.0f,0.0f,0.0f };
	Vector3 STAGE_FIRST_SCALE = { 0.0f,0.0f,0.0f };

	float PLAYER_COLLISION_SIZE_X = 20.0f;
	float PLAYER_COLLISION_SIZE_Y = 100.0f;
}

bool Game::Start()
{
	m_playerModelRender.Init("Assets/ModelData/UnityChan/unityChan.tkm",1);
	m_playerModelRender.SetPosition(m_playerPosition);
	m_playerModelRender.Update();

	stageModelRender.Init("Assets/ModelData/Stage/Stage.tkm", 3);
	stageModelRender.SetPosition(STAGE_FIRST_POSITION);
	stageModelRender.SetScale(STAGE_FIRST_SCALE);
	stageModelRender.Update();

	m_characterController.Init
	(
		PLAYER_COLLISION_SIZE_X, 
		PLAYER_COLLISION_SIZE_Y,
		m_playerPosition
	);

	return true;
}

void Game::Update()
{
	//ƒvƒŒƒCƒ„[‚ÌˆÚ“®
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	float lStick_x = g_pad[0]->GetLStickXF();
	float lStick_y = g_pad[0]->GetLStickYF();
	Vector3 cameraForward = g_camera3D->GetForward();
	Vector3 cameraRight = g_camera3D->GetRight();
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	m_moveSpeed += cameraForward * lStick_y * 500.0f;
	m_moveSpeed += cameraRight * lStick_x * 500.0f;
	m_playerPosition = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_playerModelRender.SetPosition(m_playerPosition);
	m_playerModelRender.Update();

	g_sceneLight.SetPointLightPosition(m_pointLightPosition);
}

void Game::Render(RenderContext& renderContext)
{
	m_playerModelRender.Draw(renderContext);
	stageModelRender.Draw(renderContext);
}