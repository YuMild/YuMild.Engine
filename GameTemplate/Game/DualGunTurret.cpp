#include "stdafx.h"
#include "DualGunTurret.h"

#include "LeftWindow.h"
#include "TurretManager.h"

namespace
{
	float FIRERATE = 0.1f;
}

bool DualGunTurret::Start()
{
	//タレット
	m_turretModel.Init("Assets/ModelData/Turret/DualGunTurret.tkm", ShadowRecieveAndDrop,true);
	m_turretModel.SetPosition(m_modelPosition);
	m_turretModel.SetScale({ 1.0f,1.0f,1.0f });
	m_turretModel.Update();

	//土台
	m_baseModel.Init("Assets/ModelData/Turret/Base.tkm", ShadowRecieveAndDrop, true);
	m_baseModel.SetPosition(m_modelPosition);
	m_baseModel.SetScale({ 1.0f,1.0f,1.0f });
	m_baseModel.Update();

	//エフェクトを登録
	EffectEngine::GetInstance()->ResistEffect(2, u"Assets/effect/Hit.efk");

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
		m_fireRate += g_gameTime->GetFrameDeltaTime() / 5;
	}

	//動作可能なら
	if (m_moveReady == true)
	{
		//射程より長ければOK
		m_difference = { 10000.0f,10000.0f,10000.0f };
		//ロックオンしたか否か
		m_enemys = FindGOs<EnemyObject>("ufo");
		for (auto lockOnObject : m_enemys)
		{
			//全ての敵との距離を測る
			Vector3 difference = lockOnObject->GetPosition() - m_modelPosition;
			//射程内で且つ一番近かったら
			if (difference.Length() >= 1000.0f)
			{
				continue;
			}
			if (difference.Length() < m_difference.Length())
			{
				m_lockOnPosition = lockOnObject->GetPosition();
				m_difference = difference;

				//正規化
				m_difference.Normalize();

				//モデルの回転
				Vector3 rotation = m_difference;
				rotation.y = 0.0f;
				rotation.Normalize();
				Quaternion quaternion;
				quaternion.SetRotationYFromDirectionXZ(rotation);
				m_turretModel.SetRotation(quaternion);
				m_turretModel.Update();

				//発射レート
				if (m_fireRate >= FIRERATE)
				{
					lockOnObject->SubHP(5.0f);
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
	m_turretModel.SetPosition(m_modelPosition);
	m_turretModel.Update();
	m_baseModel.SetPosition(m_modelPosition);
	m_baseModel.Update();
}

void DualGunTurret::Render(RenderContext& renderContext)
{
	m_turretModel.Draw(renderContext);
	m_baseModel.Draw(renderContext);
}