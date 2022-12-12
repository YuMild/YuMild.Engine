#include "stdafx.h"
#include "GenerationTurret.h"

#include "Energy.h"
#include "TurretManager.h"

GenerationTurret::GenerationTurret()
{

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
	m_turretMR.Init("Assets/ModelData/Turret/GenerationTurret.tkm", ShadowRecieveAndDrop, true);
	m_turretMR.SetPosition(m_modelPosition);
	m_turretMR.SetRotation(m_modelRotation);
	m_turretMR.SetScale({ 1.0f,1.0f,1.0f });
	m_turretMR.Update();

	//土台
	m_baseMR.Init("Assets/ModelData/Turret/Base.tkm", ShadowRecieveAndDrop, true);
	m_baseMR.SetPosition(m_modelPosition);
	m_baseMR.SetRotation(m_modelRotation);
	m_baseMR.SetScale({ 1.0f,1.0f,1.0f });
	m_baseMR.Update();

	m_addGenerationTurret = true;

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
}

void GenerationTurret::Update()
{
	Move();

	//更新処理
	m_turretMR.SetPosition(m_modelPosition);
	m_turretMR.SetRotation(m_modelRotation);
	m_turretMR.Update();
	m_baseMR.SetPosition(m_modelPosition);
	m_baseMR.Update();
}

void GenerationTurret::Render(RenderContext& renderContext)
{
	m_turretMR.Draw(renderContext);
	m_baseMR.Draw(renderContext);
}