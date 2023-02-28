#include "stdafx.h"
#include "HealTurret.h"

#include "Energy.h"
#include "LeftWindow.h"
#include "TurretManager.h"

namespace
{
	const float	MAX_HP				= 200.0f;
	const float EFFECTSIZE_SMOKE	= 50.0f;
}

HealTurret::~HealTurret()
{
	if (m_smokeEF != nullptr)
	{
		m_smokeEF->Stop();
	}
}

bool HealTurret::Start()
{
	//タレット
	m_turretMR.Init("Assets/ModelData/Turret/HealTurret.tkm", ShadowNone, true);
	m_turretMR.SetPosition(m_modelPosition);
	m_turretMR.SetRotation(m_modelRotation);
	m_turretMR.SetScale({ 1.0f,1.0f,1.0f });
	m_turretMR.Update();

	//タレット土台
	m_turretBaseMR.Init("Assets/ModelData/Turret/HealTurretBase.tkm", ShadowNone, true);
	m_turretBaseMR.SetPosition(m_modelPosition);
	m_turretBaseMR.SetRotation(m_modelRotation);
	m_turretBaseMR.SetScale({ 1.0f,1.0f,1.0f });
	m_turretBaseMR.Update();

	//土台
	m_baseMR.Init("Assets/ModelData/Turret/Base.tkm", ShadowNone, true);
	m_baseMR.SetPosition(m_modelPosition);
	m_baseMR.SetRotation(m_modelRotation);
	m_baseMR.SetScale({ 1.0f,1.0f,1.0f });
	m_baseMR.Update();
	m_emissionMap.InitFromDDSFile(L"Assets/modelData/Turret/Base2_Emission.DDS");
	m_base2MR.Init("Assets/ModelData/Turret/Base2.tkm", ShadowNone, false, nullptr, 0, enModelUpAxisZ, &m_emissionMap);
	m_base2MR.SetPosition(m_modelPosition);
	m_base2MR.SetRotation(m_modelRotation);
	m_base2MR.SetScale({ 1.0f,1.0f,1.0f });
	m_base2MR.Update();

	//HPを設定
	m_maxHp = MAX_HP;
	m_hp = m_maxHp;
	m_hpBarSR.Init("Assets/Sprite/Turret/TurretHP.dds", 30.0f, 30.0f);

	return true;
}

void HealTurret::Move()
{
	//死んでいたら
	if (m_hp <= 0.0f)
	{
		m_alive = false;
		if (m_smokeEF == nullptr)
		{
			EffectPlaySmoke(m_modelPosition);
		}
		else if (m_smokeEF->IsPlay() == false)
		{
			EffectPlaySmoke(m_modelPosition);
		}
	}
	//動作可能なら
	if (m_moveReady == true)
	{
		m_turrets = FindGOs<TurretObject>("turret");
		for (auto turrets : m_turrets)
		{
			//全てのタレットとの距離を取る
			Vector3 difference = turrets->GetModelPosition() - m_modelPosition;
			//射程内なら
			if (difference.Length() <= 1000.0f && turrets->GetAttackReady() == true && turrets != this && turrets->GetAlive() == true)
			{
				turrets->AddTurretHP(0.1f);
			}
		}
		m_modelRotation.AddRotationDegY(2.0f);
	}

	//更新処理
	m_turretBaseMR.SetPosition(m_modelPosition);
	m_turretBaseMR.Update();
	m_turretMR.SetPosition(m_modelPosition);
	m_turretMR.SetRotation(m_modelRotation);
	m_turretMR.Update();
	m_baseMR.SetPosition(m_modelPosition);
	m_baseMR.Update();
	m_base2MR.SetPosition(m_modelPosition);
	m_base2MR.Update();
}

void HealTurret::HP()
{
	//HPバー
	Vector3 position = m_modelPosition;
	position.y += 300.0f;
	g_camera3D->CalcScreenPositionFromWorldPosition(m_hpBarPosition, position);
	m_hpBarSR.SetPosition(Vector3(m_hpBarPosition.x, m_hpBarPosition.y, 0.0f));
	m_hpBarSR.SetIsDisplayRestrictionRightSide(true);
	m_hpBarSR.SetLimitedX(m_hp / m_maxHp);
	m_hpBarSR.Update();
}

void HealTurret::Update()
{
	Move();
	HP();
}

void HealTurret::Render(RenderContext& renderContext)
{
	m_turretBaseMR.Draw(renderContext);
	m_turretMR.Draw(renderContext);
	m_baseMR.Draw(renderContext);
	m_base2MR.Draw(renderContext);

	//ダメージを受けていたら
	if (m_hp < m_maxHp)
	{
		m_hpBarSR.Draw(renderContext);
	}
}

void HealTurret::EffectPlaySmoke(const Vector3& position)
{
	m_smokeEF = NewGO<EffectEmitter>(0);
	m_smokeEF->Init(enEffectNumber_Smoke);
	m_smokeEF->SetPosition({ position.x,position.y + 100.0f,position.z });
	m_smokeEF->SetScale(Vector3::One * EFFECTSIZE_SMOKE);
	m_smokeEF->Play();
}