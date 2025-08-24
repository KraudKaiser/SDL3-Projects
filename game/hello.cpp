#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <string>

class LTexture {
public:
	/*initializes texture variables*/
	LTexture();

	/*Cleans texture variables*/
	~LTexture();

	bool loadFromFile(std::string path);


	/*cleans texture*/
	void destroy();
	//Draws texture
	void render(float x, float y);

	int getWidth();
	int getHeight();
	bool isLoaded();

private:
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;
};

constexpr int kScreenWidth{ 640 };
constexpr int kScreenHeight{ 480 };


/*Global Variables*/

/*window were we been rendering*/
SDL_Window* gWindow{ nullptr };
/*renderer to draw window*/
SDL_Renderer* gRenderer{ nullptr };

LTexture gPngTexture;

LTexture gUpTexture, gDownTexture, gLeftTexture, gRightTexture;


/* Class Implementations */
//LTexture Implementation
LTexture::LTexture() :
	mTexture{ nullptr },
	mWidth{ 0 },
	mHeight{ 0 }
{

}

LTexture::~LTexture() {
	destroy();
}

bool LTexture::loadFromFile(std::string path) {
	//Cleans texture if already exists

	destroy();

	//load surface
	
	if (SDL_Surface* loadedSurface = IMG_Load(path.c_str()); loadedSurface == nullptr) {
		SDL_Log("Unable to load image %s! SDL_image error: %s\n", path.c_str(), SDL_GetError());
		
	}
	else {
		//Create texture from surface
		if (mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface); mTexture == nullptr) {
			SDL_Log("Unable to create texture from loaded pixels! SDL error: %s\n", SDL_GetError());
		}
		else {
			//get image 
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//clean up loaded surface
		SDL_DestroySurface(loadedSurface);
	}
	return mTexture != nullptr;
}

void LTexture::destroy() {
	//cleans up texture

	SDL_DestroyTexture(mTexture);
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
}

void LTexture::render(float x, float y) {
	//set texture position
	SDL_FRect dstRect{ x,y, static_cast<float>(mWidth), static_cast<float>(mHeight) };

	//Render Texture
	SDL_RenderTexture(gRenderer, mTexture, nullptr, &dstRect);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool LTexture::isLoaded()
{
	return mTexture != nullptr;
}


SDL_Surface* gScreenSurface{ nullptr };




bool init() {
	bool success{ true };

	if (SDL_Init(SDL_INIT_VIDEO) == false) {
		SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		/*We create the window in the conditional and then check if created correctly*/
		if (SDL_CreateWindowAndRenderer("SDL 3 Tutorial: Textures and Extension Libraries", kScreenWidth, kScreenHeight, 0, &gWindow, &gRenderer) == false) {
			SDL_Log("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
	}
	return success;
}

bool loadMedia(){
	/*File loading flag*/
	bool success{ true };


	/*Load Image splash*/
	
	if (gUpTexture.loadFromFile("D:\\Descargas\\03-key-presses-and-key-states\\03-key-presses-and-key-states\\up.png") == false) {
		SDL_Log("Unable to load png image!\n");
		success = false;
	}
	if (gDownTexture.loadFromFile("D:\\Descargas\\03-key-presses-and-key-states\\03-key-presses-and-key-states\\down.png") == false) {
		SDL_Log("Unable to load png image!\n");
		success = false;
	}
	if (gLeftTexture.loadFromFile("D:\\Descargas\\03-key-presses-and-key-states\\03-key-presses-and-key-states\\left.png") == false) {
		SDL_Log("Unable to load png image!\n");
		success = false;
	}
	if (gRightTexture.loadFromFile("D:\\Descargas\\03-key-presses-and-key-states\\03-key-presses-and-key-states\\right.png") == false) {
		SDL_Log("Unable to load png image!\n");
		success = false;
	}
	return success;
}

void close() {
	/*now cleans up texture*/
	gPngTexture.destroy();

	//destroy window 
	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

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

			LTexture* currentTexture = &gUpTexture;

			SDL_Color bgColor{ 0xFF, 0xFF, 0xFF, 0xFF };

			while (quit == false) {
				/*get Event Data*/
				while (SDL_PollEvent(&e) == true) {
					/*If event is quit type*/
					if (e.type == SDL_EVENT_QUIT) {
						quit = true;
					}

					else if (e.type == SDL_EVENT_KEY_DOWN) {
						if (e.key.key == SDLK_UP) {
							currentTexture = &gUpTexture;
						}
						else if (e.key.key == SDLK_DOWN) {
							currentTexture = &gDownTexture;
						}
						else if (e.key.key == SDLK_LEFT) {
							currentTexture = &gLeftTexture;
						}
						else if (e.key.key == SDLK_RIGHT) {
							currentTexture = &gRightTexture;
						}
					}
				}
				//Sets background to white
				bgColor.r == 0xFF;
				bgColor.g == 0xFF;
				bgColor.b == 0xFF;

				//Set background depending on key pressed
				const bool* keyStates = SDL_GetKeyboardState(nullptr);

				//Checks up is pressed
				if (keyStates[SDL_SCANCODE_UP] == true) {
					//Red
					bgColor.r = 0xFF;
					bgColor.g = 0x00;
					bgColor.b = 0x00;
				}
				else if (keyStates[SDL_SCANCODE_DOWN] == true)
				{
					//Green
					bgColor.r = 0x00;
					bgColor.g = 0xFF;
					bgColor.b = 0x00;
				}
				else if (keyStates[SDL_SCANCODE_LEFT] == true)
				{
					//Yellow
					bgColor.r = 0xFF;
					bgColor.g = 0xFF;
					bgColor.b = 0x00;
				}
				else if (keyStates[SDL_SCANCODE_RIGHT] == true)
				{
					//Blue
					bgColor.r = 0x00;
					bgColor.g = 0x00;
					bgColor.b = 0xFF;
				}

				/*fill the surface with white*/
				SDL_SetRenderDrawColor(gRenderer, bgColor.r, bgColor.g, bgColor.b, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render image of keyboard presses

				currentTexture->render((kScreenWidth - currentTexture->getWidth()) / 2.f, (kScreenHeight - currentTexture->getHeight()) / 2.f);
				
				
				/*Update screen*/
				SDL_RenderPresent(gRenderer);
			} /*end of quit while*/
		}
		
	}
	/*Clean Up*/
	close();


	return exitCode;
}