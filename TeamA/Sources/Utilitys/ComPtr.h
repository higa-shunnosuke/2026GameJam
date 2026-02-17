#pragma once
#include <wrl/client.h>

/*****************************************
* 
* スマートポインタ使用時にインクルードする
* 
*****************************************/

// スマートポインタ
template<typename T> using ComPtr = Microsoft::WRL::ComPtr<T>;
