#pragma once
#include <SDL.h>
#include "SDL_image.h"
#include <iostream>
#include <vector>

using namespace std;

class Sprite
{
protected:
	SDL_Surface *image;
	SDL_Rect rect;

	int origin_x, origin_y;

public:
	Sprite(Uint32 color, int x, int y, int w = 48, int h = 64)
	{
		image = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);

		SDL_FillRect(image, NULL, color);

		rect = image->clip_rect;

		origin_x = rect.w / 2;
		origin_y = rect.h / 2;

		rect.x = x;
		rect.y = y;
	}

	void update()
	{
		//can be overridden
	}

	void draw(SDL_Surface *destination)
	{
		SDL_BlitSurface(image, NULL, destination, &rect);
	}

	SDL_Surface* getImage() const
	{
		return image;
	}

	bool operator==(const Sprite &other) const
	{
		return (image == other.getImage());
	}

};

class SpriteGroup {
private:
	vector<Sprite*> sprites;
	int sprite_size;

public:
	SpriteGroup copy()
	{
		SpriteGroup newGroup;
		for (int i = 0; i < sprite_size; i++)
		{
			newGroup.add(sprites[i]);
		}
	}

	void add(Sprite *sprite)
	{
		sprites.push_back(sprite);
		sprite_size = sprites.size();
	}

	void remove(Sprite sprite_object)
	{
		for (int i = 0; i < sprite_size; i++)
		{
			if(*sprites[i]==sprite_object)
			{
				sprites.erase(sprites.begin() + i);
			}
			sprite_size = sprites.size();
		}

	}

	bool has(Sprite sprite_object)
	{
		for (int i = 0; i < sprite_size; i++)
		{
			if (*sprites[i] == sprite_object)
			{
				return true;
			}
		}
		return false;
	}

	void update()
	{
		if (!sprites.empty())
		{
			for (int i = 0; i < sprite_size; i++)
			{
				sprites[i]->update();
			}
		}
	}

	void draw(SDL_Surface *destination)
	{
		if (!sprites.empty())
		{
			for (int i = 0; i < sprite_size; i++)
			{
				sprites[i]->draw(destination);
			}
		}
	}

	void empty()
	{
		sprites.clear();
		sprite_size = sprites.size();
	}

	int size()
	{
		return sprite_size;
	}

	vector<Sprite*> getSprites()
	{
		return sprites;
	}
};

class Block : public Sprite
{
public:
	Block(Uint32 color, int x, int y, int w = 48, int h = 64)
		:Sprite(color, x, y, w, h)
	{
		updateProperties();
	}

	void updateProperties()
	{
		origin_x = 0;
		origin_y = 0;

		setPosition(rect.x, rect.y);
	}

	void setPosition(int x, int y)
	{
		rect.x = x - origin_x;
		rect.y = y - origin_y;
	}

	void setImage(const char filename[] = NULL)
	{
		if (filename!=NULL)
		{
			SDL_Surface *loadedimage = NULL;

			loadedimage = IMG_Load(filename);

			if (loadedimage!=NULL)
			{
				image = loadedimage;
				

				int old_x = rect.x;
				int old_y = rect.y;

				rect = image->clip_rect;

				rect.x = old_x;
				rect.y = old_y;

				updateProperties();

			}
		}
	}
};

