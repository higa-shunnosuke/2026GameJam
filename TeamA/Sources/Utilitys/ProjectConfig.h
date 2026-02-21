#pragma once

#include <string>

/**********************************************************
* マクロ定義
***********************************************************/
#define	D_SUCCESS		(0)		// 成功
#define	D_FAILURE		(-1)	// 失敗

#define D_WIN_WIDTH		(1280)	// スクリーンの横幅
#define D_WIN_HEIGHT	(720)	// スクリーンの縦幅
#define D_COLOR_BIT		(32)	// カラービット
#define D_BOX_SIZE		(128)	// ボックスサイズ
#define D_BOX_COUNT		(15)	// ボックスカウント
#define D_BOX_OFFSET	(3)		// ボックスオフセット
#define D_START_Y		(7)		// スタート地点のグリッドy

#define D_STAGE_WIDTH	(D_BOX_SIZE * D_BOX_COUNT)		// ステージ横幅
#define D_STAGE_HEIGHT	(D_BOX_SIZE * (D_BOX_COUNT + D_BOX_OFFSET))// ステージ縦幅


/**********************************************************
* プロトタイプ宣言
***********************************************************/
// エラー内容を出力する
int ErrorThrow(std::string error_log);
