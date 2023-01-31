#include "stdafx.h"
#include "GenerationTurret.h"

#include "Energy.h"
#include "TurretManager.h"

namespace
{
	const int	MAX_HP = 200;
}

GenerationTurret::~GenerationTurret()
{
	if (m_moveReady == true)
	{
		m_energy->SubGenerationTurret();
	}
}

bool GenerationTurret::Start()
{
	//FindGO
	m_energy = FindGO<Energy>("energy");

	//タレット
	m_turretMR.Init("Assets/ModelData/Turret/GenerationTurret.tkm", ShadowNone, true);
	m_turretMR.SetPosition(m_modelPosition);
	m_turretMR.SetRotation(m_modelRotation);
	m_turretMR.SetScale({ 1.0f,1.0f,1.0f });
	m_turretMR.Update();

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

	//一度だけ実行
	m_addGenerationTurret = true;

	//HPを設定
	m_maxHp = MAX_HP;
	m_hp = m_maxHp;
	m_hpBarSR.Init("Assets/Sprite/Turret/TurretHP.dds", 30.0f, 30.0f);

	return true;
}

void GenerationTurret::Move()
{
	//動作可能なら
	if (m_moveReady == true)
	{
		if (m_addGenerationTurret == true)
		{
			m_energy->AddGenerationTurret();
			m_addGenerationTurret = false;
		}
	}

	//更新処理
	m_turretMR.SetPosition(m_modelPosition);
	m_turretMR.SetRotation(m_modelRotation);
	m_turretMR.Update();
	m_baseMR.SetPosition(m_modelPosition);
	m_baseMR.Update();
	m_base2MR.SetPosition(m_modelPosition);
	m_base2MR.Update();
}

void GenerationTurret::HP()
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

void GenerationTurret::Update()
{
	Move();
	HP();
}

void GenerationTurret::Render(RenderContext& renderContext)
{
	m_turretMR.Draw(renderContext);
	m_baseMR.Draw(renderContext);
	m_base2MR.Draw(renderContext);

	//ダメージを受けていたら
	if (m_hp < m_maxHp)
	{
		m_hpBarSR.Draw(renderContext);
	}
}