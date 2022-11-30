#include "stdafx.h"
#include "Stage.h"

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
	m_modelRender.Init("Assets/ModelData/Stage/Stage.tkm", ShadowRecieveAndDrop);
	m_modelRender.SetPosition(STAGE_FIRST_POSITION);
	m_modelRender.SetScale(STAGE_FIRST_SCALE);
	m_modelRender.Update();

	//BGM
	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/BGM.wav");
	m_bgm = NewGO<SoundSource>(4);
	m_bgm->Init(4);
	m_bgm->SetVolume(0.05f);
	m_bgm->Play(true);

	return true;
}

void Stage::Update()
{

}

void Stage::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}