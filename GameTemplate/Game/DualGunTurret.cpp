#include "stdafx.h"
#include "DualGunTurret.h"

#include "LeftWindow.h"
#include "TurretManager.h"

namespace
{
	float FIRERATE = 0.1f;
	float ATTACKPOWER = 50.0f;
}

bool DualGunTurret::Start()
{
	//タレット
	m_turretMR.Init("Assets/ModelData/Turret/DualGunTurret.tkm", ShadowRecieveAndDrop,true);
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

	//射程範囲
	m_attackRangeMR.Init("Assets/ModelData/Turret/AttackRange_Circle.tkm", Dithering,true);
	m_attackRangeMR.SetPosition(m_modelPosition);
	m_attackRangeMR.SetRotation(m_modelRotation);
	m_attackRangeMR.SetScale({ 0.25f,1.0f,0.25f });
	m_attackRangeMR.Update();

	//エフェクトを登録
	EffectEngine::GetInstance()->ResistEffect(2, u"Assets/effect/DualGunTurret.efk");

	//音声の生成
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/DualGunTurret.wav");

	return true;
}

void DualGunTurret::Move()
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
		//射程より長ければOK
		m_difference = { 10000.0f,10000.0f,10000.0f };
		//ロックオンしたか否か
		m_enemys = FindGOs<EnemyObject>("normal");
		for (auto enemys : m_enemys)
		{
			//全ての敵との距離を測る
			Vector3 difference = enemys->GetPosition() - m_modelPosition;
			//射程内で且つ一番近かったら
			if (difference.Length() >= 1000.0f)
			{
				continue;
			}
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
					enemys->SubHP(ATTACKPOWER);
					EffectPlayHit(m_lockOnPosition);
					SoundPlayFire();
					m_fireRate = 0.0f;
				}
			}
		}
	}
}

void DualGunTurret::Update()
{
	Move();

	//更新処理
	m_turretMR.SetPosition(m_modelPosition);
	m_turretMR.SetRotation(m_modelRotation);
	m_turretMR.Update();
	m_baseMR.SetPosition(m_modelPosition);
	m_baseMR.Update();
	m_attackRangeMR.SetPosition(m_modelPosition);
	m_attackRangeMR.Update();
}

void DualGunTurret::Render(RenderContext& renderContext)
{
	m_turretMR.Draw(renderContext);
	m_baseMR.Draw(renderContext);
	if (m_moveReady == false)
	{
		m_attackRangeMR.Draw(renderContext);
	}
}