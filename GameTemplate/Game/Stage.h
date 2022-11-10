#pragma once

/// <summary>
/// ステージを管理するクラス
/// </summary>
class Stage : public IGameObject
{
public:

	bool Start();
	void Update();
	void Render(RenderContext& renderCntext);

private:

	ModelRender			m_modelRender;

	SoundSource*		m_bgm;
};