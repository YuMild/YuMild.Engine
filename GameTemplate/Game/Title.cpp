#include "stdafx.h"
#include "Title.h"

#include "Game.h"

Title::Title()
{

}

Title::~Title()
{

}

bool Title::Start()
{
	//画像
	m_titleSR.Init("Assets/sprite/Title/Title.dds", 1600.0f, 900.0f);
	m_titleSR.SetScale({ 1.0f,1.0f,1.0f });
	m_titleSR.Update();

	return true;
}

void Title::Update()
{
	//ボタンを押すとゲームスタート
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		m_game = NewGO<Game>(0, "game");
		DeleteGO(this);
	}
}

void Title::Render(RenderContext& renderContext)
{
	m_titleSR.Draw(renderContext);
}