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
	g_camera3D->SetPosition({ 0.0f, 100.0f, -200.0f });
	g_camera3D->SetTarget({ 0.0f, 50.0f, 0.0f });
	
	//���C�g
	g_sceneLight.SetEyePosition({ g_camera3D->GetPosition().x, g_camera3D->GetPosition().y, g_camera3D->GetPosition().z });
	g_sceneLight.SetDirectionColor({ 1.0f,1.0f,1.0f });
	g_sceneLight.SetAmbientLight({ 5.0f,5.0f,5.0f });

	//�u���[��
	//g_bloom.InitBloom();

	//RenderTarget.Create()�𗘗p���ă����_�����O�^�[�Q�b�g���쐬����
	RenderTarget mainRenderTarget;
	mainRenderTarget.Create(
		1600,                           //�e�N�X�`���̕�
		900,                            //�e�N�X�`���̒���
		1,                              //Mipmap���x��
		1,                              //�e�N�X�`���z��̃T�C�Y
		DXGI_FORMAT_R32G32B32A32_FLOAT, //�J���[�o�b�t�@�[�̃t�H�[�}�b�g
		DXGI_FORMAT_D32_FLOAT           //�f�v�X�e���V���o�b�t�@�[�̃t�H�[�}�b�g
	);

	g_bloom.InitRenderTarget();
	g_bloom.InitLuminanceSprite(mainRenderTarget);
	g_bloom.InitBlurSprite();
	g_bloom.InitFinalSprite();
	g_bloom.InitSprite(mainRenderTarget);

	NewGO<Game>(0, "game");

	// ��������Q�[�����[�v�B
	while (DispatchWindowMessage())
	{
		auto& renderContext = g_graphicsEngine->GetRenderContext();

		// �t���[���̊J�n���ɌĂяo���K�v�����鏈�������s
		g_k2EngineLow->BeginFrame();
		
		// �����_�����O�^�[�Q�b�g�Ƃ��ė��p�ł���܂ő҂�
		renderContext.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
		// �����_�����O�^�[�Q�b�g��ݒ�
		renderContext.SetRenderTargetAndViewport(mainRenderTarget);
		// �����_�����O�^�[�Q�b�g���N���A
		renderContext.ClearRenderTargetView(mainRenderTarget);

		// �Q�[���I�u�W�F�N�g�}�l�[�W���[�̍X�V�������Ăяo���B
		g_k2EngineLow->ExecuteUpdate();

		// �Q�[���I�u�W�F�N�g�}�l�[�W���[�̕`�揈�����Ăяo���B
		g_k2EngineLow->ExecuteRender();

		// �f�o�b�O�`�揈�������s����B
		g_k2EngineLow->DebubDrawWorld();

		renderContext.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

		//�u���[�O�̃����_�[
		g_bloom.BlurBeforeRender(renderContext);

		//�K�E�V�A���u���[�����s
		g_bloom.Blur(renderContext);

		//�u���[��̃����_�[
		g_bloom.BlurAfterRender(renderContext,mainRenderTarget);

		// �t���[���̏I�����ɌĂяo���K�v�����鏈�������s�B
		g_k2EngineLow->EndFrame();
	}

	delete g_k2EngineLow;

	return 0;
}