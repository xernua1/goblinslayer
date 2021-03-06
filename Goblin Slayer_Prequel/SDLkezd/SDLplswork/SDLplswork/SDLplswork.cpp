// SDLplswork.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SDL.h>
#include <iostream>
#include "Sprite.h"
#include "SDL_mixer.h"

#define window_width 1000
#define window_height 650

#define fps 60

using namespace std;

void cap_framerate(Uint32 starting_tick)
{
	if ((1000 / fps) > (SDL_GetTicks() - starting_tick))
	{
		SDL_Delay(1000 / fps - (SDL_GetTicks() - starting_tick));
	}
}


int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL COULD NOT INITIALIZE" << SDL_GetError() << std::endl;
	}
    //cout << "Hello World!\n"; 
	SDL_Window *window = NULL;

	window = SDL_CreateWindow(
		"Lul!",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		window_width,
		window_height,
		SDL_WINDOW_RESIZABLE);

	if (window==NULL)
	{
		cout << "There was an error initializing the window!" << endl << SDL_GetError() << endl;
	}

	SDL_Surface *screen = SDL_GetWindowSurface(window);
	int R = 0, G = 0, B = 0;
	Uint32 white = SDL_MapRGB(screen->format, R, G, B);
	Uint32 red = SDL_MapRGB(screen->format, 255, 0, 0);
	Uint32 blue = SDL_MapRGB(screen->format, 0, 0, 255);
	SDL_FillRect(screen, NULL, white);

	Block block(red, 0, 0);
	block.setImage("sprite.bmp");
	Block slayer(red, 222, 0);
	slayer.setImage("sprite2.png");
	Block gs(red, 222, 256);
	gs.setImage("sprite3.jpg");


	SpriteGroup activeSprites;
	activeSprites.add(&block);
	activeSprites.add(&slayer);
	activeSprites.add(&gs);
	
	activeSprites.draw(screen);

	SDL_UpdateWindowSurface(window);

	//initialize mixer
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_Chunk *sound = NULL;
	sound = Mix_LoadWAV("dummy.mp3");
	Mix_VolumeChunk(sound, 20);
	Mix_PlayChannel(-1, sound, 30);

	Mix_Music *music = NULL;
	Mix_VolumeMusic(0);
	music = Mix_LoadMUS("random.wav");
	Mix_PlayMusic(music, -1);

	Uint32 starting_tick;

	bool border = 1;
	int x, y, w, h;
	SDL_Event event;
	bool running = true;

	while (running)
	{
		starting_tick = SDL_GetTicks();
		while (SDL_PollEvent(&event))
		{
			// Quitting - X or 'Esc' key
			if (event.type == SDL_QUIT)
			{
				running = false;
				break;
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				running = false;
				break;
			}

			// WindowBorder - 'O' key 
			else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_O)
			{
				if(border)
				{
					SDL_SetWindowBordered(window, SDL_FALSE);
					border = false;
				}
				else
				{
					SDL_SetWindowBordered(window, SDL_TRUE);
					border = true;
				}
			}

			//Title - 'K' key
			else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_K)
			{
				//cout << SDL_GetWindowTitle(window) << endl;
				if ((string)SDL_GetWindowTitle(window) == "cse")
				{
					SDL_SetWindowTitle(window, "zsa");
				}
				else
				{
					SDL_SetWindowTitle(window, "cse");
				}
			}

			//Change surface color 'R', 'G', 'B' keys
			if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_R)
			{
				if(R!=255)
				{ 
					R += 5;

				}
				else
				{
					R = 0;
				}
				white = SDL_MapRGB(screen->format, R, G, B);
				SDL_FillRect(screen, NULL, white);
				SDL_UpdateWindowSurface(window);
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_G)
			{
				if (G != 255)
				{
					G += 5;

				}
				else
				{
					G = 0;
				}
				white = SDL_MapRGB(screen->format, R, G, B);
				SDL_FillRect(screen, NULL, white);
				SDL_UpdateWindowSurface(window);
			}
			else if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_B)
			{
				if (B != 255)
				{
					B += 5;

				}
				else
				{
					B = 0;
				}
				white = SDL_MapRGB(screen->format, R, G, B);
				SDL_FillRect(screen, NULL, white);
				SDL_UpdateWindowSurface(window);
			}
			//cout << "R,G,B:(" << R << "," << G << "," << B << ")" << endl;
		}

		//Automatic Surface color change ~fade

		//SDL_Delay(50);
		//if (R < 255)
		//{
		//	R += 4;
		//}
		//else
		//{
		//	R = 0;
		//}
		//if(G < 255)
		//{
		//	G += 7;
		//}
		//else
		//{
		//	G = 0;
		//}
		//if (B < 255)
		//{
		//	B += 6;
		//}
		//else
		//{
		//	B = 0;
		//}
		//white = SDL_MapRGB(screen->format, R, G, B);
		//SDL_FillRect(screen, NULL, white);
		//SDL_UpdateWindowSurface(window);

		//SDL_GetWindowPosition(window, &x, &y);
		//cout << "X: " << x << ", Y: " << y << endl;

		cap_framerate(starting_tick);
	}

	Mix_FreeMusic(music);
	Mix_FreeChunk(sound);
	Mix_CloseAudio();
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

