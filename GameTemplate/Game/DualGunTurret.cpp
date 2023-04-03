#include "stdafx.h"
#include "DualGunTurret.h"

#include "Game.h"
#include "LeftWindow.h"
#include "TurretManager.h"

namespace
{
	const float	MAX_HP				= 200.0f;
	const float FIRERATE			= 0.1f;
	const float ATTACKPOWER			= 40.0f;
	const float ATTACKRANGE			= 1000.0f;
	const float EFFECTSIZE_HIT		= 150.0f;
	const float EFFECTSIZE_SMOKE	= 50.0f;
	const float SOUNDVOLUME_HIT		= 0.15f;
}

DualGunTurret::~DualGunTurret()
{
	if (m_smokeEF != nullptr)
	{
		m_smokeEF->Stop();
	}
}

bool DualGunTurret::Start()
{
	//タレット
	m_turretMR.Init("Assets/ModelData/Turret/DualGunTurret.tkm", ShadowNone,true);
	m_turretMR.SetPosition(m_modelPosition);
	m_turretMR.SetRotation(m_modelRotation);
	m_turretMR.SetScale({ 1.0f,1.0f,1.0f });
	m_turretMR.Update();

	//タレット土台
	m_turretBaseMR.Init("Assets/ModelData/Turret/TurretBase.tkm", ShadowNone, true);
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

	//射程範囲
	m_attackRangeMR.Init("Assets/ModelData/Turret/AttackRange_Circle.tkm", Dithering,true);
	m_attackRangeMR.SetPosition(m_modelPosition);
	m_attackRangeMR.SetRotation(m_modelRotation);
	m_attackRangeMR.SetScale({ 0.25f,1.0f,0.25f });
	m_attackRangeMR.Update();

	//初期化
	m_recoilPosition = m_modelPosition;

	//HPを設定
	m_maxHp	= MAX_HP;
	m_hp = m_maxHp;
	m_hpBarSR.Init("Assets/Sprite/Turret/TurretHP.dds", 30.0f, 30.0f);

	return true;
}

void DualGunTurret::Move()
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
		if (m_smokeEF == nullptr)
		{
			EffectPlaySmoke(m_modelPosition);
		}
		else if(m_smokeEF->IsPlay() == false)
		{
			EffectPlaySmoke(m_modelPosition);
		}
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
		//射程より長ければOK
		m_difference = { 10000.0f,10000.0f,10000.0f };
		//ロックオンしたか否か
		m_enemys = FindGOs<EnemyObject>("normal");
		for (auto enemys : m_enemys)
		{
			//全ての敵との距離を測る
			Vector3 enemysPosition = { enemys->GetPosition().x,0.0f,enemys->GetPosition().z };
			Vector3 modelPosition = { m_modelPosition.x,0.0f,m_modelPosition.z };
			Vector3 difference = enemysPosition - modelPosition;
			//射程外なら戻る
			if (difference.Length() >= ATTACKRANGE)
			{
				continue;
			}
			//射程内なら続行
			if (difference.Length() < m_difference.Length())
			{
				//ロックオン
				m_lockOnPosition = enemys->GetPosition();

				//正規化
				m_difference = difference;
				m_difference.Normalize();

				//モデルの回転
				Vector3 rotation = m_difference;
				rotation.y = 0.0f;
				rotation.Normalize();
				m_modelRotation.SetRotationYFromDirectionXZ(rotation);
				m_turretMR.SetRotation(m_modelRotation);
				m_turretMR.Update();

				//発射レート
				if (m_fireRate >= FIRERATE)
				{
					enemys->SubEnemyHP(ATTACKPOWER);
					EffectPlayHit(m_lockOnPosition);
					SoundPlayFire();
					//リコイル
					m_recoilDifference = m_difference;
					m_recoilPosition = m_modelPosition;
					m_recoilPosition -= m_recoilDifference * 50.0f;
					m_fireRate = 0.0f;
				}
			}
		}
		//リコイル制御
		Vector3 recoilDifference = m_recoilPosition - m_modelPosition;
		if (recoilDifference.Length() >= 10.0f)
		{
			m_recoilPosition += m_recoilDifference * 10.0f;
		}
		m_turretMR.SetPosition(m_recoilPosition);
	}
	//動作可能でないなら
	else
	{
		m_turretMR.SetPosition(m_modelPosition);
	}

	//更新処理
	m_turretMR.SetRotation(m_modelRotation);
	m_turretMR.Update();
	m_turretBaseMR.SetPosition(m_modelPosition);
	m_turretBaseMR.Update();
	m_baseMR.SetPosition(m_modelPosition);
	m_baseMR.Update();
	m_base2MR.SetPosition(m_modelPosition);
	m_base2MR.Update();
	m_attackRangeMR.SetPosition(m_modelPosition);
	m_attackRangeMR.Update();
}

void DualGunTurret::HP()
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

void DualGunTurret::Update()
{
	Move();
	HP();
}

void DualGunTurret::Render(RenderContext& renderContext)
{
	m_turretMR.Draw(renderContext);
	m_turretBaseMR.Draw(renderContext);
	m_baseMR.Draw(renderContext);
	m_base2MR.Draw(renderContext);

	if (m_moveReady == false)
	{
		m_attackRangeMR.Draw(renderContext);
	}

	//ダメージを受けていたら
	if (m_hp < m_maxHp)
	{
		m_hpBarSR.Draw(renderContext);
	}
}

void DualGunTurret::EffectPlaySmoke(const Vector3& position)
{
	m_smokeEF = NewGO<EffectEmitter>(0);
	m_smokeEF->Init(enEffectNumber_Smoke);
	m_smokeEF->SetPosition({ position.x,position.y + 100.0f,position.z });
	m_smokeEF->SetScale(Vector3::One * EFFECTSIZE_SMOKE);
	m_smokeEF->Play();
}

void DualGunTurret::EffectPlayHit(const Vector3& position)
{
	m_hitEF = NewGO<EffectEmitter>(0);
	m_hitEF->Init(enEffectNumber_DualGunTurret);
	m_hitEF->SetPosition({ position.x,position.y + 200.0f,position.z + 300.0f });
	m_hitEF->SetScale(Vector3::One * EFFECTSIZE_HIT);
	m_hitEF->Play();
}

void DualGunTurret::SoundPlayFire()
{
	m_fireSE = NewGO<SoundSource>(0);
	m_fireSE->Init(enSoundNumber_DualGunTurret);
	m_fireSE->SetVolume(SOUNDVOLUME_HIT);
	m_fireSE->Play(false);
}