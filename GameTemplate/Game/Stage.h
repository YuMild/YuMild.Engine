#pragma once

/// <summary>
/// �X�e�[�W���Ǘ�����N���X
/// </summary>
class Stage : public IGameObject
{
public:

private:

	bool Start();
	void Update();
	void Render(RenderContext& renderCntext);

	//���f��
	ModelRender			m_modelRender;

	//����
	SoundSource*		m_bgm;
};