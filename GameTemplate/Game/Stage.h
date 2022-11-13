#pragma once

/// <summary>
/// ステージを管理するクラス
/// </summary>
class Stage : public IGameObject
{
public:

private:

	bool Start();
	void Update();
	void Render(RenderContext& renderCntext);

	//モデル
	ModelRender			m_modelRender;

	//音声
	SoundSource*		m_bgm;
};