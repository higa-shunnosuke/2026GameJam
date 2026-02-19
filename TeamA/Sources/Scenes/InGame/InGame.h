#pragma once
#include "../SceneBase.h"
#include "../../GameObjects/ObjectManager.h"
#include "../../GameObjects/Player/Player.h"
#include "../../GameObjects/Jewel/Jewel.h"


class InGame : public SceneBase
{
private:
	Player* player;
	Jewel* jewel;
	std::vector<std::vector<char>> m_mapData;

	int groundImage;	// 地面の画像

public:
	// コンストラクタ
	InGame();

	// デストラクタ
	virtual ~InGame() = default;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	/// <returns>現在のシーンタイプ</returns>
	virtual SceneType Update(float delta) override;

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() const override;

	/// <summary>
	/// 終了
	/// </summary>
	virtual void Finalize() override;

	/// <summary>
	/// 現在のシーンタイプを取得
	/// </summary>
	/// <returns>現在のシーンタイプ</returns>
	virtual const SceneType GetNowSceneType() const override;

private:

	/// <summary>
	/// マップcsvの読み込み
	/// </summary>
	void LoadMapCsv();
};