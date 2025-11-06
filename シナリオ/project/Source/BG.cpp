#include "BG.h"

BG::BG()
{
}

BG::~BG()
{
}

void BG::Set(std::string filename)
{
	std::string folder = "data/textures/";
	hImage = LoadGraph((folder + filename).c_str());
}

void BG::Update()
{
}

void BG::Draw()
{
	DrawGraph(0, 0, hImage, TRUE);
}
