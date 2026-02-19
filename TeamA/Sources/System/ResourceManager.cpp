#include "ResourceManager.h"
#include "DxLib.h"

const std::vector<int>& ResourceManager::GetImageResource(const std::string& file_name, int all_num, int num_x, int num_y, int size_x, int size_y)
{
	// コンテナ内に画像データが無い場合、画像読み込みを行う
	if (image_container.count(file_name) == NULL)
	{
		// 分割読み込みを行う？行わない？
		if (all_num != 1)
		{
			// 分割読み込みを行う
			CreateImagesResource(file_name, all_num, num_x, num_y, size_x, size_y);
		}
		if (all_num == 1)
		{
			// 分割読み込みを行わない
			CreateImageResource(file_name);
		}

	}

	// コンテナ内のデータを返す
	return image_container[file_name];
}

const int& ResourceManager::GetSoundResource(const std::string& file_path)
{
	// コンテナ内に指定ファイルが無ければ、生成する
	if (sound_container.count(file_path) == NULL)
	{
		// 音源の読み込みを行う
		CreateSoundsResource(file_path);
	}

	// コンテナ内のデータを返す
	return sound_container[file_path];
}

void ResourceManager::UnloadAllResourceData()
{
	UnloadImageResourceData();
	UnloadSoundResourceData();
}

void ResourceManager::CreateImageResource(const std::string& file_path)
{
	// 指定された画像ファイル読み込む
	int handle = LoadGraph(file_path.c_str());

	// エラーチェック
	if (handle == -1)
	{
		throw (file_path + "がありません\n");
	}

	// コンテナに読み込んだ画像を追加する
	image_container[file_path].push_back(handle);
}

void ResourceManager::CreateImagesResource(std::string file_name, int all_num, int num_x, int num_y, int size_x, int size_y)
{
	// 分割する画像分だけメモリを確保する
	int* handle = new int[all_num];

	// 指定された画像ファイルを分割で読み込む
	int result = LoadDivGraph(file_name.c_str(), all_num, num_x, num_y, size_x, size_y, handle);

	// エラーチェック
	if (result == -1)
	{
		throw (file_name + "がありません\n");
	}

	// コンテナに読み込んだ画像を追加する
	for (int i = 0; i < all_num; i++)
	{
		image_container[file_name].push_back(handle[i]);
	}

	// 確保したメモリを解放する
	delete[] handle;
}

void ResourceManager::CreateSoundsResource(std::string file_path)
{
	// 指定されたファイルを読み込む
	int handle = LoadSoundMem(file_path.c_str());

	// エラーチェック
	if (handle == -1)
	{
		throw (file_path + "がありません\n");
	}

	// コンテナに読み込んだ音源を追加する
	sound_container[file_path] = handle;
}

void ResourceManager::UnloadImageResourceData()
{
	// コンテナ内に画像が無ければ、処理を終了する
	if (image_container.size() == NULL)
	{
		return;
	}

	// 全ての画像を削除
	for (std::pair<std::string, std::vector<int>> value : image_container)
	{
		DeleteSharingGraph(value.second[0]);
		value.second.clear();
	}

	// コンテナを解放
	image_container.clear();
}

void ResourceManager::UnloadSoundResourceData()
{
	// コンテナ内に音源が無ければ、処理を終了する
	if (sound_container.size() == NULL)
	{
		return;
	}

	// 全ての音源を削除
	for (std::pair<std::string, int> value : sound_container)
	{
		DeleteSoundMem(value.second);
	}

	// コンテナを解放
	sound_container.clear();
}