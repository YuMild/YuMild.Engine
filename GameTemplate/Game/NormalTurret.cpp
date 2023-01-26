#include "stdafx.h"
#include "NormalTurret.h"

#include "Game.h"
#include "LeftWindow.h"
#include "TurretManager.h"

namespace
{
	const int	MAX_HP		= 100;
	const float FIRERATE	= 0.5f;
	const float ATTACKPOWER	= 50.0f;
	const float ATTACKRANGE	= 1000.0f;
}

bool NormalTurret::Start()
{
	//タレット
	m_turretMR.Init("Assets/ModelData/Turret/NormalTurret.tkm", ShadowNone, true);
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
	m_attackRangeMR.SetScale({ 0.25f,1.0f,0.25f });
	m_attackRangeMR.Update();

	//エフェクトを登録
	EffectEngine::GetInstance()->ResistEffect(6, u"Assets/effect/NormalTurret.efk");

	//音声の生成
	g_soundEngine->ResistWaveFileBank(enSoundNumber_NormalTurret, "Assets/sound/NormalTurret.wav");

	//HPを設定
	m_maxHp = MAX_HP;
	m_hp = m_maxHp;

	return true;
}

void NormalTurret::Move()
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

void NormalTurret::Update()
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

void NormalTurret::Render(RenderContext& renderContext)
{
	m_turretMR.Draw(renderContext);
	m_baseMR.Draw(renderContext);
	if (m_moveReady == false)
	{
		m_attackRangeMR.Draw(renderContext);
	}
}

void NormalTurret::EffectPlayHit(const Vector3& position)
{
	m_hitEF = NewGO<EffectEmitter>(0);
	m_hitEF->Init(6);
	m_hitEF->SetPosition({ position.x,position.y + 200.0f,position.z + 300.0f });
	m_hitEF->SetScale(Vector3::One * 150.0f);
	m_hitEF->Play();
}

void NormalTurret::SoundPlayFire()
{
	m_fireSE = NewGO<SoundSource>(0);
	m_fireSE->Init(enSoundNumber_NormalTurret);
	m_fireSE->SetVolume(0.025f);
	m_fireSE->Play(false);
}