#include "stdafx.h"
#include "HolyTurret.h"

#include "TurretManager.h"

namespace
{
	float FIRERATE = 10.0f;
}

HolyTurret::~HolyTurret()
{

}

bool HolyTurret::Start()
{
	//時計土台
	m_turret_BaseMR.Init("Assets/ModelData/Turret/HolyTurret_Base.tkm", ShadowRecieveAndDrop, true);
	m_turret_BaseMR.SetPosition(m_modelPosition);
	m_turret_BaseMR.SetRotation(m_modelRotation);
	m_turret_BaseMR.SetScale({ 1.0f,1.0f,1.0f });
	m_turret_BaseMR.Update();

	//短針
	m_turret_HourHandMR.Init("Assets/ModelData/Turret/HolyTurret_HourHand.tkm", ShadowRecieveAndDrop, true);
	m_turret_HourHandMR.SetPosition(m_modelPosition);
	m_turret_HourHandMR.SetRotation(m_modelRotation);
	m_turret_HourHandMR.SetScale({ 1.0f,1.0f,1.0f });
	m_turret_HourHandMR.Update();

	//長針
	m_turret_MiniteHandMR.Init("Assets/ModelData/Turret/HolyTurret_MiniteHand.tkm", ShadowRecieveAndDrop, true);
	m_turret_MiniteHandMR.SetPosition(m_modelPosition);
	m_turret_MiniteHandMR.SetRotation(m_modelRotation);
	m_turret_MiniteHandMR.SetScale({ 1.0f,1.0f,1.0f });
	m_turret_MiniteHandMR.Update();

	//土台
	m_baseMR.Init("Assets/ModelData/Turret/Base.tkm", ShadowRecieveAndDrop, true);
	m_baseMR.SetPosition(m_modelPosition);
	m_baseMR.SetRotation(m_modelRotation);
	m_baseMR.SetScale({ 1.0f,1.0f,1.0f });
	m_baseMR.Update();

	//エフェクトの回転
	m_effectRotation.SetRotationDegX(90.0f);

	//エフェクトを登録
	EffectEngine::GetInstance()->ResistEffect(8, u"Assets/effect/HolyTurret.efk");

	//音声の生成
	g_soundEngine->ResistWaveFileBank(14, "Assets/sound/HolyTurret.wav");

	return true;
}

void HolyTurret::Move()
{
	//デバフに掛かっていなかったら
	if (m_debuffTimer <= 0.0f)
	{
		m_fireRate += g_gameTime->GetFrameDeltaTime();
	}
	//掛かっていたら
	else
	{
		m_debuffTimer -= g_gameTime->GetFrameDeltaTime();
		m_fireRate += g_gameTime->GetFrameDeltaTime() / 2;
	}

	//動作可能なら
	if (m_moveReady == true)
	{
		if (m_fireRate >= FIRERATE)
		{
			m_enemys = FindGOs<EnemyObject>("normal");
			for (auto enemys : m_enemys)
			{
				enemys->SetBind(2.0f);
			}
			EffectPlayHoly(m_modelPosition);
			SoundPlayHoly();
			m_fireRate = 0.0f;
		}
		m_model_HourHandRotation.AddRotationDegY(g_gameTime->GetFrameDeltaTime() * 0.4f);
		m_model_MiniteHandRotation.AddRotationDegY(g_gameTime->GetFrameDeltaTime() * 30.0f);
	}
}

void HolyTurret::Update()
{
	Move();

	//更新処理
	m_turret_BaseMR.SetPosition(m_modelPosition);
	m_turret_BaseMR.SetRotation(m_modelRotation);
	m_turret_BaseMR.Update();
	m_turret_HourHandMR.SetPosition(m_modelPosition);
	m_turret_HourHandMR.SetRotation(m_modelRotation);
	m_turret_HourHandMR.Update();
	m_turret_MiniteHandMR.SetPosition(m_modelPosition);
	m_turret_MiniteHandMR.SetRotation(m_modelRotation);
	m_turret_MiniteHandMR.Update();
	m_baseMR.SetPosition(m_modelPosition);
	m_baseMR.Update();
}

void HolyTurret::Render(RenderContext& renderContext)
{
	m_turret_BaseMR.Draw(renderContext);
	m_turret_HourHandMR.Draw(renderContext);
	m_turret_MiniteHandMR.Draw(renderContext);
	m_baseMR.Draw(renderContext);
}