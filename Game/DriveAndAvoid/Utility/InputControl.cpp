#include "InputControl.h"
#include "DxLib.h"

//�ÓI�����o�ϐ���`
bool InputControl::now_button[16] = {};
bool InputControl::old_button[16] = {};
bool InputControl::now_button2[16] = {};
bool InputControl::old_button2[16] = {};
float InputControl::trigger[2] = {};
Vector2D InputControl::stick[2] = {};

//���͋@�\�F�X�V����
void InputControl::Update()
{
	//XInput�R���g���[���[�̓��͒l���擾����
	XINPUT_STATE input_state = {};
	
	GetJoypadXInputState(DX_INPUT_PAD1, &input_state);
	//XInput�R���g���[���[�̓��͒l���擾����
	XINPUT_STATE input_state2 = {};

	GetJoypadXInputState(DX_INPUT_PAD2, &input_state2);

	//�{�^�����͒l�̍X�V
	for (int i = 0; i < 16; i++)
	{
		old_button[i] = now_button[i];
		old_button2[i] = now_button2[i];
		now_button[i] = (bool)input_state.Buttons[i];
		now_button2[i] = (bool)input_state2.Buttons[i];
	}

	//�g���K�[���͒l�̍X�V(0.0f�`1.0f�ɔ͈͂𐧌�����)(�v���C���[�P)
	trigger[0] = (float)input_state.LeftTrigger / (float)UCHAR_MAX;
	trigger[1] = (float)input_state.RightTrigger / (float)UCHAR_MAX;

	//�g���K�[���͒l�̍X�V(0.0f�`1.0f�ɔ͈͂𐧌�����)�i�v���C���[�Q�j
	trigger[0] = (float)input_state2.LeftTrigger / (float)UCHAR_MAX;
	trigger[1] = (float)input_state2.RightTrigger / (float)UCHAR_MAX;

	//���X�e�B�b�N���͒l�̍X�V(-1.0f�`1.0f�ɔ͈͂𐧌�����)(�v���C���[�P)
	if (input_state.ThumbLX > 0.0f)
	{
		stick[0].x = (float)input_state.ThumbLX / (float)SHRT_MAX;
	}
	else
	{
		stick[0].x = -((float)input_state.ThumbLX / (float)SHRT_MIN);
	}

	if (input_state.ThumbLY > 0.0f)
	{
		stick[0].y = (float)input_state.ThumbLY / (float)SHRT_MAX;
	}
	else
	{
		stick[0].y = -((float)input_state.ThumbLY / (float)SHRT_MIN);
	}

	//���X�e�B�b�N���͒l�̍X�V(-1.0f�`1.0f�ɔ͈͂𐧌�����)(�v���C���[�Q)
	if (input_state2.ThumbLX > 0.0f)
	{
		stick[0].x = (float)input_state2.ThumbLX / (float)SHRT_MAX;
	}
	else
	{
		stick[0].x = -((float)input_state2.ThumbLX / (float)SHRT_MIN);
	}

	if (input_state.ThumbLY > 0.0f)
	{
		stick[0].y = (float)input_state2.ThumbLY / (float)SHRT_MAX;
	}
	else
	{
		stick[0].y = -((float)input_state2.ThumbLY / (float)SHRT_MIN);
	}

	//�E�X�e�B�b�N���͒l�̍X�V(-1.0f�`1.0f�ɔ͈͂𐧌�����)(�v���C���[�P)
	if (input_state.ThumbLX > 0.0f)
	{
		stick[1].x = (float)input_state.ThumbRX / (float)SHRT_MAX;
	}
	else
	{
		stick[1].x = -((float)input_state.ThumbRX / (float)SHRT_MIN);
	}

	if (input_state.ThumbLY > 0.0f)
	{
		stick[1].y = (float)input_state.ThumbRY / (float)SHRT_MAX;
	}
	else
	{
		stick[1].y = -((float)input_state.ThumbRY / (float)SHRT_MIN);
	}
	//�E�X�e�B�b�N���͒l�̍X�V(-1.0f�`1.0f�ɔ͈͂𐧌�����)(�v���C���[�Q)
	if (input_state2.ThumbLX > 0.0f)
	{
		stick[1].x = (float)input_state2.ThumbRX / (float)SHRT_MAX;
	}
	else
	{
		stick[1].x = -((float)input_state2.ThumbRX / (float)SHRT_MIN);
	}

	if (input_state.ThumbLY > 0.0f)
	{
		stick[1].y = (float)input_state2.ThumbRY / (float)SHRT_MAX;
	}
	else
	{
		stick[1].y = -((float)input_state2.ThumbRY / (float)SHRT_MIN);
	}
}

//�{�^���擾�F�����Ă��(�v���C���[�P)
bool InputControl::GetButton(int button)
{
	return CheckButtonRange(button) && (now_button[button] && old_button[button]);
}

//�{�^���擾�F�������u��(�v���C���[�P)
bool InputControl::GetButtonDown(int button)
{
	return CheckButtonRange(button) && (now_button[button] && !old_button[button]);
}

//�{�^���擾�F�������u��(�v���C���[�P)
bool InputControl::GetButtonUp(int button)
{
	return CheckButtonRange(button) && (!now_button[button] && old_button[button]);
}
//�{�^���擾�F�����Ă��(�v���C���[2)
bool InputControl::GetButton2(int button2)
{
	return CheckButtonRange2(button2) && (now_button2[button2] && old_button2[button2]);
}

//�{�^���擾�F�������u��(�v���C���[�Q)
bool InputControl::GetButtonDown2(int button2)
{
	return CheckButtonRange2(button2) && (now_button2[button2] && !old_button2[button2]);
}

//�{�^���擾�F�������u��(�v���C���[�Q)
bool InputControl::GetButtonUp2(int button2)
{
	return CheckButtonRange2(button2) && (!now_button2[button2] && old_button2[button2]);
}

//���g���K�[�擾
float InputControl::GetLeftTrigger()
{
	return trigger[0];
}

//�E�g���K�[�擾
float InputControl::GetRightTrigger()
{
	return trigger[1];
}

//���X�e�B�b�N�擾
Vector2D InputControl::GetLeftStick()
{
	return stick[0];
}

//�E�X�e�B�b�N�擾
Vector2D InputControl::GetRightStick()
{
	return stick[1];
}



//�{�^���z��͈̓`�F�b�N
bool InputControl::CheckButtonRange(int button)
{
	return (0 <= button && button < 16);
}

//�{�^���z��͈̓`�F�b�N
bool InputControl::CheckButtonRange2(int button2)
{
	return (0 <= button2 && button2 < 16);
}

