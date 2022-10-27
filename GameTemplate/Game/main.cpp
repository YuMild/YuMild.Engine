#include "stdafx.h"
#include "system/system.h"
#include "Game.h"

// K2EngineLow�̃O���[�o���A�N�Z�X�|�C���g�B
K2EngineLow* g_k2EngineLow = nullptr;

/// <summary>
/// ���C���֐�
/// </summary>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// �Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	// k2EngineLow�̏������B
	g_k2EngineLow = new K2EngineLow();
	g_k2EngineLow->Init(g_hWnd, FRAME_BUFFER_W, FRAME_BUFFER_H);
	
	//���C�g
	g_sceneLight.SetEyePosition({ g_camera3D->GetPosition().x, g_camera3D->GetPosition().y, g_camera3D->GetPosition().z });
	g_sceneLight.SetDirectionColor({ 1.0f,1.0f,1.0f });

	g_renderingEngine.Init();
	g_postEffect.Init();
	g_bloom.Init();

	NewGO<Game>(0, "game");

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		auto& renderContext = g_graphicsEngine->GetRenderContext();

		//�t���[���̊J�n���ɌĂяo���K�v�����鏈�������s
		g_k2EngineLow->BeginFrame();
		
		//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̍X�V����
		g_k2EngineLow->ExecuteUpdate();

		//���f���̕`��
		g_renderingEngine.Execute(renderContext);

		//�|�X�g�G�t�F�N�g
		g_postEffect.Render(renderContext);

		//�f�o�b�O�`�揈�������s
		g_k2EngineLow->DebubDrawWorld();

		//�t���[���̏I�����ɌĂяo���K�v�����鏈�������s
		g_k2EngineLow->EndFrame();
	}

	delete g_k2EngineLow;

	return 0;
}