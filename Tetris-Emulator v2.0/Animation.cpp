#include "Animation.h"
#include <iostream>
#include <fstream>
using namespace std;

Animation::Animation()
{
	// empty
}

Animation::Animation(string filename, size_t framesCount)
{
	SetAnimation(filename, framesCount);
}

void Animation::SetColor(Color color, size_t frame)
{
	if (frame < frames.size())
		frames[frame].SetColor(color);
}

void Animation::SetBackground(Color color, size_t frame)
{
	if (frame < frames.size())
		frames[frame].SetBackground(color);
}

void Animation::SetColor(Color color)
{
	for (size_t i = 0; i < frames.size(); i++)
		frames[i].SetColor(color);
}

void Animation::SetBackground(Color color)
{
	for (size_t i = 0; i < frames.size(); i++)
		frames[i].SetBackground(color);
}

void Animation::SetAnimation(string filename, size_t framesCount)
{
	for (size_t i = 0; i <= framesCount; i++)
	{
		frames.push_back(Image::GetFrameFromFile(filename, Image::FindResolution(filename), i));
	}
}

void Animation::AddFrame(Image image)
{
	frames.push_back(image);
}

Image& Animation::GetFrame(size_t index)
{
	if (index <= GetFramesCount())
		return this->frames[index];
	return this->frames[0];
}

size_t Animation::GetFramesCount() const
{
	return this->frames.size();
}

size_t Animation::GetFramesCount(string filename)
{
	if (filename.empty())
	{
		cout << "Error! Filename is empty!\n";
		return 0;
	}
	fstream fread(filename);
	if (!fread.is_open())
	{
		cout << "Error! File not opened!\n";
		return 0;
	}

	char symbol;
	int counter = -1;
	while ((symbol = fread.get()) != EOF)
	{
		if (symbol == '@')
			counter++;
	}

	if (counter > 0)
		return counter;
	return 0;
}

void Animation::LoadFrameToBuffer(Buffer& buffer, __COORD coord, size_t frame)
{
	if (frame < frames.size())
	{
		frames[frame].LoadToBuffer(buffer, coord);
	}
}