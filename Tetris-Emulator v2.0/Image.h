#pragma once
#include "Buffer.h"
#include <string>
using namespace std;

class Image
{
private:
	Buffer image;

public:
	Image();
	Image(string filename);
	Image(const Image& image);

	static Resolution FindResolution(std::string filename);
	Resolution GetResolution() const;

	void SetImage(std::string filename, Resolution resolution, size_t frame);
	void SetColor(Color color);
	void SetBackground(Color color);

	static Image GetFrameFromFile(std::string filename, Resolution resolution, size_t frame);

	void LoadToBuffer(Buffer& buffer, __COORD coord);

	void operator = (const Image& image);
};

