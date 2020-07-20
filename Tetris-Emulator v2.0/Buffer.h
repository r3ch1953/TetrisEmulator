#pragma once

enum Color
{
	BLACK,
	BLUE,
	GREEN,
	AQUA,
	RED,
	PURPULE,
	YELLOW,
	WHITE,
	GRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTAQUA,
	LIGHTRED,
	LIGHTPURPULE,
	LIGHTYELLOW,
	BRIGHTWHITE
};

struct Resolution
{
	size_t height;
	size_t width;
};

struct __COORD
{
	size_t y;
	size_t x;
};

struct Pixel
{
	char symbol;
	Color color = Color::WHITE;
	Color background = Color::BLACK;
};

class Buffer
{
private:
	Resolution resolution;
	Pixel** buffer = nullptr;

public:
	Buffer();
	Buffer(Resolution resolution);
	Buffer(const Buffer& buffer);
	~Buffer();

	Resolution GetResolution() const;
	size_t GetWidth() const;
	size_t GetHeight() const;
	Pixel GetPixel(__COORD coord) const;

	void Resize(Resolution resolution);

	void Replace(Pixel** frame, Resolution resolution);
	void Replace(Pixel pixel, __COORD coord);

	void Clear();
	void Print() const;

	friend class Image;

	void operator = (const Buffer& buffer);
};
