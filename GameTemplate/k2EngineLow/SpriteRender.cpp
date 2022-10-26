#include "k2EngineLowPreCompile.h"
#include "SpriteRender.h"

namespace nsK2EngineLow
{
	void SpriteRender::Init(const char* filePath, const float width, const float height, AlphaBlendMode alphaBlendMode)
	{
		SpriteInitData spriteInitData;
		spriteInitData.m_ddsFilePath[0] = filePath;
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";
		spriteInitData.m_width = static_cast<UINT>(width);
		spriteInitData.m_height = static_cast<UINT>(height);
		spriteInitData.m_alphaBlendMode = alphaBlendMode;
		spriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R16G16B16A16_FLOAT;
		m_sprite.Init(spriteInitData);
	}

	void SpriteRender::Draw(RenderContext& renderContext)
	{
		m_sprite.Draw(renderContext);
	}
}