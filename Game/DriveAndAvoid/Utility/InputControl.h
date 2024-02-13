#pragma once

#include "Vector2D.h"

//���͊Ǘ��@�\
class InputControl
{
private:
	static bool now_button[16];		//���݃t���[�����͒l
	static bool old_button[16];		//�ߋ��t���[�����͒l

	static bool now_button2[16];		//���݃t���[�����͒l
	static bool old_button2[16];		//�ߋ��t���[�����͒l
	static float trigger[2];		//���E�g���K�[���͒l
	static Vector2D stick[2];		//���E�X�e�B�b�N���͒l

public:

	

	static void Update();			//�X�V����

	//�{�^�����͎擾����
	static bool GetButton(int button);			//���������Ă����
	static bool GetButtonDown(int button);		//�������u��
	static bool GetButtonUp(int button);			//�b�����u��
	//�{�^�����͎擾����
	static bool GetButton2(int button2);			//���������Ă����
	static bool GetButtonDown2(int button2);		//�������u��
	static bool GetButtonUp2(int button2);			//�b�����u��

	//�g���K�[���͎擾����
	static float GetLeftTrigger();		//���g���K�[
	static float GetRightTrigger();		//�E�g���K�[

	//�X�e�B�b�N���͎擾����
	static Vector2D GetLeftStick();		//���X�e�B�b�N
	static Vector2D GetRightStick();	//�E�X�e�B�b�N

private:
	//�{�^���z��͈̓`�F�b�N
	static bool CheckButtonRange(int button);
	//�{�^���z��͈̓`�F�b�N
	static bool CheckButtonRange2(int button2);
};