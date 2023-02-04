#include "stdafx.h"
#include "Missile.h"

#include "GameOver.h"

#include "SpawnManager.h"
#include "TurretManager.h"

namespace
{
	//モデルの初期値
	Vector3		DEFAULT_POSITION		= { 0.0f,300.0f,-8000.0f };
	Vector3		DEFAULT_SCALE			= { 0.7f,0.7f,0.7f };

	//パラメーター
	float		DEFAULT_MOVE_SPEED		= 15.0f;
	float		DEFAULT_ROTATION_SPEED	= 1.5f;
}

Missile::~Missile()
{

}

bool Missile::Start()
{
	//FindGO
	m_gameOver = FindGO<GameOver>("gameOver");
	m_spawnManager = FindGO<SpawnManager>("spawnManager");
	m_turretManager = FindGO<TurretManager>("turretManager");

	m_position = DEFAULT_POSITION;
	m_scale = DEFAULT_SCALE;

	//モデル
	m_emissionMap.InitFromDDSFile(L"Assets/modelData/Enemy/Missile_Emission.DDS");
	m_modelRender.Init("Assets/modelData/Enemy/Missile.tkm", ShadowNone, false, nullptr, 0, enModelUpAxisZ, &m_emissionMap);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();

	//HP
	m_hp = m_spawnManager->GetDefaultHP_Missile();
	m_maxHp = m_spawnManager->GetDefaultHP_Missile();
	m_hpBarSR.Init("Assets/Sprite/Enemy/EnemyHP.dds", 30.0f, 30.0f);

	return true;
}

void Missile::Move()
{
	//HPが0になったら
	if (m_hp <= 0.0f)
	{
		m_spawnManager->EffectPlayExplosion(m_position);
		m_spawnManager->SoundPlayExplosion();
		DeleteGO(this);
	}

	//移動
	//拘束されていなかったら
	if (m_bindTimer <= 0.0f)
	{
		//射程より長ければOK
		m_difference = { 1000000.0f,1000000.0f,1000000.0f };
		//一番近いタレットに向かう
		m_turrets = FindGOs<TurretObject>("turret");
		{
			//見つかったタレット分for文を回す
			for (auto lockOnObject : m_turrets)
			{
				//配置されているタレットじゃなかったら戻る
				if (lockOnObject->GetAttackReady() == false || lockOnObject->GetAlive() == false)
				{
					continue;
				}
				//全ての敵との距離を測る
				Vector3 turretPosition = { lockOnObject->GetModelPosition().x,0.0f,lockOnObject->GetModelPosition().z };
				Vector3 modelPosition = { m_position.x,0.0f,m_position.z };
				Vector3 difference = turretPosition - modelPosition;
				//全てのタレットの位置を比べて一番近いタレットへ向かう
				if (difference.Length() < m_difference.Length())
				{
					m_difference = difference;
					m_moveSpeed = difference;
					m_moveSpeed.Normalize();
				}
				//攻撃範囲内なら
				if (m_difference.Length() < 200.0f)
				{
					lockOnObject->SubTurretHP(50.0f);
					m_spawnManager->EffectPlayExplosion(m_position);
					m_spawnManager->SoundPlayExplosion();
					DeleteGO(this);
					break;
				}
			}
		}
		//移動
		m_position += m_moveSpeed* 10.0f;
		//回転
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
	}
	//拘束されていたら
	else
	{
		m_bindTimer -= g_gameTime->GetFrameDeltaTime();
	}

	//更新処理
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();
}

void Missile::HP()
{
	//HPバー
	Vector3 position = m_position;
	position.y += 300.0f;
	g_camera3D->CalcScreenPositionFromWorldPosition(m_hpBarPosition, position);
	m_hpBarSR.SetPosition(Vector3(m_hpBarPosition.x, m_hpBarPosition.y, 0.0f));
	m_hpBarSR.SetIsDisplayRestrictionRightSide(true);
	m_hpBarSR.SetLimitedX(m_hp / m_spawnManager->GetDefaultHP_Missile());
	m_hpBarSR.Update();
}

void Missile::Update()
{
	Move();
	HP();
}

void Missile::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);

	//ダメージを受けていたら
	if (m_hp < m_maxHp)
	{
		m_hpBarSR.Draw(renderContext);
	}
}