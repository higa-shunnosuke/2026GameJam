#pragma once
#include "Potato.h"

class RainbowPotato : public Potato
{
private:

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	RainbowPotato();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~RainbowPotato();

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

};