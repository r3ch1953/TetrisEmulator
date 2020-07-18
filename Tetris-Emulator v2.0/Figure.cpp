#include "Figure.h"
#include <iostream>
using namespace std;

Figure::Figure()
{
	this->parts.resize(4);
}

Figure::Figure(string filename, FigureIndex index)
{
	texture.SetImage(filename, Image::FindResolution(filename), 1);
	this->index = index;
	CreateFigure();
	this->figure.Resize(this->texture.GetResolution());
	this->parts.resize(4);
}

Figure::Figure(const Figure& figure)
{
	this->figure = figure.figure;
	this->texture = figure.texture;
}

void Figure::Rotate()
{
	Buffer temp(Resolution{ this->texture.GetResolution().width, this->texture.GetResolution().height });

	for (size_t i = 0; i < temp.GetHeight(); i++)
		for (size_t j = 0; j < temp.GetWidth(); j++)
			temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ j, temp.GetHeight() - i - 1 }), __COORD{ i,j });

	this->texture.SetBuffer(temp);
	this->figure.Resize(this->texture.GetResolution());
}

void Figure::LoadTextureToFigure()
{
	this->texture.LoadToBuffer(this->figure, __COORD{0, 0});
}

void Figure::CreateFigure()
{
	Buffer temp;
	switch (index)
	{
	case I:
		temp.Resize(Resolution{ 1,4 });

		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 0,0 }); // #
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 0,1 }); // #
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 0,2 }); // #
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 0,3 }); // #

		this->texture.SetBuffer(temp);

		break;
	case J:
		temp.Resize(Resolution{ 2,3 });

		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 0,0 }); // #
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 1,0 }); // ###
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 1,1 });
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 1,2 });

		this->texture.SetBuffer(temp);
		break;
	case Z:
		temp.Resize(Resolution{ 2,3 });

		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 0,0 }); // ##
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 0,1 }); //  ##
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 1,1 });
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 1,2 });

		this->texture.SetBuffer(temp);
		break;
	case T:
		temp.Resize(Resolution{ 2,3 });

		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 0,1 }); //  #
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 1,0 }); // ###
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 1,1 });
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 1,2 });

		this->texture.SetBuffer(temp);
		break;
	case O:
		temp.Resize(Resolution{ 2,2 });

		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 0,0 }); // ##
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 0,1 }); // ##
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 1,0 });
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 1,1 });

		this->texture.SetBuffer(temp);
		break;
	case S:
		temp.Resize(Resolution{ 2,3 });

		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 0,1 }); //  ##
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 0,2 }); // ##
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 1,0 });
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 1,1 });

		this->texture.SetBuffer(temp);
		break;
	case L:
		temp.Resize(Resolution{ 2,3 });

		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 0,2 }); //   #
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 1,0 }); // ###
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 1,1 });
		temp.Replace(this->texture.GetBuffer().GetPixel(__COORD{ 0,0 }), __COORD{ 1,2 });

		this->texture.SetBuffer(temp);
		break;
	}
}

__COORD Figure::GetCoord() const
{
	return this->coord;
}

void Figure::SetCoord(size_t x, size_t y)
{
	this->coord.x = x;
	this->coord.y = y;
}

void Figure::SetCoord(__COORD coord)
{
	this->coord = coord;
}

Image& Figure::GetTexture()
{
	return this->texture;
}

Buffer& Figure::GetBuffer()
{
	return this->figure;
}

vector<__COORD>& Figure::GetParts()
{
	return this->parts;
}

__COORD Figure::GetPart(size_t index)
{
	if (index < this->parts.size())
		return this->parts[index];
	return this->parts[0];
}

void Figure::LoadToBuffer(Buffer& buffer, __COORD coord)
{
	LoadTextureToFigure();

	if ((coord.y + this->figure.GetHeight()) > buffer.GetHeight() || (coord.x + this->figure.GetWidth()) > buffer.GetWidth())
	{
		cout << "Wrong X or Y! Error!\n";
		return;
	}

	int partCounter = 0;
	for (size_t i = coord.y, figureI = 0; figureI < this->figure.GetHeight(); i++, figureI++)
	{
		for (size_t j = coord.x, figureJ = 0; figureJ < this->figure.GetWidth(); j++, figureJ++)
		{
			if (this->figure.GetPixel(__COORD{ figureI, figureJ }).symbol == '#')
				this->parts[partCounter] = (__COORD{ i,j });

			if(this->figure.GetPixel(__COORD{ figureI, figureJ }).symbol != ' ')
				buffer.Replace(this->figure.GetPixel(__COORD{ figureI, figureJ }), __COORD{ i,j });

			++partCounter;
			if (partCounter == 4)
				partCounter = 0;
		}
	}
}

void Figure::LoadToBuffer(Buffer& buffer)
{
	LoadTextureToFigure();

	if ((this->coord.y + this->figure.GetHeight()) > buffer.GetHeight() || (this->coord.x + this->figure.GetWidth()) > buffer.GetWidth())
	{
		cout << "Wrong X or Y! Error!\n";
		return;
	}

	int partCounter = 0;
	for (size_t i = this->coord.y, figureI = 0; figureI < this->figure.GetHeight(); i++, figureI++)
	{
		for (size_t j = this->coord.x, figureJ = 0; figureJ < this->figure.GetWidth(); j++, figureJ++)
		{
			if (this->figure.GetPixel(__COORD{ figureI, figureJ }).symbol == '#')
				this->parts[partCounter] = (__COORD{ i,j });

			if (this->figure.GetPixel(__COORD{ figureI, figureJ }).symbol != ' ')
				buffer.Replace(this->figure.GetPixel(__COORD{ figureI, figureJ }), __COORD{ i,j });

			++partCounter;
			if (partCounter == 4)
				partCounter = 0;
		}
	}
}