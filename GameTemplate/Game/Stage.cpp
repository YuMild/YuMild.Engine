#include "stdafx.h"
#include "Stage.h"

#include "Game.h"

namespace
{
	//ÉÇÉfÉã
	const Vector3	STAGE_FIRST_POSITION		= { 0.0f,0.0f,0.0f };
	const Vector3	STAGE_FIRST_SCALE			= { 1.0f,1.0f,1.0f };
	const Vector3	CAMP_FIRST_POSITION			= { 0.0f,-100.0f,500.0f };
	const Vector3	CAMP_FIRST_SCALE			= { 12.0f,12.0f,12.0f };
	//îwåiÉÇÉfÉã
	const Vector3	EARTH_FIRST_POSITION		= { -20000.0f,500.0f,-25000.0f };
	const Vector3	EARTH_FIRST_SCALE			= { 200.0f,200.0f,200.0f };
	const float		EARTH_ROTATIONSPEED			= 0.00005f;
	const Vector3	MOON_FIRST_POSITION			= { -7000.0f,500.0f, -20000.0f };
	const Vector3	MOON_FIRST_SCALE			= { 100.0f,100.0f,100.0f };
	const float		MOON_ROTATIONSPEED			= -0.00025f;
	const Vector3	SPACEJUNK_FIRST_POSITION	= { 4000.0f,1000.0f,-10000.0f };
	const Vector3	SPACEJUNK_FIRST_SCALE		= { 10.0f,10.0f,10.0f };
	const float		SPACEJUNK_ROTATIONSPEED		= 0.0001f;
	//ÉTÉEÉìÉh
	const float		DEFAULT_NORMALBGM_VOLUME	= 0.05f;
}

Stage::Stage()
{

}

Stage::~Stage()
{
	//BGMÇé~ÇﬂÇÈ
	m_normalBGM->Stop();
}

bool Stage::Start()
{
	//èâä˙âª
	m_normalBGMVolume = DEFAULT_NORMALBGM_VOLUME;

	//ÉÇÉfÉã
	m_stageEmissionMap.InitFromDDSFile(L"Assets/modelData/Stage/Stage_Emission.DDS");
	m_stageMR.Init("Assets/ModelData/Stage/Stage.tkm", ShadowNone);
	m_stageMR.SetPosition(STAGE_FIRST_POSITION);
	m_stageMR.SetScale(STAGE_FIRST_SCALE);
	m_stageMR.Update();
	m_campEmissionMap.InitFromDDSFile(L"Assets/modelData/Stage/Camp_Emission.DDS");
	m_campMR.Init("Assets/ModelData/Stage/Camp.tkm", ShadowNone, false, nullptr, 0, enModelUpAxisZ, &m_campEmissionMap);
	m_campMR.SetPosition(CAMP_FIRST_POSITION);
	m_campMR.SetScale(CAMP_FIRST_SCALE);
	m_campMR.Update();
	//îwåiÉÇÉfÉã
	m_earthMR.Init("Assets/ModelData/Stage/Earth.tkm");
	m_earthMR.SetPosition(EARTH_FIRST_POSITION);
	m_earthMR.SetScale(EARTH_FIRST_SCALE);
	m_earthMR.Update();
	m_moonMR.Init("Assets/ModelData/Stage/Moon.tkm");
	m_moonMR.SetPosition(MOON_FIRST_POSITION);
	m_moonMR.SetScale(MOON_FIRST_SCALE);
	m_moonMR.Update();
	m_spaceJunkEmissionMap.InitFromDDSFile(L"Assets/modelData/Stage/SpaceJunk_Emission.DDS");
	m_spaceJunkMR.Init("Assets/ModelData/Stage/SpaceJunk.tkm", ShadowNone, false, nullptr, 0, enModelUpAxisZ, &m_spaceJunkEmissionMap);
	m_spaceJunkMR.SetPosition(SPACEJUNK_FIRST_POSITION);
	m_spaceJunkMR.SetScale(SPACEJUNK_FIRST_SCALE);
	m_spaceJunkMR.Update();

	//BGM
	SetNormalBGM();

	return true;
}

void Stage::Move()
{
	//BGMÇÃÉtÉFÅ[ÉhÉCÉì
	if (m_normalBGMVolume < 0.05f)
	{
		m_normalBGMVolume += 0.00001f;
	}

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
	//ÉÇÉfÉã
	m_stageMR.Draw(renderContext);
	m_campMR.Draw(renderContext);
	//îwåiÉÇÉfÉã
	m_earthMR.Draw(renderContext);
	m_moonMR.Draw(renderContext);
	m_spaceJunkMR.Draw(renderContext);
}

void Stage::SetNormalBGM()
{
	//BOSSêÌÇÃBGMÇé~ÇﬂÇÈ
	if (m_bossBGM != nullptr && m_bossBGM->IsPlaying() == true)
	{
		m_bossBGM->Stop();
	}
	m_normalBGM = NewGO<SoundSource>(0);
	m_normalBGM->Init(enSoundNumber_NormalBGM);
	m_normalBGM->SetVolume(m_normalBGMVolume);
	m_normalBGM->Play(true);
}

void Stage::SetBossBGM()
{
	//í èÌéûÇÃBGMÇé~ÇﬂÇÈ
	if (m_normalBGM != nullptr && m_normalBGM->IsPlaying() == true)
	{
		m_normalBGM->Stop();
	}
	m_bossBGM = NewGO<SoundSource>(0);
	m_bossBGM->Init(enSoundNumber_BossBGM);
	m_bossBGM->SetVolume(0.05f);
	m_bossBGM->Play(true);
}