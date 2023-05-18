#pragma once

namespace nsK2EngineLow
{
	class RenderingEngine
	{
	public:

		/// <summary>
		/// �e��Init�����s
		/// </summary>
		void Init();

		/// <summary>
		/// �����_�[�^�[�Q�b�g���쐬
		/// </summary>
		void InitMainRenderTarget();

		/// <summary>
		/// ���f�������_�[�I�u�W�F�N�g�̐���ǉ�
		/// </summary>
		/// <param name="modelRenderObject"></param>
		void AddModelRenderObject(ModelRender* modelRenderObject)
		{
			m_modelRenderObject.push_back(modelRenderObject);
		}

		/// <summary>
		/// �X�v���C�g�����_�[�I�u�W�F�N�g�̐��̒ǉ�
		/// </summary>
		/// <param name="spriteRenderObject"></param>
		void AddSpriteRenderObject(SpriteRender* spriteRenderObject)
		{
			m_spriteRenderObject.push_back(spriteRenderObject);
		}

		/// <summary>
		/// �t�H���g�����_�[�I�u�W�F�N�g�̐��̒ǉ�
		/// </summary>
		/// <param name="spriteRenderObject"></param>
		void AddFontRenderObject(FontRender* fontRenderObject)
		{
			m_fontRenderObject.push_back(fontRenderObject);
		}

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="renderContext"></param>
		void Draw(RenderContext& renderContext);

		/// <summary>
		/// �摜�̕`��
		/// </summary>
		/// <param name="renderContext"></param>
		void SpriteDraw(RenderContext& renderContext);

		/// <summary>
		/// �t�H���g�̕`��
		/// </summary>
		/// <param name="renderContext"></param>
		void FontDraw(RenderContext& renderContext);

		/// <summary>
		/// ���s
		/// </summary>
		/// <param name="renderTarget"></param>
		void Execute(RenderContext& renderTarget);

		/// <summary>
		/// ���C�������_�����O�^�[�Q�b�g���擾
		/// </summary>
		/// <returns></returns>
		RenderTarget& GetMainRenderTarget()
		{
			return m_mainRenderTarget;
		}

	private:

		std::vector<ModelRender*>		m_modelRenderObject;
		std::vector<SpriteRender*>		m_spriteRenderObject;
		std::vector<FontRender*>		m_fontRenderObject;
		RenderTarget					m_mainRenderTarget;
	};

	extern RenderingEngine				g_renderingEngine;
}
