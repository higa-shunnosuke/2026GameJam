#include "SceneManager.h"
#include "SceneFactory.h"
#include "../System/InputManager.h"
#include <Windows.h>

// コンストラクタ
SceneManager::SceneManager()
	: currentScene(nullptr)
	, fontHandle()
{
}

// 初期化処理
void SceneManager::Initialize()
{
	// 最初のシーンをインゲーム画面にする
	ChangeScene(SceneType::load);

	// フォントデータを読み込む
	AddFontResourceExA("Assets/Fonts/07にくまるフォント.otf", FR_PRIVATE, NULL);

	// フォントハンドルの作成
	fontHandle = CreateFontToHandle("07にくまるフォント", 20, 3, DX_FONTTYPE_ANTIALIASING);

	// 描画する文字列の文字セットを変更
	ChangeFont("07にくまるフォント");
}

//  更新処理
bool SceneManager::Update(float delta)
{
	//インスタンス取得
	InputManager& input = InputManager::GetInstance();
	//コントローラーの入力値更新
	input.Update();	

	// シーンの更新
	SceneType nextSceneType = currentScene->Update(delta);

	// 描画処理
	Draw();

	// 現在のシーンタイプが次のシーンタイプと違っているか？
	if (currentScene->GetNowSceneType() != nextSceneType)
	{
		// シーン切り替え処理
		ChangeScene(nextSceneType);
	}

	return true;
}

// 終了時処理
void SceneManager::Finalize()
{
	// シーン情報が生成されていれば、削除する
	if (currentScene != nullptr)
	{
		currentScene->Finalize();
		delete currentScene;
		currentScene = nullptr;
	}

	// 作成したフォントハンドルを削除する
	DeleteFontToHandle(fontHandle);
}

// 描画処理
void SceneManager::Draw() const
{
	// 画面の初期化
	ClearDrawScreen();

	// シーンの描画処理
	currentScene->Draw();

	// 裏画面の内容を表画面に反映する
	ScreenFlip();
}

// シーン切り替え処理
void SceneManager::ChangeScene(SceneType nextType)
{
	// 次のシーンを生成する
	SceneBase* next_scene = SceneFactory::CreateScene(nextType);

	// エラーチェック
	if (next_scene == nullptr)
	{
		throw ("シーンが生成できませんでした\n");
	}
	
	// データを受け渡す
	PlayData nextData{};
	if (currentScene)
	{
		nextData = currentScene->TransitionData(nullptr);
	}
	if (next_scene)
	{
		next_scene->TransitionData(&nextData);
	}

	// シーン情報が格納されていたら、削除する
	if (currentScene != nullptr)
	{
		currentScene->Finalize();
		delete currentScene;
	}

	// 次のシーンの初期化
	next_scene->Initialize();

	// 現在シーンの上書き
	currentScene = next_scene;
}