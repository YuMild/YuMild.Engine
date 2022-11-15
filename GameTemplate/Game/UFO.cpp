#include "stdafx.h"
#include "UFO.h"

#include "SpawnManager.h"

#include "TurretManager.h"

namespace
{
	//初期値
	Vector3 FIRST_POSITION = { 0.0f,0.0f,-8000.0f };
	Vector3 FIRST_SCALE = { 2.95f,2.95f,2.95f };
	float FIRST_ROTATION_Y = 0.0f;

	//ポイントポジション
	Vector3 POINT_1_POSITION = { 0.0f,0.0f,-5900.0f };
	Vector3 POINT_2_POSITION = { -2750.0f,0.0f,-5900.0f };
	Vector3 POINT_3_POSITION = { -2750.0f,0.0f,-3150.0f };
	Vector3 POINT_4_POSITION = { 2750.0f,0.0f,-3150.0f };
	Vector3 POINT_5_POSITION = { 2750.0f,0.0f,-2000.0f };
	Vector3 POINT_6_POSITION = { 0.0f,0.0f,-2000.0f };
	Vector3 POINT_7_POSITION = { 0.0f,0.0f,0.0f };

	//動作
	float MOVE_SPEED = 15.0f;
	float ROTATION_SPEED = 1.5f;
}

UFO::UFO()
{

}

UFO::~UFO()
{

}

bool UFO::Start()
{
	//テスト
	m_scale = { 1.0f,1.0f,1.0f };

	//FindGO
	m_spawnManager = FindGO<SpawnManager>("spawnManager");
	m_turretManager = FindGO<TurretManager>("turretManager");

	m_position = FIRST_POSITION;
	m_rotation.SetRotationDegY(FIRST_ROTATION_Y);

	m_modelRender.Init("Assets/modelData/Enemy/UFO_Blue.tkm", ShadowRecieveAndDrop);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(FIRST_SCALE);
	m_modelRender.Update();

	m_pointList.push_back({ POINT_1_POSITION });     //1番目のポイント
	m_pointList.push_back({ POINT_2_POSITION });     //2番目のポイント
	m_pointList.push_back({ POINT_3_POSITION });     //3番目のポイント
	m_pointList.push_back({ POINT_4_POSITION });     //4番目のポイント
	m_pointList.push_back({ POINT_5_POSITION });     //5番目のポイント
	m_pointList.push_back({ POINT_6_POSITION });     //6番目のポイント
	m_pointList.push_back({ POINT_7_POSITION });     //7番目のポイント
	
	m_pointNum = 0;
	m_target = m_pointList[m_pointNum];

	return true;
}

void UFO::Move()
{
	Vector3 difference = m_target - m_position;

	if (difference.Length() <= 10.0f)
	{
		if (m_pointNum < 6)
		{
			m_pointNum += 1;
			m_target = m_pointList[m_pointNum];
		}
		else
		{
			m_spawnManager->EffectPlayExplosion(m_position);
			m_spawnManager->SoundPlayExplosion(); 
			DeleteGO(this);
			return;
		}
	}

	if (m_scale.x >= 5.0f)
	{
		m_spawnManager->EffectPlayExplosion(m_position);
		m_spawnManager->SoundPlayExplosion();
		DeleteGO(this);
	}

	Vector3 moveSpeed = m_target - m_position;
	moveSpeed.Normalize();
	moveSpeed *= MOVE_SPEED;
	m_position += moveSpeed;

	//回転し続ける
	m_rotation.AddRotationDegY(ROTATION_SPEED);

	//更新処理
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
}

void UFO::Update()
{
	Move();
}

void UFO::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}