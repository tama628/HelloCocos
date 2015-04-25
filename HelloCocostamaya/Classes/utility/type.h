#pragma once

// C define
// null pointer
#ifndef NULL
#define NULL		(0)
#endif
// boolean
#ifndef TRUE
#define FALSE		(0)
#define TRUE		(1)
typedef int			BOOL;
#endif

// C++11 keyword
#if 0
#define nullptr		NULL	// ヌルポインタ
#define override			// 関数のオーバーライドを明示
#define final				// 関数のオーバーライド禁止
#endif

// 型定義
#include <cstdint>
typedef int8_t		s8;
typedef uint8_t		u8;
typedef int16_t		s16;
typedef uint16_t	u16;
typedef int32_t		s32;
typedef uint32_t	u32;
typedef int64_t		s64;
typedef uint64_t	u64;
typedef float		f32;
typedef double		f64;

// ポインタを整数として扱う型
typedef intptr_t	sptr;
typedef uintptr_t	uptr;
