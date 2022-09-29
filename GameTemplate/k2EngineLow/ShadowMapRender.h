#pragma once

#include "ModelRender.h"

namespace nsK2EngineLow
{
	class ShadowMapRender
	{
	public:

		/// <summary>
		/// �V���h�E�}�b�v�`��p�̃����_�����O�^�[�Q�b�g���쐬
		/// </summary>
		void Init();

		/// <summary>
		/// �V���h�E�}�b�v�`��p�̃��f�����쐬
		/// </summary>
		/// <param name="filePath"></param>
		void DrawShadowModelInit(const char* filePath);

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="rc"></param>
		void Render(RenderContext& renderContext);

		/// <summary>
		/// �V���h�E�}�b�v�쐬�p�̃J�������擾
		/// </summary>
		/// <returns></returns>
		Camera& GetLightCamera()
		{
			return m_lightCamera;
		}

		/// <summary>
		/// �����_�����O�^�[�Q�b�g���擾
		/// </summary>
		/// <returns></returns>
		RenderTarget& GetRenderTarget()
		{
			return m_shadowMap;
		}

	private:

		ModelRender m_modelRender;
		RenderTarget m_shadowMap;
		Camera m_lightCamera;
	};

	extern ShadowMapRender g_shadowMapRender;
}