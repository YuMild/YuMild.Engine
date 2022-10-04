#pragma once

#include "ShadowMapRender.h"

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
		/// �V���h�E�}�b�v�����_�[���쐬
		/// </summary>
		void InitShadowMapRender();

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="renderContext"></param>
		void Draw(RenderContext& renderContext);

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="renderContext"></param>
		void RenderToShadowMap(RenderContext& renderContext);

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
		ShadowMapRender m_shadowMapRender;
		RenderTarget m_mainRenderTarget;
	};

	extern RenderingEngine g_renderingEngine;
}
