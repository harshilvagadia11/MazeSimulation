#include "Main.h"

enum direction {left, up, right, down};

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Texture gTextTexture;
Texture gDroidTexture;

Maze maze;
Droid droid;
Timer timer;

bool quit = false;
bool start = false;
int tot_nodes=MAZEX*MAZEY;
int tot_stones = 8;
std::vector<int> loc_stones(tot_stones);
std::vector<bool> loc_taken(tot_nodes);          // to check location if we dont place multiple stones at same loc
int start_loc=-1,end_loc=-1;
std::vector<std::vector<int>> adj(tot_nodes);

bool init() {
	bool success = true;
	for(int i=0; i<tot_nodes;i++) loc_taken[tot_nodes]=false;
	

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	} else {
		if(TTF_Init() == -1) {
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
			success = false;
			return false;
		}
		int imgFlags = IMG_INIT_PNG;
		if(!(IMG_Init(imgFlags) & imgFlags)) {
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			success = false;
			return false;
		}
		//Initialize SDL_mixer
		if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
		{
			printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
			success = false;
		}
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		gWindow = SDL_CreateWindow("Maze Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		} else {
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
			if(gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			} else {
				SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
				maze.initialise();
			}
		}
	}

	return success;
}

bool loadMedia() {
	bool success = true;

	SDL_Color textColor = {255, 64, 0};
	if(!gTextTexture.loadFromRenderedText(gRenderer, "Press ENTER to start simulation!", textColor)) {
		printf( "Failed to render text texture!\n" );
		success = false;
	}
    if(!gDroidTexture.loadFromFile(gRenderer, "images/tank_red.bmp")) {
		printf( "Failed to render text texture!\n" );
		success = false;
	}

    maze.generate();

	return success;
}

void close() {
	
	gTextTexture.free();

	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void get_start_loc(){
	int x = rand()%tot_nodes;
	start_loc=x;
	loc_taken[x]=true;
}

void get_end_loc(){
	int x = rand()%tot_nodes;
	while(loc_taken[x]){
		x = rand()%tot_nodes;
	}
	end_loc=x;
	loc_taken[x]=true;
}

void get_stones() {
	int i=0;
	while(i<tot_stones){
		int x = rand()%tot_nodes;
		if (loc_taken[x]) continue;
		loc_stones[i]=x;
		i++;
	}
}

void get_adjacency_list(){
	maze.maze_to_list(adj);
}

int main(int argc, char* args[]) {
	if(!init()) {
		printf("Failed to initialize!\n");
	} else {
		if(!loadMedia()) {
			printf("Failed to load media!\n");
		} else {

			SDL_Event e;
			SDL_Color textColor = {255, 64, 0};

			SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
			SDL_RenderClear(gRenderer);

			get_start_loc();
			get_end_loc();
			get_stones();
			get_adjacency_list();

            droid.insert(right); droid.insert(right); droid.insert(down); droid.insert(left);

			while(!quit) {
				while(SDL_PollEvent(&e) != 0) {
					if(e.type == SDL_QUIT) {
						quit = true;
					} else if(e.type == SDL_KEYDOWN) {
						if(e.key.keysym.sym == SDLK_RETURN) {
                            start = true;
                            timer.start();
						}
					}
				}

				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
				SDL_RenderClear(gRenderer);

				if(start) {
					if(timer.getTicks() <= 2000) maze.render(gRenderer, 255*timer.getTicks()/2000);
					else {
                        maze.render(gRenderer, 255);
                        droid.move();
                        droid.render(gRenderer, gDroidTexture);
                    }
				} else {
					gTextTexture.render(gRenderer, (SCREEN_WIDTH - gTextTexture.getWidth())/2, (SCREEN_HEIGHT - gTextTexture.getHeight())/2);
				}

				SDL_RenderPresent(gRenderer);
			}
		}
	}

	close();

	return 0;
}