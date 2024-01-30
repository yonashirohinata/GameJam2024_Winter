#include "SceneManager.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "TitleScene.h"
#include  "GameMainScene.h"
#include "ResultScene.h"
#include "HelpScene.h"
#include "RankingDispScene.h"
#include "RankingInputScene.h"

SceneManager::SceneManager() : current_scene(nullptr)
{

}

SceneManager::~SceneManager()
{

}

//
void SceneManager::Initialize()
{
	//
	SetMainWindowText("Drive&Avoid");

	//
	if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK)
	{
		throw("�E�B���h�E���[�h�ŋN���ł��܂���ł���\n");
	}

	//
	if (DxLib_Init() == -1)
	{
		throw("Dx���C�u�������������o���܂���ł���\n");
	}

	//
	if (SetDrawScreen(DX_SCREEN_BACK) == -1)
	{
		throw("�`���̎w�肪�ł��܂���ł���\n");
	}

	//
	ChangeScene(eSceneType::E_TITLE);
}

//
void SceneManager::Update()
{
	//
	LONGLONG start_time = GetNowHiPerformanceCount();

	//
	while (ProcessMessage() != -1)
	{
		//
		LONGLONG now_time = GetNowHiPerformanceCount();

		//
		if ((now_time - start_time) >= DELTA_SECOND)
		{
			//
			start_time = now_time;

			//
			InputControl::Update();

			//
			eSceneType next = current_scene->Update();

			//
			Draw();

			//
			if (next == eSceneType::E_END)
			{
				break;
			}

			//
			if (next != current_scene->GetNowScene())
			{
				ChangeScene(next);
			}
		}

		//
		if (CheckHitKey(KEY_INPUT_ESCAPE) || InputControl::GetButtonUp(XINPUT_BUTTON_BACK))
		{
			break;
		}
	}
}

//
void SceneManager::Finalize()
{
	//
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}

	//
	DxLib_End();
}

//
void SceneManager::Draw() const
{
	//
	ClearDrawScreen();

	//
	current_scene->Draw();

	//
	ScreenFlip();
}

//
void SceneManager::ChangeScene(eSceneType scene_type)
{
	//
	SceneBase* new_scene = dynamic_cast<SceneBase*>(CreateScene(scene_type));

	//
	if (new_scene == nullptr)
	{
		throw("�V�[���������ł��܂���ł����B\n");
	}

	//
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	//
	new_scene->Initialize();

	//
	current_scene = new_scene;
}

//
SceneBase* SceneManager::CreateScene(eSceneType scene_type)
{
	//
	switch (scene_type)
	{
	case eSceneType::E_TITLE:
		return new TitleScene;

	case eSceneType::E_MAIN:
		return new GameMainScene;

	case eSceneType::E_RESULT:
		return new ResultScene;

	case eSceneType::E_HELP:
		return new HelpScene;

	case eSceneType::E_RANKING_DISP:
		return new RankingDispScene;

	case eSceneType::E_RANKING_INPUT:
		return new RankingInputScene;
	default:
		return nullptr;
	}
}