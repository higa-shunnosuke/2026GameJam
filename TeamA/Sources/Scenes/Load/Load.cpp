#include "Load.h"
#include "../../System/ResourceManager.h"

// コンストラクタ
Load::Load():
	count(),
	size(),
	is_complete(false),
	next_scene(nullptr)
{

}

// デストラクタ
Load::~Load()
{

}

// 初期化処理
void Load::Initialize()
{
	count = 0;
	size = (int)load_list.size();
	is_complete = false;
}

// 更新処理
SceneType Load::Update(float delta)
{
	// 1フレームごとに1つずつロード
	if (count < size)
	{
		// リソースマネージャーのポインタ
		ResourceManager& rm = ResourceManager::GetInstance();
		// 読み込むファイル
		LoadItem item = load_list[count];

		// 画像の読み込み
		if (item.type == "Sprites/" || item.type == "Textures/")
		{
			// ファイルパス
			std::string Path = "Assets/" + item.type + item.path + ".PNG";

			if (!rm.GetImageResource(Path.c_str())[0])
			{
				// エラー処理
				MessageBoxA(NULL, "画像の読込みに失敗しました", "エラー", MB_OK);
			}
			
		}
		// 音源の読み込み
		else if (item.type == "Sounds/")
		{
			// ファイルパス
			std::string Path = "Assets/" + item.type + item.path + ".mp3";

			if (!rm.GetSoundResource(Path.c_str()))
			{
				// エラー処理
				MessageBoxA(NULL, "音源の読込みに失敗しました", "エラー", MB_OK);
			}
		}

		count++;
	}
	else if (!is_complete)
	{
		// ロード完了
		is_complete = true;

		// タイトルシーンへ遷移
		return SceneType::title;
	}

	// 現在のシーン情報を返却する
	return GetNowSceneType();
}

// 描画処理
void Load::Draw() const
{
	// UI描画
	SetFontSize(48);
	DrawString(500, 630, "Now Loading...", GetColor(255, 255, 255));

	// バーの描画
	float rate = (float)count / size;
	int barWidth = 400;
	int barHeight = 20;
	int x = 50;
	int y = 720 - barHeight-50;
	DrawBox(x, y, x + barWidth, y + barHeight, GetColor(100, 100, 100), TRUE);         // 背景
	DrawBox(x, y, x + (int)(barWidth * rate), y + barHeight, GetColor(0, 255, 0), TRUE); // 緑の進捗
	DrawBox(x, y, x + barWidth, y + barHeight, GetColor(255, 255, 255), FALSE);         // 枠線
}

// 終了処理
void Load::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

// 現在のシーンタイプ取得処理
const SceneType Load::GetNowSceneType() const
{
	return SceneType::load;
}

// 次のシーンタイプ設定処理
void Load::SetNextSceneType(SceneBase* next_scene)
{
	this->next_scene = next_scene;
}