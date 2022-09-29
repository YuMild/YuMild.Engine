#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"

namespace  nsK2EngineLow
{
	ModelRender::ModelRender()
	{

	}

	ModelRender::~ModelRender()
	{

	}

	void ModelRender::Init(const char* filePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis)
	{
		ModelInitData initData;

		initData.m_tkmFilePath = filePath;
		initData.m_fxFilePath = "Assets/shader/model.fx";

		initData.m_expandConstantBuffer = &g_sceneLight.GetLight();
		initData.m_expandConstantBufferSize = sizeof(g_sceneLight.GetLight());

		if (animationClips == nullptr)
		{
			initData.m_vsEntryPointFunc = "VSMain";
		}
		else
		{
			initData.m_vsSkinEntryPointFunc = "VSSkinMain";
			InitSkeleton(filePath);
			initData.m_skeleton = &m_skeleton;
			InitAnimation(animationClips, numAnimationClips, enModelUpAxis);
		}

		initData.m_modelUpAxis = enModelUpAxis;
		m_model.Init(initData);
		Update();
	}

	void ModelRender::InitDrawShadowMapModel(const char* filePath)
	{
		ModelInitData shadowModelInitData;

		shadowModelInitData.m_tkmFilePath = filePath;
		shadowModelInitData.m_fxFilePath = "Assets/shader/DrawShadowMap.fx";
		shadowModelInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;

		m_drawShadowModel.Init(shadowModelInitData);
		Update();
	}

	void ModelRender::InitShadowRecieverModel(const char* filePath)
	{
		ModelInitData shadowModelInitData;

		shadowModelInitData.m_tkmFilePath = filePath;
		shadowModelInitData.m_fxFilePath = "Assets/shader/ShadowReciever.fx";
		shadowModelInitData.m_expandShaderResoruceView[0] = &g_shadowMapRender.GetRenderTarget().GetRenderTargetTexture();
		shadowModelInitData.m_expandConstantBuffer = (void*)&g_shadowMapRender.GetLightCamera().GetViewProjectionMatrix();
		shadowModelInitData.m_expandConstantBufferSize = sizeof(g_shadowMapRender.GetLightCamera().GetViewProjectionMatrix());

		m_shadowRecieverModel.Init(shadowModelInitData);
		Update();
	}

	void ModelRender::InitSkeleton(const char* filePath)
	{
		std::string skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	void ModelRender::InitAnimation(AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr) {
			m_animation.Init
			(m_skeleton,
				m_animationClips,
				m_numAnimationClips);
		}
	}

	void ModelRender::Update()
	{
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		if (m_skeleton.IsInited())
		{
			m_skeleton.Update(m_model.GetWorldMatrix());
		}

		m_animation.Progress(g_gameTime->GetFrameDeltaTime());
	}

	void ModelRender::Draw(RenderContext& renderContext)
	{
		m_model.Draw(renderContext);
	}

	void ModelRender::Draw(RenderContext& renderContext, Camera& camera)
	{
		m_model.Draw(renderContext, camera.GetViewMatrix(), camera.GetProjectionMatrix());
	}

	void ModelRender::ShadowMapDraw(RenderContext& renderContext, Camera& camera)
	{
		m_drawShadowModel.Draw(renderContext, camera.GetViewMatrix(), camera.GetProjectionMatrix());
	}

	void ModelRender::ShadowRecieverDraw(RenderContext& renderContext)
	{
		m_shadowRecieverModel.Draw(renderContext);
	}
}