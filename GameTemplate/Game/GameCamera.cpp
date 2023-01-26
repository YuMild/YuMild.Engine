#include "stdafx.h"
#include "GameCamera.h"

bool GameCamera::Start()
{
	Vector3 target = { 0.0f,0.0f,-1500.0f };
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition({ 0.0f, 1500.0f, 1500.0f });
	g_camera3D->SetFar(1000000000.0f);
	return true;
}

void GameCamera::Update()
{

}