#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>

constexpr int kScreenWidth{ 640 };
constexpr int kScreenHeight{ 480 };


/*Global Variables*/

SDL_Window* gWindow{ nullptr };

SDL_Surface* gScreenSurface{ nullptr };
SDL_Surface* gHelloWorld{ nullptr };

bool init() {
	bool success{ true };

	if (SDL_Init(SDL_INIT_VIDEO) == false) {
		SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		/*We create the window in the conditional and then check if created correctly*/
		if (gWindow = SDL_CreateWindow("SDL 3 Tutorial: Hello SDL3", kScreenWidth, kScreenHeight, 0); gWindow == nullptr) {
			SDL_Log("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia(){
	/*File loading flag*/
	bool success{ true };
	/*Load Image splash*/
	std::string imagePath{ "D:\\Descargas\\hello-sdl3.bmp" };
	if (gHelloWorld = SDL_LoadBMP(imagePath.c_str()); gHelloWorld == nullptr) {
		SDL_Log("Unable to load image %s! SDL Error: %s\n", imagePath.c_str(), SDL_GetError());
		success = false;
	}
	return success;
}

void close() {
	/*Clean up Surface*/
	SDL_DestroySurface(gHelloWorld);
	gHelloWorld = nullptr;

	/*Destroy the window we created*/

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gScreenSurface = nullptr;


	/*Quit SDL subsystems*/
	SDL_Quit();
}

int SDL_main(int argc, char* argv[]) {
	/*Final exit code to find where could be errors*/

	int exitCode{ 0 };

	if (init() == false) {
		SDL_Log("Unable to initialize program!\n");
		exitCode = 1;
		/*exitCode set to 1 if error on init*/
	}
	else {
		/*Load Media*/
		if (loadMedia() == false) {
			SDL_Log("Unable to load media!\n");
			exitCode = 2;
			/*exitCode set to 2 if error on loadMedia*/
		}
		else {
			/*Quit Flag*/

			bool quit{ false };

			/*The Event Data*/
			SDL_Event e;
			SDL_zero(e);

			while (quit == false) {
				/*get Event Data*/
				while (SDL_PollEvent(&e) == true) {
					/*If event is quit type*/
					if (e.type == SDL_EVENT_QUIT) {
						quit = true;
					}
				}

				/*fill the surface with white*/
				SDL_FillSurfaceRect(gScreenSurface, nullptr, SDL_MapSurfaceRGB(gScreenSurface, 0xFF, 0xFF, 0xFF));
				/*Render image on screen*/
				SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);

				/*Update Surface*/
				SDL_UpdateWindowSurface(gWindow);
			} /*end of quit while*/
		}
		
	}
	/*Clean Up*/
	close();


	return exitCode;
}