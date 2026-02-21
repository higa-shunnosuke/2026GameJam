#pragma once
#include "../ObjectBase.h"

class Potato : public ObjectBase
{
protected:

	int m_potatoImage;	// ポテトの画像

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Potato();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Potato();

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() const override;

public:

	/// <summary>
	/// 判定処理
	/// </summary>
	/// <param name="other"></param>
	void OnHitCollision(ObjectBase& other) override;
};

