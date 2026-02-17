#pragma once
#include "DxLib.h"

// シングルトン化テンプレート
template <class Type>
class Singleton
{
protected:
    Singleton() = default;
    ~Singleton() = default; 

    // コピーガード
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

public:
    // インスタンス取得
    static Type& GetInstance()
    {
        static Type instance;
        return instance;
    }
};
