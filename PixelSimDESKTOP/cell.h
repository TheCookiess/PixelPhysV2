#pragma once
#include "pch.h"

namespace MaterialID { // Scope blocked Enum for safety.
	enum : u8 {
		EMPTY,
		SAND,
		WATER,
		CONCRETE,
		GOL_ALIVE,
		COUNT,
	};

	static const std::vector<std::string> names = {
		"EMPTY",
		"SAND",
		"WATER",
		"CONCRETE",
		"Game of Life: Alive",
	};
};

struct Material
{
	u8 r, g, b, a;
	u16 d;
	std::vector<std::vector<u8>> variants;

	Material(u8 RED, u8 GREEN, u8 BLUE, u8 ALPHA, u16 DENSITY)
	{
		r = RED;
		g = GREEN;
		b = BLUE;
		a = ALPHA;
		d = DENSITY;
		variants = { {RED,GREEN,BLUE,ALPHA} };
	}
	Material() = default;
};

struct Cell
{	// 32 bits of data, for more cache hits === speed.
	u8 matID;
	bool updated;	// uses 1 byte??? should just be a bit 
	u8 variant;		// index to array of randomly generated RGBA values from material's RGBA.
	u8 data;		// extra data if needed, e.g fire temp

	Cell(u8 MATERIAL, u8 UPDATED, u8 COLOUR_VARIANT, u8 EXTRA_DATA)
	{
		matID = MATERIAL;
		updated = UPDATED;
		variant = COLOUR_VARIANT;
		data = EXTRA_DATA;
	}
	Cell() = default;
};