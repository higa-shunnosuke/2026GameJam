#pragma once

#include "../SceneBase.h"

struct LoadItem {
	std::string type;	// 使用用途
	std::string path;	// ファイルパス
};

// ローディングシーン
class Load :public SceneBase
{
private:
	SceneBase* next_scene;	// 次のシーン情報
	int count;				// 読み込んだアイテムの数
	int size;				// 読み込むアイテムの数
	bool is_complete;		// 読み込み完了フラグ

	// ロードリスト
	std::vector<LoadItem> load_list = {
		
		//------------------------------
		// 画像
		//------------------------------
		
		// タイトル
		{"Sprites","Title/Title"},

		// インゲーム
		// 背景
		{"Textures/","InGame/Ground"},
		{"Textures/","InGame/Sky1"},
		{"Textures/","InGame/Sky2"},
		{"Textures/","InGame/Sky3"},
		// UI
		{"Sprites/","UI/Board"},
		{"Sprites/","UI/Timer"},
		{"Sprites/","UI/Stamina1"},
		{"Sprites/","UI/Stamina2"},
		{"Sprites/","UI/Stamina3"},
		{"Sprites/","UI/Frame1"},
		{"Sprites/","UI/Frame2"},
		{"Sprites/","UI/Mole1"},
		{"Sprites/","UI/Mole2"},
		{"Sprites/","UI/Mole3"},
		// オブジェクト
		{"Sprites/","Jewel/emerald/emerald1"},
		{"Sprites/","Jewel/emerald/emerald2"},
		{"Sprites/","Jewel/emerald/emerald3"},
		{"Sprites/","Jewel/emerald/emerald4"},
		{"Sprites/","Jewel/effect/キラキラ１"},
		{"Sprites/","Jewel/effect/キラキラ２"},
		{"Sprites/","Jewel/effect/キラキラ３"},
		{"Sprites/","soil/soil0"},
		{"Sprites/","soil/soil1"},
		{"Sprites/","soil/soil2"},
		{"Sprites/","soil/soil3"},
		{"Sprites/","Player/Idle1"},
		{"Sprites/","Player/Walk1"},
		{"Sprites/","Player/Walk2"},
		{"Sprites/","Player/Up1"},
		{"Sprites/","Player/Up2"},
		{"Sprites/","Player/Up3"},
		{"Sprites/","Player/Down1"},
		{"Sprites/","Player/Down2"},
		{"Sprites/","Player/Down3"},
		{"Sprites/","Drill/Drill1"},
		{"Sprites/","Drill/Drill2"},
		{"Sprites/","Drill/Drill3"},
		{"Sprites/","Drill/Up1"},
		{"Sprites/","Drill/Up2"},
		{"Sprites/","Drill/Up3"},
		{"Sprites/","Effect/Effect1"},
		{"Sprites/","Effect/Effect2"},
		{"Sprites/","Effect/Effect3"},
		{"Sprites/","Potato/PoisonPotato"},
		{"Sprites/","Potato/NormalPotato"},
		{"Sprites/","Potato/RainbowPotato"},
		{"Sprites/","Potato/Leaves_Nekko1"},
		{"Sprites/","Potato/Leaves_Nekko2"},
		{"Sprites/","Potato/Leaves_Nekko3"},
		{"Sprites/","Rock/Rock"}

		//------------------------------
		// 音源
		//------------------------------	
	};

public:
	// コンストラクタ
	Load();
	// デストラクタ
	virtual ~Load();

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second">1フレーム当たりの時間</param>
	/// <returns>次のシーンタイプ情報</returns>
	virtual SceneType Update(float delta) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() const override;

	/// <summary>
	/// 終了時処理
	/// </summary>
	virtual void Finalize() override;

	/// <summary>
	/// 現在のシーンタイプ情報を取得する
	/// </summary>
	/// <returns>現在のシーンタイプ</returns>
	virtual const SceneType GetNowSceneType() const override;

	/// <summary>
	/// 次のシーンタイプ設定処理
	/// </summary>
	void SetNextSceneType(SceneBase* next_scene);
};

