#pragma once

/// <summary>
/// �X�e�[�W���Ǘ�����N���X
/// </summary>
class Stage : public IGameObject
{
public:

	/// <summary>
	/// BOSS��BGM�ɐ؂�ւ���
	/// </summary>
	void SetNormalBGM()
	{
		/*if (m_bossBgm->IsPlaying() == true)
		{
			m_bossBgm->Stop();
		}*/
		m_bgm = NewGO<SoundSource>(0);
		m_bgm->Init(0);
		m_bgm->SetVolume(0.05f);
		m_bgm->Play(true);
	}

	/// <summary>
	/// BOSS��BGM�ɐ؂�ւ���
	/// </summary>
	void SetBossBGM()
	{
		/*if (m_bgm->IsPlaying() == true)
		{
			m_bgm->Stop();
		}*/
		m_bossBgm = NewGO<SoundSource>(0);
		m_bossBgm->Init(2);
		m_bossBgm->SetVolume(0.05f);
		m_bossBgm->Play(true);
	}

	Stage();
	~Stage();
	bool Start();
	void Update();
	void Render(RenderContext& renderCntext);

private:

	//���f��
	Texture				m_emissionMap;
	ModelRender			m_modelRender;

	//����
	SoundSource*		m_bgm;
	SoundSource*		m_bossBgm;
};