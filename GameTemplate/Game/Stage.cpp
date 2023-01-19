#include "stdafx.h"
#include "Stage.h"

#include "Game.h"

namespace
{
	Vector3 STAGE_FIRST_POSITION = { 0.0f,0.0f,0.0f };
	Vector3 STAGE_FIRST_SCALE = { 1.0f,1.0f,1.0f };
}

Stage::Stage()
{

}

Stage::~Stage()
{
	//BGM‚ðŽ~‚ß‚é
	m_bgm->Stop();
}

bool Stage::Start()
{
	//ƒ‚ƒfƒ‹
	m_modelRender.Init("Assets/ModelData/Stage/Stage.tkm", ShadowRecieve);
	m_modelRender.SetPosition(STAGE_FIRST_POSITION);
	m_modelRender.SetScale(STAGE_FIRST_SCALE);
	m_modelRender.Update();

	//BGM
	g_soundEngine->ResistWaveFileBank(enSoundNumber_BGM, "Assets/sound/BGM.wav");
	g_soundEngine->ResistWaveFileBank(enSoundNumber_BossBGM, "Assets/sound/BossBGM.wav");
	SetNormalBGM();

	return true;
}

void Stage::Update()
{

}

void Stage::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}