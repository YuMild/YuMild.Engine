#include "stdafx.h"
#include "Stage.h"

namespace
{
	Vector3 STAGE_FIRST_POSITION = { 0.0f,0.0f,0.0f };
	Vector3 STAGE_FIRST_SCALE = { 1.0f,1.0f,1.0f };
}

bool Stage::Start()
{
	m_modelRender.Init("Assets/ModelData/Stage/Stage.tkm", ShadowRecieveAndDrop);
	m_modelRender.SetPosition(STAGE_FIRST_POSITION);
	m_modelRender.SetScale(STAGE_FIRST_SCALE);
	m_modelRender.Update();

	return true;
}

void Stage::Update()
{

}

void Stage::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}