#include "stdafx.h"
#include "Stage.h"

#include "Game.h"

namespace
{
	//モデル
	const Vector3	STAGE_FIRST_POSITION		= { 0.0f,0.0f,0.0f };
	const float 	STAGE_FIRST_SCALE			= 1.0f;
	const Vector3	CAMP_FIRST_POSITION			= { 0.0f,-100.0f,500.0f };
	const float 	CAMP_FIRST_SCALE			= 12.0f;
	//背景モデル
	//地球
	const Vector3	EARTH_FIRST_POSITION		= { -20000.0f,500.0f,-25000.0f };
	const float 	EARTH_FIRST_SCALE			= 200.0f;
	const float		EARTH_ROTATIONSPEED			= 0.0001f;
	//月
	const Vector3	MOON_FIRST_POSITION			= { -7000.0f,500.0f, -20000.0f };
	const float 	MOON_FIRST_SCALE			= 100.0f;
	const float		MOON_ROTATIONSPEED			= -0.00025f;
	//宇宙ステーション
	const Vector3	SPACEJUNK_FIRST_POSITION	= { 4000.0f,1000.0f,-10000.0f };
	const float 	SPACEJUNK_FIRST_SCALE		= 10.0f;
	const float		SPACEJUNK_ROTATIONSPEED		= 0.0001f;
	//隕石群
	const Vector3	ASTEROID_1_POSITION			= { -3000.0f,700.0f,-20000.0f };
	const Vector3	ASTEROID_1_SCALE			= { 7.0f,7.0f,7.0f };
	const float		ASTEROID_1_ROTATION			= 0.0015f;
	const Vector3	ASTEROID_2_POSITION			= { 2200.0f,-300.0f,0.0f };
	const Vector3	ASTEROID_2_SCALE			= { 2.0f,2.0f,2.0f };
	const float		ASTEROID_2_ROTATION			= -0.0015f;
	const Vector3	ASTEROID_3_POSITION			= { 1500.0f,-500.0f,-6000.0f };
	const Vector3	ASTEROID_3_SCALE			= { 3.0f,3.0f,3.0f };
	const float		ASTEROID_3_ROTATION			= 0.0015f;
	const Vector3	ASTEROID_4_POSITION			= { -2500.0f,-500.0f,-10000.0f };
	const Vector3	ASTEROID_4_SCALE			= { 1.5f,1.5f,1.5f };
	const float		ASTEROID_4_ROTATION			= 0.0020f;
	const Vector3	ASTEROID_5_POSITION			= { 7000.0f,0.0f,-8000.0f };
	const Vector3	ASTEROID_5_SCALE			= { 4.0f,4.0f,4.0f };
	const float		ASTEROID_5_ROTATION			= -0.0020f;
	const Vector3	ASTEROID_6_POSITION			= { -2000.0f,-400.0f,-2500.0f };
	const Vector3	ASTEROID_6_SCALE			= { 2.0f,2.0f,2.0f };
	const float		ASTEROID_6_ROTATION			= 0.0020f;
	const Vector3	ASTEROID_7_POSITION			= { 4800.0f,-200.0f,-2500.0f };
	const Vector3	ASTEROID_7_SCALE			= { 3.0f,3.0f,3.0f };
	const float		ASTEROID_7_ROTATION			= 0.0025f;
	const Vector3	ASTEROID_8_POSITION			= { -4500.0f,200.0f,-4000.0f };
	const Vector3	ASTEROID_8_SCALE			= { 1.0f,1.0f,1.0f };
	const float		ASTEROID_8_ROTATION			= -0.0025f;
	const Vector3	ASTEROID_9_POSITION			= { 1300.0f,-400.0f,-1000.0f };
	const Vector3	ASTEROID_9_SCALE			= { 1.0f,1.0f,1.0f };
	const float		ASTEROID_9_ROTATION			= 0.0025f;
	const Vector3	ASTEROID_10_POSITION		= { -2800.0f,-600.0f,-500.0f };
	const Vector3	ASTEROID_10_SCALE			= { 3.0f,3.0f,3.0f };
	const float		ASTEROID_10_ROTATION		= 0.0030f;
	//エフェクト
	const Vector3	ENERGY_FIRST_POSITION		= { 0.0f,400.0f,500.0f };
	const float		ENERGY_EFFECTSIZE			= 300.0f;
	//サウンド
	const float		DEFAULT_NORMALBGM_VOLUME	= 0.05f;
}

Stage::Stage()
{

}

Stage::~Stage()
{
	//BGMを止める
	if (m_normalBGM != nullptr && m_normalBGM->IsPlaying() == true)
	{
		m_normalBGM->Stop();
	}
}

bool Stage::Start()
{
	//FindGO
	m_gameOver = FindGO<GameOver>("gameOver");

	//初期化
	m_normalBGMVolume = DEFAULT_NORMALBGM_VOLUME;

	//エフェクト
	EffectPlayEnergy(ENERGY_FIRST_POSITION);

	//モデル
	m_stageEmissionMap.InitFromDDSFile(L"Assets/modelData/Stage/Stage_Emission.DDS");
	m_stageMR.Init("Assets/ModelData/Stage/Stage.tkm", ShadowNone, false, nullptr, 0, enModelUpAxisZ, &m_stageEmissionMap);
	m_stageMR.SetPosition(STAGE_FIRST_POSITION);
	m_stageMR.SetScale(Vector3::One * STAGE_FIRST_SCALE);
	m_stageMR.Update();
	m_campEmissionMap.InitFromDDSFile(L"Assets/modelData/Stage/Camp_Emission.DDS");
	m_campMR.Init("Assets/ModelData/Stage/Camp.tkm", ShadowNone, false, nullptr, 0, enModelUpAxisZ, &m_campEmissionMap);
	m_campMR.SetPosition(CAMP_FIRST_POSITION);
	m_campMR.SetScale(Vector3::One * CAMP_FIRST_SCALE);
	m_campMR.Update();
	//背景モデル
	m_earthEmissionMap.InitFromDDSFile(L"Assets/modelData/Stage/Earth_Emission.DDS");
	m_earthMR.Init("Assets/ModelData/Stage/Earth.tkm", ShadowNone, false, nullptr, 0, enModelUpAxisZ, &m_earthEmissionMap);
	m_earthMR.SetPosition(EARTH_FIRST_POSITION);
	m_earthMR.SetScale(Vector3::One * EARTH_FIRST_SCALE);
	m_earthMR.Update();
	m_moonMR.Init("Assets/ModelData/Stage/Moon.tkm");
	m_moonMR.SetPosition(MOON_FIRST_POSITION);
	m_moonMR.SetScale(Vector3::One * MOON_FIRST_SCALE);
	m_moonMR.Update();
	m_spaceJunkEmissionMap.InitFromDDSFile(L"Assets/modelData/Stage/SpaceJunk_Emission.DDS");
	m_spaceJunkMR.Init("Assets/ModelData/Stage/SpaceJunk.tkm", ShadowNone, false, nullptr, 0, enModelUpAxisZ, &m_spaceJunkEmissionMap);
	m_spaceJunkMR.SetPosition(SPACEJUNK_FIRST_POSITION);
	m_spaceJunkMR.SetScale(Vector3::One * SPACEJUNK_FIRST_SCALE);
	m_spaceJunkMR.Update();
	//隕石群
	m_asteroid1MR.Init("Assets/ModelData/Stage/Asteroid1.tkm");
	m_asteroid1MR.SetPosition(ASTEROID_1_POSITION);
	m_asteroid1MR.SetScale(ASTEROID_1_SCALE);
	m_asteroid1MR.Update();
	m_asteroid2MR.Init("Assets/ModelData/Stage/Asteroid2.tkm");
	m_asteroid2MR.SetPosition(ASTEROID_2_POSITION);
	m_asteroid2MR.SetScale(ASTEROID_2_SCALE);
	m_asteroid2MR.Update();
	m_asteroid3MR.Init("Assets/ModelData/Stage/Asteroid3.tkm");
	m_asteroid3MR.SetPosition(ASTEROID_3_POSITION);
	m_asteroid3MR.SetScale(ASTEROID_3_SCALE);
	m_asteroid3MR.Update();
	m_asteroid4MR.Init("Assets/ModelData/Stage/Asteroid4.tkm");
	m_asteroid4MR.SetPosition(ASTEROID_4_POSITION);
	m_asteroid4MR.SetScale(ASTEROID_4_SCALE);
	m_asteroid4MR.Update();
	m_asteroid5MR.Init("Assets/ModelData/Stage/Asteroid5.tkm");
	m_asteroid5MR.SetPosition(ASTEROID_5_POSITION);
	m_asteroid5MR.SetScale(ASTEROID_5_SCALE);
	m_asteroid5MR.Update();
	m_asteroid6MR.Init("Assets/ModelData/Stage/Asteroid6.tkm");
	m_asteroid6MR.SetPosition(ASTEROID_6_POSITION);
	m_asteroid6MR.SetScale(ASTEROID_6_SCALE);
	m_asteroid6MR.Update();
	m_asteroid7MR.Init("Assets/ModelData/Stage/Asteroid7.tkm");
	m_asteroid7MR.SetPosition(ASTEROID_7_POSITION);
	m_asteroid7MR.SetScale(ASTEROID_7_SCALE);
	m_asteroid7MR.Update();
	m_asteroid8MR.Init("Assets/ModelData/Stage/Asteroid8.tkm");
	m_asteroid8MR.SetPosition(ASTEROID_8_POSITION);
	m_asteroid8MR.SetScale(ASTEROID_8_SCALE);
	m_asteroid8MR.Update();
	m_asteroid9MR.Init("Assets/ModelData/Stage/Asteroid9.tkm");
	m_asteroid9MR.SetPosition(ASTEROID_9_POSITION);
	m_asteroid9MR.SetScale(ASTEROID_9_SCALE);
	m_asteroid9MR.Update();
	m_asteroid10MR.Init("Assets/ModelData/Stage/Asteroid10.tkm");
	m_asteroid10MR.SetPosition(ASTEROID_10_POSITION);
	m_asteroid10MR.SetScale(ASTEROID_10_SCALE);
	m_asteroid10MR.Update();

	//BGM
	SetNormalBGM();

	return true;
}

void Stage::Move()
{
	//BGMのフェードイン
	if (m_normalBGMVolume < 0.05f)
	{
		m_normalBGMVolume += 0.00001f;
	}

	//エフェクトのループ
	if (m_energyEF != nullptr && m_energyEF->IsPlay() == false)
	{
		EffectPlayEnergy({ ENERGY_FIRST_POSITION });
	}

	//エフェクトのサイズ
	if (m_energyEF != nullptr)
	{
		m_energyEF->SetScale(((Vector3::One * ENERGY_EFFECTSIZE) * (m_gameOver->GetHP() / 3.0f)));
	}
	
	//隕石群
	m_asteroid1Rotation.AddRotationX(ASTEROID_1_ROTATION);
	m_asteroid1MR.SetRotation(m_asteroid1Rotation);
	m_asteroid1MR.Update();
	m_asteroid2Rotation.AddRotationY(ASTEROID_2_ROTATION);
	m_asteroid2MR.SetRotation(m_asteroid2Rotation);
	m_asteroid2MR.Update();
	m_asteroid3Rotation.AddRotationZ(ASTEROID_3_ROTATION);
	m_asteroid3MR.SetRotation(m_asteroid3Rotation);
	m_asteroid3MR.Update();
	m_asteroid4Rotation.AddRotationX(ASTEROID_4_ROTATION);
	m_asteroid4MR.SetRotation(m_asteroid4Rotation);
	m_asteroid4MR.Update();
	m_asteroid5Rotation.AddRotationY(ASTEROID_5_ROTATION);
	m_asteroid5MR.SetRotation(m_asteroid5Rotation);
	m_asteroid5MR.Update();
	m_asteroid6Rotation.AddRotationZ(ASTEROID_6_ROTATION);
	m_asteroid6MR.SetRotation(m_asteroid6Rotation);
	m_asteroid6MR.Update();
	m_asteroid7Rotation.AddRotationX(ASTEROID_7_ROTATION);
	m_asteroid7MR.SetRotation(m_asteroid7Rotation);
	m_asteroid7MR.Update();
	m_asteroid8Rotation.AddRotationY(ASTEROID_8_ROTATION);
	m_asteroid8MR.SetRotation(m_asteroid8Rotation);
	m_asteroid8MR.Update();
	m_asteroid9Rotation.AddRotationZ(ASTEROID_9_ROTATION);
	m_asteroid9MR.SetRotation(m_asteroid9Rotation);
	m_asteroid9MR.Update();
	m_asteroid10Rotation.AddRotationX(ASTEROID_10_ROTATION);
	m_asteroid10MR.SetRotation(m_asteroid10Rotation);
	m_asteroid10MR.Update();

	//Earth
	m_earthRotation.AddRotationY(EARTH_ROTATIONSPEED);
	m_earthMR.SetRotation(m_earthRotation);
	m_earthMR.Update();
	//Moon
	m_moonRotation.AddRotationX(MOON_ROTATIONSPEED);
	m_moonRotation.AddRotationY(MOON_ROTATIONSPEED);
	m_moonRotation.AddRotationZ(MOON_ROTATIONSPEED);
	m_moonMR.SetRotation(m_moonRotation);
	m_moonMR.Update();
	//SpaceJunk
	m_spaceJunkRotation.AddRotationY(SPACEJUNK_ROTATIONSPEED);
	m_spaceJunkMR.SetRotation(m_spaceJunkRotation);
	m_spaceJunkMR.Update();
}

void Stage::Update()
{
	Move();
}

void Stage::Render(RenderContext& renderContext)
{
	//モデル
	m_stageMR.Draw(renderContext);
	m_campMR.Draw(renderContext);
	//背景モデル
	m_earthMR.Draw(renderContext);
	m_moonMR.Draw(renderContext);
	m_spaceJunkMR.Draw(renderContext);
	//隕石群
	m_asteroid1MR.Draw(renderContext);
	m_asteroid2MR.Draw(renderContext);
	m_asteroid3MR.Draw(renderContext);
	m_asteroid4MR.Draw(renderContext);
	m_asteroid5MR.Draw(renderContext);
	m_asteroid6MR.Draw(renderContext);
	m_asteroid7MR.Draw(renderContext);
	m_asteroid8MR.Draw(renderContext);
	m_asteroid9MR.Draw(renderContext);
	m_asteroid10MR.Draw(renderContext);
}

void Stage::SetNormalBGM()
{
	//BOSS戦のBGMを止める
	if (m_bossBGM != nullptr && m_bossBGM->IsPlaying() == true)
	{
		m_bossBGM->Stop();
	}
	m_normalBGM = NewGO<SoundSource>(0);
	if (m_normalBGM != nullptr)
	{
		m_normalBGM->Init(enSoundNumber_NormalBGM);
		m_normalBGM->SetVolume(m_normalBGMVolume);
		m_normalBGM->Play(true);
	}
}

void Stage::SetBossBGM()
{
	//通常時のBGMを止める
	if (m_normalBGM != nullptr && m_normalBGM->IsPlaying() == true)
	{
		m_normalBGM->Stop();
	}
	m_bossBGM = NewGO<SoundSource>(0);
	if (m_bossBGM != nullptr)
	{
		m_bossBGM->Init(enSoundNumber_BossBGM);
		m_bossBGM->SetVolume(0.05f);
		m_bossBGM->Play(true);
	}
}

void Stage::EffectPlayEnergy(const Vector3& position)
{
	m_energyEF = NewGO<EffectEmitter>(0);
	m_energyEF->Init(enEffectNumber_Energy);
	m_energyEF->SetPosition({ position.x,position.y + 100.0f,position.z });
	m_energyEF->SetScale((Vector3::One * ENERGY_EFFECTSIZE) * (m_gameOver->GetHP() / m_gameOver->GetHP()));
	m_energyEF->Play();
}