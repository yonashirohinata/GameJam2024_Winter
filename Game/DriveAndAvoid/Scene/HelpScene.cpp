#include "HelpScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

HelpScene::HelpScene() : background_image(NULL)
{

}

HelpScene::~HelpScene()
{

}

//
void HelpScene::Initialize()
{
	//
	background_image = LoadGraph("Resource/images/Title.bmp");

	//
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmp‚ª‚ ‚è‚Ü‚¹‚ñ\n");
	}
}

//
eSceneType HelpScene::Update()
{
	//
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

//