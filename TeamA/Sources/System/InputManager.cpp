#include "InputManager.h"
#include "DxLib.h"

/// <summary>
/// 更新処理
/// </summary>
void InputManager::Update()
{
	// キー入力値の更新
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));
	GetHitKeyStateAll(now_key);

	// コントローラー入力値の更新
	XINPUT_STATE input = {};
	GetJoypadXInputState(DX_INPUT_PAD1, &input);
	for (int i = 0; i < D_BUTTON_MAX; i++)
	{
		old_button[i] = now_button[i];
		now_button[i] = static_cast<bool>(input.Buttons[i]);
	}
	trigger[0] = TriggerNormalize(input.LeftTrigger);
	trigger[1] = TriggerNormalize(input.RightTrigger);
	stick[0].x = StickNormalize(input.ThumbLX);
	stick[0].y = StickNormalize(input.ThumbLY);
	stick[1].x = StickNormalize(input.ThumbRX);
	stick[1].y = StickNormalize(input.ThumbRY);
}

/// <summary>
/// キーボードの入力状態を確認する
/// </summary>
/// <param name="button">割り当てられたキー</param>
/// <returns>押した瞬間：Pressed、押している間：Hold、離した瞬間：Released</returns>
eInputState InputManager::GetKeyState(int keycode) const
{
	if (CheckKeyCodeRange(keycode))
	{
		if (old_key[keycode] == TRUE)
		{
			if (now_key[keycode] == TRUE)
			{
				return eInputState::Hold;
			}
			else
			{
				return eInputState::Released;
			}
		}
		else
		{
			if (now_key[keycode] == TRUE)
			{
				return eInputState::Pressed;
			}
			else
			{
				return eInputState::None;
			}
		}
	}
	return eInputState::None;
}

/// <summary>
/// コントローラーの入力状態を確認する
/// </summary>
/// <param name="button">割り当てられたボタン</param>
/// <returns>押した瞬間：Pressed、押している間：Hold、離した瞬間：Released</returns>
eInputState InputManager::GetButtonState(int button) const
{
	if (CheckButtonRange(button))
	{
		if (old_button[button] == TRUE)
		{
			if (now_button[button] == TRUE)
			{
				return eInputState::Hold;
			}
			else
			{
				return eInputState::Released;
			}
		}
		else
		{
			if (now_button[button] == TRUE)
			{
				return eInputState::Pressed;
			}
			else
			{
				return eInputState::None;
			}
		}
	}
	return eInputState::None;
}

/// <summary>
/// 左トリガー入力状態取得
/// </summary>
/// <returns>左トリガー入力状態(0.0f～1.0f)</returns>
float InputManager::GetLeftTrigger() const
{
	return trigger[0];
}

/// <summary>
/// 右トリガー入力状態取得
/// </summary>
/// <returns>右トリガー入力状態(0.0f～1.0f)</returns>
float InputManager::GetRightTrigger() const
{
	return trigger[1];
}

/// <summary>
/// 左スティック入力状態取得
/// </summary>
/// <returns>左スティック入力状態(-1.0f～1.0f)</returns>
Vector2D InputManager::GetLeftStick() const
{
	return stick[0];
}

/// <summary>
/// 右スティック入力状態取得
/// </summary>
/// <returns>右スティック入力状態(-1.0f～1.0f)</returns>
Vector2D InputManager::GetRightStick() const
{
	return stick[1];
}

/// <summary>
/// トリガー入力値の正規化
/// </summary>
/// <param name="value">トリガー入力値</param>
/// <returns>入力値を正規化した値</returns>
float InputManager::TriggerNormalize(unsigned char value)
{
	float result = 0.0f;

	result = (float)value / (float)UCHAR_MAX;

	return result;
}

/// <summary>
/// スティック入力値の正規化
/// </summary>
/// <param name="value">スティック入力値</param>
/// <returns>入力値を正規化した値</returns>
float InputManager::StickNormalize(short value)
{
	float result = 0.0f;

	if (value >= 0)
	{
		result = (float)value / (float)SHRT_MAX;
	}
	else
	{
		result = -((float)value / (float)SHRT_MIN);
	}

	return result;
}

/// <summary>
/// 割り当てキーコード範囲内チェック処理
/// </summary>
/// <param name="button">割り当てられたキーコード</param>
/// <returns>範囲内なら、true</returns>
bool InputManager::CheckKeyCodeRange(int key_code) const
{
	return (0 <= key_code && key_code < D_KEYCODE_MAX);
}

/// <summary>
/// 割り当てボタン範囲内チェック処理
/// </summary>
/// <param name="button">割り当てられたボタン</param>
/// <returns>範囲内なら、true</returns>
bool InputManager::CheckButtonRange(int button) const

{
	return (0 <= button && button < D_BUTTON_MAX);
}

eInputState InputManager::ApplyOneInput(int getInput[], int getInputSize)
{
	GetInstance();

	for (int i = 0;i < getInputSize;i++)
	{
		// もし、対応入力のうち、どれか一つでもHoldなら
		if (GetKeyState(getInput[i]) == eInputState::Hold || GetButtonState(getInput[i]) == eInputState::Hold)
		{
			// 変数にHoldを当てはめる
			return eInputState::Hold;
		}
	}

	for (int i = 0;i < getInputSize;i++)
	{
		// もし、対応入力のうち、どれか一つでもPressedなら
		if (GetKeyState(getInput[i]) == eInputState::Pressed || GetButtonState(getInput[i]) == eInputState::Pressed)
		{
			// 前フレームで別の対応ボタンが押されているなら
			for (int i = 0;i < getInputSize;i++)
			{
				if (GetKeyState(getInput[i]) == eInputState::Released || GetButtonState(getInput[i]) == eInputState::Released)
				{
					return eInputState::Hold;
				}
			}
			return eInputState::Pressed;
		}
	}

	for (int i = 0;i < getInputSize;i++)
	{
		// もし、対応入力のうち、どれか一つでもReleasedなら
		if (GetKeyState(getInput[i]) == eInputState::Released || GetButtonState(getInput[i]) == eInputState::Released)
		{
			return eInputState::Released;
		}
	}

	for (int i = 0;i < getInputSize;i++)
	{
		// 変数にNoneを当てはめる
		return eInputState::None;
	}
}

void InputManager::TitleApplyInput(eInputState& left, eInputState& right, eInputState& decision)
{
	int getInput[3];

	getInput[0] = XINPUT_BUTTON_DPAD_LEFT;
	getInput[1] = KEY_INPUT_LEFT;
	getInput[2] = KEY_INPUT_A;
	left = ApplyOneInput(getInput, 3);

	getInput[0] = XINPUT_BUTTON_DPAD_RIGHT;
	getInput[1] = KEY_INPUT_RIGHT;
	getInput[2] = KEY_INPUT_D;
	right = ApplyOneInput(getInput, 3);

	getInput[0] = XINPUT_BUTTON_A;
	getInput[1] = XINPUT_BUTTON_B;
	getInput[2] = KEY_INPUT_SPACE;
	decision = ApplyOneInput(getInput, 3);
}