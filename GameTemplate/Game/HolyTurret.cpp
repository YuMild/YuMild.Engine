#include "stdafx.h"
#include "HolyTurret.h"

#include "Game.h"
#include "TurretManager.h"

namespace
{
	const int	MAX_HP		= 200;
	const float FIRERATE	= 12.0f;
}

HolyTurret::~HolyTurret()
{

}

bool HolyTurret::Start()
{
	//時計土台
	m_turret_BaseMR.Init("Assets/ModelData/Turret/HolyTurret_Base.tkm", ShadowNone, true);
	m_turret_BaseMR.SetPosition(m_modelPosition);
	m_turret_BaseMR.SetRotation(m_modelRotation);
	m_turret_BaseMR.SetScale({ 1.0f,1.0f,1.0f });
	m_turret_BaseMR.Update();

	//短針
	m_turret_HourHandMR.Init("Assets/ModelData/Turret/HolyTurret_HourHand.tkm", ShadowNone, true);
	m_turret_HourHandMR.SetPosition(m_modelPosition);
	m_turret_HourHandMR.SetRotation(m_modelRotation);
	m_turret_HourHandMR.SetScale({ 1.0f,1.0f,1.0f });
	m_turret_HourHandMR.Update();

	//長針
	m_turret_MiniteHandMR.Init("Assets/ModelData/Turret/HolyTurret_MiniteHand.tkm", ShadowNone, true);
	m_turret_MiniteHandMR.SetPosition(m_modelPosition);
	m_turret_MiniteHandMR.SetRotation(m_modelRotation);
	m_turret_MiniteHandMR.SetScale({ 1.0f,1.0f,1.0f });
	m_turret_MiniteHandMR.Update();

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

	//エフェクトの回転
	m_effectRotation.SetRotationDegX(90.0f);

	//エフェクトを登録
	EffectEngine::GetInstance()->ResistEffect(enEffectNumber_HolyTurret, u"Assets/effect/HolyTurret.efk");

	//音声の生成
	g_soundEngine->ResistWaveFileBank(enSoundNumber_HolyTurret, "Assets/sound/HolyTurret.wav");

	//HPを設定
	m_maxHp = MAX_HP;
	m_hp = m_maxHp;
	m_hpBarSR.Init("Assets/Sprite/Turret/TurretHP.dds", 30.0f, 30.0f);

	return true;
}

void HolyTurret::Move()
{
	//デバフに掛かっていたら
	if (m_debuffTimer > 0.0f)
	{
		m_debuffTimer -= g_gameTime->GetFrameDeltaTime();
		m_fireRate += g_gameTime->GetFrameDeltaTime() / 2;
	}
	//死んでいたら
	else if (m_hp <= 0.0f)
	{
		m_alive = false;
		m_fireRate += g_gameTime->GetFrameDeltaTime() / 2;
	}
	//生きていてデバフに掛かっていなかったら
	else
	{
		m_alive = true;
		m_fireRate += g_gameTime->GetFrameDeltaTime();
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
		m_model_HourHandRotation.AddRotationDegY(g_gameTime->GetFrameDeltaTime() * 5.0f);
		m_model_MiniteHandRotation.AddRotationDegY(g_gameTime->GetFrameDeltaTime() * 60.0f);
	}

	//更新処理
	m_turret_BaseMR.SetPosition(m_modelPosition);
	m_turret_BaseMR.SetRotation(m_modelRotation);
	m_turret_BaseMR.Update();
	m_turret_HourHandMR.SetPosition(m_modelPosition);
	m_turret_HourHandMR.SetRotation(m_model_HourHandRotation);
	m_turret_HourHandMR.Update();
	m_turret_MiniteHandMR.SetPosition(m_modelPosition);
	m_turret_MiniteHandMR.SetRotation(m_model_MiniteHandRotation);
	m_turret_MiniteHandMR.Update();
	m_baseMR.SetPosition(m_modelPosition);
	m_baseMR.Update();
	m_base2MR.SetPosition(m_modelPosition);
	m_base2MR.Update();
}

void HolyTurret::HP()
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

void HolyTurret::Update()
{
	Move();
	HP();
}

void HolyTurret::Render(RenderContext& renderContext)
{
	m_turret_BaseMR.Draw(renderContext);
	m_turret_HourHandMR.Draw(renderContext);
	m_turret_MiniteHandMR.Draw(renderContext);
	m_baseMR.Draw(renderContext);
	m_base2MR.Draw(renderContext);

	//ダメージを受けていたら
	if (m_hp < m_maxHp)
	{
		m_hpBarSR.Draw(renderContext);
	}
}

void HolyTurret::EffectPlayHoly(const Vector3& position)
{
	m_holyEF = NewGO<EffectEmitter>(0);
	m_holyEF->Init(enEffectNumber_HolyTurret);
	m_holyEF->SetPosition({ position.x,position.y - 10.0f,position.z + 300.0f });
	m_holyEF->SetRotation(m_effectRotation);
	m_holyEF->SetScale(Vector3::One * 100.0f);
	m_holyEF->Play();
}

void HolyTurret::SoundPlayHoly()
{
	m_holySE = NewGO<SoundSource>(0);
	m_holySE->Init(enSoundNumber_HolyTurret);
	m_holySE->SetVolume(0.05f);
	m_holySE->Play(false);
}