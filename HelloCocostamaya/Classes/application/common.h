#pragma once

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
// Windowsでは文字列リテラルがshift-jisで埋め込まれるので
// utf-8に変更する
#pragma execution_character_set("utf-8")
#endif

#include "../AppConst.h"

#include "utility/type.h"
#include "utility/cc/cc.h"

#include "SceneCreator.h"
