#pragma once
#include "Buffer.h"
#include "Image.h"
#include <vector>
#include <string>
using namespace std;

class Animation
{
private:
	vector<Image> frames;

public:
	Animation();
	Animation(string filename, size_t framesCount);

	void SetColor(Color color, size_t frame);
	void SetBackground(Color color, size_t frame);
	void SetColor(Color color);
	void SetBackground(Color color);

	void SetAnimation(string filename, size_t framesCount);
	void AddFrame(Image image);

	Image& GetFrame(size_t index);
	size_t GetFramesCount() const;
	static size_t GetFramesCount(string filename);

	void LoadFrameToBuffer(Buffer& buffer, __COORD coord, size_t frame);
};

