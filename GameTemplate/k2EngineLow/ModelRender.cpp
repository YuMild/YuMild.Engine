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
		int draw,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis,
		Texture* emission)
	{
		ModelInitData initData;
		initData.m_tkmFilePath = filePath;

		//Draw
		if (draw == Normal)
		{
			initData.m_fxFilePath = "Assets/shader/model.fx";
			initData.m_expandConstantBuffer = &g_sceneLight.GetLight();
			initData.m_expandConstantBufferSize = sizeof(g_sceneLight.GetLight());
		}
		else if (draw == Dithering)
		{
			initData.m_fxFilePath = "Assets/shader/dithering.fx";
			initData.m_expandConstantBuffer = &g_sceneLight.GetLight();
			initData.m_expandConstantBufferSize = sizeof(g_sceneLight.GetLight());
		}

		//Animation
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

		//Emission
		if (emission != nullptr)
		{
			initData.m_expandShaderResoruceView[2] = emission;
		}

		initData.m_modelUpAxis = enModelUpAxis;
		m_model.Init(initData);
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
		g_renderingEngine.AddModelRenderObject(this);
		m_model.Draw(renderContext);
	}
}