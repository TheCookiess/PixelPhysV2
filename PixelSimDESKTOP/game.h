#pragma once

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <vector>
#include <ranges>

#include "cell.h"
#include "interfaceData.h"

class Game
{
public:
	Game();
	~Game();

	void init(std::vector<GLubyte> texData, int textureW, int textureH, int scale);
	void reload(std::vector<GLubyte> texData, int textureW, int textureH);
	void reset(int CellTypeID, bool& resetSim);
	void update(interfaceData& data);
	void cellUpdate(Cell& p);

	void createCell(int range, bool flag, int texIdx, int x, int y, int CellTypeID);
	void updatePixel(int x, int y, int r, int g, int b, int a);
	void updatePixel(Cell& c);
	
	CellType varyPixelColour(int range, int CellTypeID);
	void mouseDraw(int x, int y, int radius, int chance, int CellTypeID, int CellDrawShape, int range);

	void changeCellType(int x, int y, int CellTypeID, int range);
	//void swapCells(int x1, int y1, int x2, int y2);
	void swapCells(Cell& p1, Cell& p2);
	//bool checkDensity(int x1, int y1, int x2, int y2);
	bool checkDensity(Cell& p1, int delX, int delY);

	void updateSand(Cell& c);
	void updateWater(Cell& c);

	inline bool outOfBounds(int x, int y) { return (x >= cellW || x < 0 || y >= cellH || y < 0); }
	//inline int cellIdx(int x, int y) { return (outOfBounds(x,y)) ? (y * texW) + x : 0; }
	inline int cellIdx(int x, int y) { return (y * cellW) + x; }
	inline int texIdx(int x, int y) { return 4 * (y * texW + x); }
	inline std::vector<GLubyte> getTextureData() { return textureData; }

private:
	int texW, texH, cellScale, cellW, cellH;	
	std::vector<Cell> cells;
	std::vector<GLubyte> textureData;
	CellType Types[4];
	CellType AIR, SAND, WATER, CONCRETE;
};