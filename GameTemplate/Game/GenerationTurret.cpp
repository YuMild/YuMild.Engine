#include "stdafx.h"
#include "GenerationTurret.h"

#include "Energy.h"
#include "LeftWindow.h"
#include "TurretManager.h"

bool GenerationTurret::Start()
{
	//FindGO
	m_energy = FindGO<Energy>("energy");
	m_leftWindow = FindGO<LeftWindow>("leftWindow");
	m_turretManager = FindGO<TurretManager>("turretManager");

	//タレット
	m_turretBaseModel.Init("Assets/ModelData/Turret/GenerationTurretBase.tkm", ShadowRecieveAndDrop, true);
	m_turretBaseModel.SetPosition(m_modelPosition);
	m_turretBaseModel.SetRotation(m_modelRotation);
	m_turretBaseModel.SetScale({ 1.0f,1.0f,1.0f });
	m_turretBaseModel.Update();
	m_turretModel.Init("Assets/ModelData/Turret/GenerationTurret.tkm", ShadowRecieveAndDrop, true);
	m_turretModel.SetPosition(m_modelPosition);
	m_turretModel.SetRotation(m_modelRotation);
	m_turretModel.SetScale({ 1.0f,1.0f,1.0f });
	m_turretModel.Update();

	//土台
	m_baseModel.Init("Assets/ModelData/Turret/Base.tkm", ShadowRecieveAndDrop, true);
	m_baseModel.SetPosition(m_modelPosition);
	m_baseModel.SetRotation(m_modelRotation);
	m_baseModel.SetScale({ 1.0f,1.0f,1.0f });
	m_baseModel.Update();

	m_addGenerationTurret = true;

	return true;
}

void GenerationTurret::Move()
{
	//動作可能なら
	if (m_moveReady == true)
	{
		m_modelRotation.AddRotationDegY(2.0f);
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
	m_turretBaseModel.SetPosition(m_modelPosition);
	m_turretBaseModel.Update();
	m_turretModel.SetPosition(m_modelPosition);
	m_turretModel.SetRotation(m_modelRotation);
	m_turretModel.Update();
	m_baseModel.SetPosition(m_modelPosition);
	m_baseModel.Update();
}

void GenerationTurret::Render(RenderContext& renderContext)
{
	m_turretBaseModel.Draw(renderContext);
	m_turretModel.Draw(renderContext);
	m_baseModel.Draw(renderContext);
}