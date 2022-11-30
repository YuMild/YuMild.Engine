#pragma once

/// <summary>
/// ステージを管理するクラス
/// </summary>
class Stage : public IGameObject
{
public:

	Stage();
	~Stage();
	bool Start();
	void Update();
	void Render(RenderContext& renderCntext);

private:

	//モデル
	ModelRender			m_modelRender;

	//音声
	SoundSource*		m_bgm;
};