#pragma once

/// <summary>
/// �X�e�[�W���Ǘ�����N���X
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