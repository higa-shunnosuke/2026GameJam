#pragma once
#include "../Utilitys/Singleton.h"
#include <unordered_map>
#include <string>
#include <vector>

class ResourceManager : public Singleton<ResourceManager>
{
private:
	std::unordered_map<std::string, std::vector<int>> image_container;
	std::unordered_map<std::string, int> sound_container;

public:
	const std::vector<int>& GetImageResource(const std::string& file_name, int all_num = 1, int num_x = 1, int num_y = 1, int size_x = 0, int size_y = 0);
	const int& GetSoundResource(const std::string& file_path);
	void UnloadAllResourceData();

private:
	void CreateImageResource(const std::string& file_path);
	void CreateImagesResource(std::string file_name, int all_num, int num_x, int num_y, int size_x, int size_y);
	void CreateSoundsResource(std::string file_path);
	void UnloadImageResourceData();
	void UnloadSoundResourceData();
};

