#include "Maze.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

Maze::Maze(): xsize(MAZEX), ysize(MAZEY), numin(0) {}

void Maze::initialise() {
    for(int x = 0; x < xsize; x++) {
		for(int y = 0; y < ysize; y++) {
			MAZE[x][y].in = ( x == 0 || x == xsize - 1 || y == 0 || y == ysize - 1 ) ? 1 : 0;
			MAZE[x][y].up = ( x == 0 || x == xsize - 1 || y == 0 ) ? 0 : 1;
			MAZE[x][y].left = ( x == 0 || y == 0 || y == ysize - 1 ) ? 0 : 1;
		}
	}
}

void Maze::maze_to_list(std::vector<std::pair<int,int>> adj[][MAZEY]) {
	for(int i = 1; i < xsize-1; i++) {
		for(int j = 1; j < ysize-1; j++) {
			if(!MAZE[i][j].up) {
				adj[i][j].push_back({i,j-1});
				adj[i][j-1].push_back({i,j});
			}
			if(!MAZE[i][j].left) {
				adj[i][j].push_back({i-1,j});
				adj[i-1][j].push_back({i,j});
			}
		}
	}
}

void Maze::generate() {
	srand(time(0));
    int xcur = 1, ycur = 1;
    MAZE[xcur][ycur].in = 1;
    numin++;
    int whichway;
    bool success;
    do {
        while(MAZE[xcur][ycur-1].in && MAZE[xcur][ycur+1].in && MAZE[xcur-1][ycur].in && MAZE[xcur+1][ycur].in) {
            int xcur2 = MAZE[xcur][ycur].prevx;
            ycur = MAZE[xcur][ycur].prevy;
            xcur = xcur2;
		}

        do {
			success = 0;
			whichway = rand()%4;
			switch(whichway){
			case UP:
				if(!MAZE[xcur][ycur-1].in) {
					success = 1;
					MAZE[xcur][ycur].up = 0;
					MAZE[xcur][ycur-1].prevx = xcur;
					MAZE[xcur][ycur-1].prevy = ycur;
					ycur--;
				}
				break;
			case DOWN:
				if(!MAZE[xcur][ycur+1].in) {
					success = 1;
					MAZE[xcur][ycur+1].up = 0;
					MAZE[xcur][ycur+1].prevx = xcur;
					MAZE[xcur][ycur+1].prevy = ycur;
					ycur++;
				}
				break;
			case LEFT:
				if(!MAZE[xcur-1][ycur].in) {
					success = 1;
					MAZE[xcur][ycur].left = 0;
					MAZE[xcur-1][ycur].prevx = xcur;
					MAZE[xcur-1][ycur].prevy = ycur;
					xcur--;
				}
				break;
			case RIGHT:
				if(!MAZE[xcur+1][ycur].in) {
					success = 1;
					MAZE[xcur+1][ycur].left = 0;
					MAZE[xcur+1][ycur].prevx = xcur;
					MAZE[xcur+1][ycur].prevy = ycur;
					xcur++;
				}
				break;
			}
		} while(!success);
		MAZE[xcur][ycur].in = 1;
		numin++;
    } while(numin < (xsize-2)*(ysize-2));
}

void Maze::render(SDL_Renderer* renderer, Uint8 opacity) {
	for(int y = 1; y < ysize-1; y++) {
		for(int x = 1; x < xsize-1; x++) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 205, opacity);
			SDL_Rect fillRect = {BX + x*GAP, BY + TEXT_GAP + y*GAP, GAP, GAP};
			SDL_RenderFillRect(renderer, &fillRect);
			if(MAZE[x][y].left) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, opacity);
				SDL_Rect fillRect = {BX + x*GAP, BY + TEXT_GAP + y*GAP, WALL_THICKNESS, GAP};
				SDL_RenderFillRect(renderer, &fillRect);
			}
			if(MAZE[x][y].up) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, opacity);
				SDL_Rect fillRect = {BX + x*GAP, BY + TEXT_GAP + y*GAP, GAP, WALL_THICKNESS};
				SDL_RenderFillRect(renderer, &fillRect);
			}
		}
	}
}
