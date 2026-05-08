#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

typedef struct {
	int x, y;
} Coord;

const Coord TARGET = {.x = 4, .y = 4};

int main(void)
{
	Coord prev[MAX_ROW][MAX_COL];
	Coord stack[MAX_ROW * MAX_COL];
	Coord cur;
	size_t stack_nr = 1;

	stack[0].x = stack[0].y = 0;
	prev[0][0].x = -1;
	maze[0][0] = 2;
	while(stack_nr > 0) {
		cur = stack[--stack_nr];
		if(cur.x == TARGET.x && cur.y == TARGET.y)
			break;


		if(cur.x < MAX_ROW-1 && maze[cur.x+1][cur.y] == 0) {
			stack[stack_nr].x = cur.x+1, stack[stack_nr].y = cur.y;
			stack_nr++;
			prev[cur.x+1][cur.y].x = cur.x, prev[cur.x+1][cur.y].y = cur.y;
			maze[cur.x+1][cur.y] = 2;
		}

		if(cur.y < MAX_COL-1 && maze[cur.x][cur.y+1] == 0) {
			stack[stack_nr].x = cur.x, stack[stack_nr].y = cur.y+1;
			stack_nr++;
			prev[cur.x][cur.y+1].x = cur.x, prev[cur.x][cur.y+1].y = cur.y;
			maze[cur.x][cur.y+1] = 2;
		}
		if(cur.x > 0 && maze[cur.x-1][cur.y] == 0) {
			stack[stack_nr].x = cur.x-1, stack[stack_nr].y = cur.y;
			stack_nr++;
			prev[cur.x-1][cur.y].x = cur.x, prev[cur.x-1][cur.y].y = cur.y;
			maze[cur.x-1][cur.y] = 2;
		}

		if(cur.y > 0 && maze[cur.x][cur.y-1] == 0) {
			stack[stack_nr].x = cur.x, stack[stack_nr].y = cur.y-1;
			stack_nr++;
			prev[cur.x][cur.y-1].x = cur.x, prev[cur.x][cur.y-1].y = cur.y;
			maze[cur.x][cur.y-1] = 2;
		}
	}
	if(cur.x == TARGET.x && cur.y == TARGET.y) {
		do {
			printf("(%d, %d)\n", cur.x, cur.y);
			cur = prev[cur.x][cur.y];
		} while(cur.x >= 0);
	} else {
		printf("No path!\n");
	}

	return 0;
}