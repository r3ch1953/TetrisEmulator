#include "Image.h"
#include <iostream>
#include <fstream>

Image::Image()
{
	image.buffer = nullptr;
}

Image::Image(string filename)
{
	SetImage(filename, Image::FindResolution(filename), 1);
}

Image::Image(const Image& image)
{
	this->image.Resize(image.image.GetResolution());

	for (size_t i = 0; i < this->image.GetHeight(); i++)
		for (size_t j = 0; j < this->image.GetWidth(); j++)
			this->image.buffer[i][j] = image.image.buffer[i][j];

	this->image.resolution = image.image.resolution;
}

Resolution Image::FindResolution(std::string filename)
{
	Resolution resolution{ 0,0 };

	if (filename.empty())
	{
		cout << "Error! Filename is empty!\n";
		return resolution;
	}
	fstream fread(filename);
	if (!fread.is_open())
	{
		cout << "Error! File not opened!\n";
		return resolution;
	}

	char temp = ' ';
	char prev = ' ';
	int counter = 0;
	while ((temp = fread.get()) != EOF)
	{
		if (temp == '@')
			counter++;

		if (prev != '@' && temp == '\n')
			resolution.height++;

		if (temp != '\n' && temp != '@')
			resolution.width++;


		prev = temp;
	}
	fread.close();

	resolution.width = (resolution.width / resolution.height) + 1;
	if(counter != 1)
		resolution.height = resolution.height / (counter - 1);

	return resolution;
}

Resolution Image::GetResolution() const
{
	return this->image.resolution;
}

void Image::SetImage(std::string filename, Resolution resolution, size_t frame)
{
	if (filename.empty())
	{
		cout << "Error! Filename is empty!\n";
		return;
	}
	fstream fread(filename);
	if (!fread.is_open())
	{
		cout << "Error! File not opened!\n";
		return;
	}

	image.Resize(resolution);

	if (frame >= 2)
	{
		char temp;
		int counter = 0;
		while ((frame - 1) != counter)
		{
			if ((temp = fread.get()) != EOF)
			{
				if (temp == '@')
					counter++;
			}
		}
	}

	bool startRead = false;
	char currentSymbol;
	char prevSymbol;
	for (int i = 0; i < resolution.height; i++)
	{
		for (int j = 0; j < resolution.width; j++)
		{
			if ((currentSymbol = fread.get()) != EOF)
			{
				if (startRead && prevSymbol != '@' && currentSymbol != '@')
					image.Replace(Pixel{ currentSymbol, Color::WHITE, Color::BLACK }, __COORD{ size_t(i),size_t(j) });
				else
					j--;

				if (currentSymbol == '@')
					startRead = !startRead;

				prevSymbol = currentSymbol;
			}
		}
	}
	fread.close();
}

void Image::SetColor(Color color)
{
	for (size_t i = 0; i < image.GetHeight(); i++)
		for (size_t j = 0; j < image.GetWidth(); j++)
			image.buffer[i][j].color = color;
}

void Image::SetBackground(Color color)
{
	for (size_t i = 0; i < image.GetHeight(); i++)
		for (size_t j = 0; j < image.GetWidth(); j++)
			image.buffer[i][j].background = color;
}

Buffer& Image::GetBuffer()
{
	return this->image;
}

Image Image::GetFrameFromFile(std::string filename, Resolution resolution, size_t frame)
{
	Image temp;
	temp.SetImage(filename, resolution, frame);
	return temp;
}

void Image::LoadToBuffer(Buffer& buffer, __COORD coord)
{
	if (!((coord.x + image.GetWidth()) <= buffer.GetWidth() && (coord.y + image.GetHeight()) <= buffer.GetHeight()))
	{
		cout << "Wrong x or y! Error!";
		return;
	}

	for (size_t i = coord.y, imageI = 0; imageI < image.GetHeight(); i++, imageI++)
	{
		for (size_t j = coord.x, imageJ = 0; imageJ < image.GetWidth(); j++, imageJ++)
		{
			if (image.buffer[imageI][imageJ].symbol != '\n')
				buffer.Replace(image.buffer[imageI][imageJ], __COORD{ i,j });
		}
	}
}

void Image::operator=(const Image& image)
{
	this->image.Resize(image.image.GetResolution());

	for (size_t i = 0; i < this->image.GetHeight(); i++)
		for (size_t j = 0; j < this->image.GetWidth(); j++)
			this->image.buffer[i][j] = image.image.buffer[i][j];

	this->image.resolution = image.image.resolution;
}
