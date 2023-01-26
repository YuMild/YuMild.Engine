#include "stdafx.h"
#include "TeslaTurret.h"

#include "Game.h"
#include "LeftWindow.h"
#include "TurretManager.h"

namespace
{
	const int	MAX_HP		= 200;
	const float FIRERATE	= 2.0f;
	const float ATTACKPOWER	= 300.0f;
	const float ATTACKRANGE	= 2000.0f;
	const float BINDTIME	= 0.5f;
}

bool TeslaTurret::Start()
{
	//タレット
	m_turretMR.Init("Assets/ModelData/Turret/TeslaTurret.tkm", ShadowNone, true);
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
	m_attackRangeMR.Init("Assets/ModelData/Turret/AttackRange_Circle.tkm", Dithering, true);
	m_attackRangeMR.SetPosition(m_modelPosition);
	m_attackRangeMR.SetRotation(m_modelRotation);
	m_attackRangeMR.SetScale({ 0.5f,1.0f,0.5f });
	m_attackRangeMR.Update();

	//エフェクトを登録
	EffectEngine::GetInstance()->ResistEffect(7, u"Assets/effect/TeslaTurret.efk");

	//音声の生成
	g_soundEngine->ResistWaveFileBank(enSoundNumber_TeslaTurret, "Assets/sound/TeslaTurret.wav");

	//HPを設定
	m_maxHp = MAX_HP;
	m_hp = m_maxHp;

	return true;
}

void TeslaTurret::Move()
{
	//体力が無くなったら
	if (m_hp <= 0)
	{
		DeleteGO(this);
	}

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

				//発射レート
				if (m_fireRate >= FIRERATE)
				{
					enemys->SubHP(ATTACKPOWER);
					enemys->SetBind(BINDTIME);
					EffectPlayHit(m_lockOnPosition);
					SoundPlayFire();
					m_fireRate = 0.0f;
				}
			}
		}
	}
}

void TeslaTurret::Update()
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

void TeslaTurret::Render(RenderContext& renderContext)
{
	m_turretMR.Draw(renderContext);
	m_baseMR.Draw(renderContext);
	if (m_moveReady == false)
	{
		m_attackRangeMR.Draw(renderContext);
	}
}