#include "Buffer.h"
#include <Windows.h>
#include <iostream>
using namespace std;

Buffer::Buffer()
{
	buffer = nullptr;
	Resize(Resolution{ 1,1 });
}

Buffer::Buffer(Resolution resolution)
{
	Resize(resolution);
}

Buffer::Buffer(const Buffer& buffer)
{
	Resize(buffer.GetResolution());

	for (size_t i = 0; i < GetHeight(); i++)
		for (size_t j = 0; j < GetWidth(); j++)
			this->buffer[i][j] = buffer.buffer[i][j];

	this->resolution = buffer.resolution;
}

Buffer::~Buffer()
{
	if (buffer != nullptr)
	{
		for (size_t i = 0; i < this->resolution.height; i++)
			delete[] buffer[i];
		delete[] buffer;

		buffer = nullptr;
	}
}

Resolution Buffer::GetResolution() const
{
	return this->resolution;
}

size_t Buffer::GetWidth() const
{
	return this->resolution.width;
}

size_t Buffer::GetHeight() const
{
	return this->resolution.height;
}

Pixel Buffer::GetPixel(__COORD coord) const
{
	return this->buffer[coord.y][coord.x];
}

void Buffer::Resize(Resolution resolution)
{
	if (buffer != nullptr)
	{
		for (size_t i = 0; i < this->resolution.height; i++)
			delete[] buffer[i];
		delete[] buffer;

		buffer = nullptr;
	}

	this->resolution.height = resolution.height;
	this->resolution.width = resolution.width;

	buffer = new Pixel * [this->resolution.height];
	for (size_t i = 0; i < this->resolution.height; i++)
		buffer[i] = new Pixel[this->resolution.width];

	Clear();
}

void Buffer::Replace(Pixel** frame, Resolution resolution)
{
	Resize(resolution);
	for (size_t i = 0; i < this->resolution.height; i++)
	{
		for (size_t j = 0; j < this->resolution.width; i++)
		{
			this->buffer[i][j].symbol = frame[i][j].symbol;
			this->buffer[i][j].color = frame[i][j].color;
			this->buffer[i][j].background = frame[i][j].background;
		}
	}
}

void Buffer::Replace(Pixel pixel, __COORD coord)
{
	this->buffer[coord.y][coord.x] = pixel;
}

void Buffer::Clear()
{
	for (size_t i = 0; i < this->resolution.height; i++)
	{
		for (size_t j = 0; j < this->resolution.width; j++)
		{
			buffer[i][j].symbol = ' ';
			buffer[i][j].color = Color::WHITE;
			buffer[i][j].background = Color::BLACK;
		}
	}
}

void Buffer::Print() const
{
	for (size_t i = 0; i < this->resolution.height; i++)
	{
		for (size_t j = 0; j < this->resolution.width; j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (buffer[i][j].color + (buffer[i][j].background * 16)));

			cout << buffer[i][j].symbol;

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		cout << endl;
	}
}

void Buffer::operator=(const Buffer& buffer)
{
	Resize(buffer.GetResolution());

	for (size_t i = 0; i < GetHeight(); i++)
		for (size_t j = 0; j < GetWidth(); j++)
			this->buffer[i][j] = buffer.buffer[i][j];

	this->resolution = buffer.resolution;
}