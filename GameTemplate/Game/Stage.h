#pragma once

/// <summary>
/// �X�e�[�W���Ǘ�����N���X
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

	//���f��
	ModelRender			m_modelRender;

	//����
	SoundSource*		m_bgm;
};