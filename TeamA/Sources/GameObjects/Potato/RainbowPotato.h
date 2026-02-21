#pragma once
#include "Potato.h"

class RainbowPotato : public Potato
{
private:
	float m_animeTime;
	int m_animeCount;
	int m_rainbowpotatoImage;

public:
	RainbowPotato();
	~RainbowPotato();

public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	 //<summary>
	 //更新処理
	 //</summary>
	void Update(float delta) override; //虹色の更新使うかも

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