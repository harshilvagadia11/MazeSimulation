#include "Main.h"

enum direction {left, up, right, down};

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Texture gTextTexture;
Texture gDroidTexture;
Texture gFirstVisTexture;
Texture gSecondVisTexture;
Texture gNotifTexture;
Texture gNotifTexture1;
Texture gNotifTexture2;
Texture gPromptTexture;
Texture gDFSTexture1;
Texture gDFSTexture2;
Texture gBipTexture1;
Texture gBipTexture2;

Mix_Music *gGameMusic = NULL;
Mix_Chunk *gChangeTabSound = NULL;

Maze maze;
Droid droid;
Timer timer,timer1;
bool check=false;

bool quit = false;
bool start = false;
bool pause = false;
float vel = 1.0;
float delay = 0.0;
bool run_dfs=true;

bool visited[MAZEX][MAZEY];
std::map<std::pair<int,int>,int> status;
std::vector<std::pair<int,int>> adj[MAZEX][MAZEY];
std::string prompt=" ";

void dfs(int i, int j) {
	for(std::pair<int,int> p : adj[i][j]) {
		int x = p.first, y = p.second;
		if(visited[x][y]) continue;
		visited[x][y] = true;
		if(x == i-1) {
			droid.insert(left);
			dfs(x,y);
			droid.insert(right);
		} else if(x == i+1) {
			droid.insert(right);
			dfs(x,y);
			droid.insert(left);
		} else if(y == j-1) {
			droid.insert(up);
			dfs(x,y);
			droid.insert(down);
		} else if(y == j+1) {
			droid.insert(down);
			dfs(x,y);
			droid.insert(up);
		}
	}
}

bool init() {
	bool success = true;

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

	//SDL_Color textColor = {192, 192, 192};
	SDL_Color textColor = {0, 0, 205};
	if(!gDFSTexture2.loadFromRenderedText(gRenderer, "Simulate DFS", textColor)) {
		printf( "Failed to render text texture!\n" );
		success = false;
	}
	if(!gBipTexture2.loadFromRenderedText(gRenderer, "Simulate Bipartite", textColor)) {
		printf( "Failed to render text texture!\n" );
		success = false;
	}
	gBipTexture2.setAlpha(100);
	gDFSTexture2.setAlpha(100);
	textColor = {0, 0, 205};
	if(!gDFSTexture1.loadFromRenderedText(gRenderer, "Simulate DFS", textColor)) {
		printf( "Failed to render text texture!\n" );
		success = false;
	}
	if(!gBipTexture1.loadFromRenderedText(gRenderer, "Simulate Bipartite", textColor)) {
		printf( "Failed to render text texture!\n" );
		success = false;
	}
	textColor = {255, 64, 0};
	if(!gTextTexture.loadFromRenderedText(gRenderer, "Select the simulation and Press ENTER!", textColor)) {
		printf( "Failed to render text texture!\n" );
		success = false;
	}
	
	if(!gNotifTexture.loadFromRenderedText(gRenderer, "Simulation of DFS!", textColor)) {
		printf( "Failed to load tank texture!\n" );
		success = false;
	}
	if(!gNotifTexture1.loadFromRenderedText(gRenderer, "Simulation of Bipartite Algorithm!", textColor)) {
		printf( "Failed to load tank texture!\n" );
		success = false;
	}
	if(!gNotifTexture2.loadFromRenderedText(gRenderer, "Graph is not Bipartite!", textColor)) {
		printf( "Failed to load tank texture!\n" );
		success = false;
	}
    if(!gDroidTexture.loadFromFile(gRenderer, "images/tank_opaque.png")) {
		printf( "Failed to render text texture!\n" );
		success = false;
	}
	if(!gFirstVisTexture.loadFromFile(gRenderer, "images/yellow_dot_small.png")) {
		printf( "Failed to render text texture!\n" );
		success = false;
	}
	if(!gSecondVisTexture.loadFromFile(gRenderer, "images/purple_dot_small.png")) {    
		printf( "Failed to render text texture!\n" );
		success = false;
	}

	gGameMusic = Mix_LoadMUS( "sounds/game_music_low.wav" );
	if( gGameMusic == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	gChangeTabSound = Mix_LoadWAV( "sounds/change_tab.wav" );
	if( gChangeTabSound == NULL )
	{
		printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

    maze.generate();

	return success;
}

void close() {

	gTextTexture.free();
	gDroidTexture.free();
	gFirstVisTexture.free();
	gSecondVisTexture.free();
	gNotifTexture.free();
	gNotifTexture1.free();
	gNotifTexture2.free();
	gPromptTexture.free();
	gDFSTexture1.free();
	gDFSTexture2.free();
	gBipTexture1.free();
	gBipTexture2.free();
	
	Mix_FreeMusic( gGameMusic );
	gGameMusic = NULL;

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

			for(int i = 0; i < MAZEX; i++) {
				for(int j = 0; j < MAZEY; j++) {
					visited[i][j] = false;
				}
			}
			visited[1][1] = true;

			maze.maze_to_list(adj);
			dfs(1,1);

			while(!quit) {
				while(SDL_PollEvent(&e) != 0) {
					if(e.type == SDL_QUIT) {
						quit = true;
					} else if(e.type == SDL_KEYDOWN) {
						if(e.key.keysym.sym == SDLK_RETURN) {
                            start = true;
                            timer.start();
							Mix_PlayChannel( -1, gChangeTabSound, 0 );
						} else if (!start && (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP) ){
							run_dfs=!run_dfs;
							Mix_PlayChannel( -1, gChangeTabSound, 0 );
						}else if(start && e.key.keysym.sym==SDLK_SPACE) {
							pause=!pause;
							Mix_PlayChannel( -1, gChangeTabSound, 0 );
						} else if(start && !pause && e.key.keysym.sym==SDLK_RIGHT) {
							timer1.start();
							prompt="Speed Increased";
							check=true;
							if(vel < 40.0) {
								vel += 0.5;
							}
							Mix_PlayChannel( -1, gChangeTabSound, 0 );
						} else if(start && !pause && e.key.keysym.sym==SDLK_LEFT) {
							timer1.start();
							prompt="Speed Decreased";
							check=true;
							if(vel > 0.5) {
								vel -= 0.5;
							}
							Mix_PlayChannel( -1, gChangeTabSound, 0 );
						}
					}
				}

				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
				SDL_RenderClear(gRenderer);

				if(start) {
					if(timer.getTicks() <= 2000) maze.render(gRenderer, 255*timer.getTicks()/2000);
					else {
						if( Mix_PlayingMusic() == 0 )
						{
							//Play the music
							Mix_PlayMusic( gGameMusic, -1 );
						}
						if (pause) prompt="Paused";
						if (check && timer1.getTicks()>2000) {
							check=false;
						} 
						if (!pause && !check) prompt=" ";
						if (run_dfs) gNotifTexture.render(gRenderer, (SCREEN_WIDTH - gNotifTexture.getWidth())/2, BY);
						else {
							if (droid.bipartite) gNotifTexture1.render(gRenderer, (SCREEN_WIDTH - gNotifTexture1.getWidth())/2, BY);
							else gNotifTexture2.render(gRenderer, (SCREEN_WIDTH - gNotifTexture2.getWidth())/2, BY);
						}
						if (droid.bipartite) gPromptTexture.loadFromRenderedText(gRenderer, prompt.c_str(), textColor); 
						if (droid.bipartite) gPromptTexture.render(gRenderer, (SCREEN_WIDTH - gPromptTexture.getWidth())/2, SCREEN_HEIGHT-gPromptTexture.getHeight()-BY);
                        maze.render(gRenderer, 255);
						for(auto it : status) {
							int x_cor=it.first.first;
							int y_cor=it.first.second;
							if (it.second==1) gFirstVisTexture.render(gRenderer, x_cor+10, y_cor+10, NULL, 0);
							else gSecondVisTexture.render(gRenderer, x_cor+10, y_cor+10, NULL, 0);
						}
                        if (!pause && droid.bipartite) {
							delay += vel;
							float integer;
							delay = modf(delay, &integer);
							while(integer > 0.0) {
								if (run_dfs) droid.move(status);
								else {
									droid.move1(status);
								}
								integer--;
							}
						}
                        droid.render(gRenderer, gDroidTexture);
                    }
				} else {
					gTextTexture.render(gRenderer, (SCREEN_WIDTH - gTextTexture.getWidth())/2, (SCREEN_HEIGHT - gTextTexture.getHeight())/2);
					if (run_dfs){
						gDFSTexture1.render(gRenderer, (SCREEN_WIDTH - gDFSTexture1.getWidth())/2, (SCREEN_HEIGHT - gDFSTexture1.getHeight())/2+gTextTexture.getHeight());
						gBipTexture2.render(gRenderer, (SCREEN_WIDTH - gBipTexture2.getWidth())/2, (SCREEN_HEIGHT - gBipTexture2.getHeight())/2+gTextTexture.getHeight()+gDFSTexture1.getHeight());
					}else{
						gDFSTexture2.render(gRenderer, (SCREEN_WIDTH - gDFSTexture2.getWidth())/2, (SCREEN_HEIGHT - gDFSTexture2.getHeight())/2+gTextTexture.getHeight());
						gBipTexture1.render(gRenderer, (SCREEN_WIDTH - gBipTexture1.getWidth())/2, (SCREEN_HEIGHT - gBipTexture1.getHeight())/2+gTextTexture.getHeight()+gDFSTexture2.getHeight());
					}
				}

				SDL_RenderPresent(gRenderer);
			}
		}
	}

	close();

	return 0;
}