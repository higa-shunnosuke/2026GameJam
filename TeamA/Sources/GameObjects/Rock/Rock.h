#pragma once
#include "../ObjectBase.h"

class Rock : public ObjectBase
{
private:

	int m_rockImage;	// 岩の画像

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Rock();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Rock();

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() const override;

};

