#pragma once
#include "Potato.h"

class PoisonPotato : public Potato
{
private:

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PoisonPotato();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PoisonPotato();

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

};