#pragma once
#include "../ObjectBase.h"

#include "../../Utilitys/Vector2D.h"

class PotatoPlant : public ObjectBase
{
private:
	int m_leavesnekkoImages[3]; // 葉っぱと根っこの画像
	int m_plantType;			// プラントの種類

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	PotatoPlant();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~PotatoPlant();


public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() const override;

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize() override;

private:

	/// <summary>
	/// ポテトの生成位置を決定し、生成処理を実行する
	/// </summary>
	void SpawnPotatoAtDecidedPosition();

	/// <summary>
	/// 指定座標にランダムな種類のポテトを生成する
	/// </summary>
	/// <param name="position">生成座標</param>
	void SpawnRandomPotato(const Vector2D& position);
};