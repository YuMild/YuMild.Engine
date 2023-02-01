#include "stdafx.h"
#include "Stage.h"

#include "Game.h"

namespace
{
	const Vector3	STAGE_FIRST_POSITION		= { 0.0f,0.0f,0.0f };
	const Vector3	STAGE_FIRST_SCALE			= { 1.0f,1.0f,1.0f };
	const Vector3	CAMP_FIRST_POSITION			= { 0.0f,-100.0f,500.0f };
	const Vector3	CAMP_FIRST_SCALE			= { 12.0f,12.0f,12.0f };
	const float		DEFAULT_NORMALBGM_VOLUME	= 0.05f;
}

Stage::Stage()
{

}

Stage::~Stage()
{
	//BGMを止める
	m_normalBGM->Stop();
}

bool Stage::Start()
{
	//初期化
	m_normalBGMVolume = DEFAULT_NORMALBGM_VOLUME;

	//モデル
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

	//BGM
	SetNormalBGM();

	return true;
}

void Stage::Update()
{
	//BGMのフェードイン
	if (m_normalBGMVolume < 0.05f)
	{
		m_normalBGMVolume += 0.00001f;
	}
}

void Stage::Render(RenderContext& renderContext)
{
	m_stageMR.Draw(renderContext);
	m_campMR.Draw(renderContext);
}

void Stage::SetNormalBGM()
{
	//BOSS戦のBGMを止める
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
	//通常時のBGMを止める
	if (m_normalBGM != nullptr && m_normalBGM->IsPlaying() == true)
	{
		m_normalBGM->Stop();
	}
	m_bossBGM = NewGO<SoundSource>(0);
	m_bossBGM->Init(enSoundNumber_BossBGM);
	m_bossBGM->SetVolume(0.05f);
	m_bossBGM->Play(true);
}