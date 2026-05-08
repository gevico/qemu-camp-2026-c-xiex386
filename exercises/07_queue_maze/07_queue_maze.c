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

struct ListNode {
	struct ListNode *next;
	Coord coord;
};

static void push_back(struct ListNode **head_ptr, struct ListNode **tail_ptr, struct ListNode *node) {
	struct ListNode *tail = *tail_ptr;
	if(tail == NULL) {
		*head_ptr = *tail_ptr = node;
		return;
	}

	tail->next = node;
	*tail_ptr = node;
}

static struct ListNode *pop_front(struct ListNode **head_ptr, struct ListNode **tail_ptr) {
	struct ListNode *head = *head_ptr, *tail = *tail_ptr;
	if(head == tail) {
		*head_ptr = *tail_ptr = NULL;
		return head;
	}

	*head_ptr = head->next;
	return head;
}

int main(void)
{
	Coord prev[MAX_ROW][MAX_COL];
	struct ListNode queue[MAX_ROW * MAX_COL];
	struct ListNode *head = NULL, *tail = NULL;
	Coord cur;
	size_t alloc_cnt;

	queue[0].coord.x = 0, queue[0].coord.y = 0;
	push_back(&head, &tail, &queue[0]);

	alloc_cnt = 1;
	prev[0][0].x = -1;
	maze[0][0] = 2;
	while(head) {
		// TODO: reuse allocated ListNode
		cur = pop_front(&head, &tail)->coord;
		if(cur.x == TARGET.x && cur.y == TARGET.y)
			break;
	
		if(cur.x < MAX_ROW-1 && maze[cur.x+1][cur.y] == 0) {
			queue[alloc_cnt].coord.x = cur.x+1, queue[alloc_cnt].coord.y = cur.y;
			push_back(&head, &tail, &queue[alloc_cnt]);
			alloc_cnt++;
			prev[cur.x+1][cur.y].x = cur.x, prev[cur.x+1][cur.y].y = cur.y;
			maze[cur.x+1][cur.y] = 2;
		}

		if(cur.y < MAX_COL-1 && maze[cur.x][cur.y+1] == 0) {
			queue[alloc_cnt].coord.x = cur.x, queue[alloc_cnt].coord.y = cur.y+1;
			push_back(&head, &tail, &queue[alloc_cnt]);
			alloc_cnt++;
			prev[cur.x][cur.y+1].x = cur.x, prev[cur.x][cur.y+1].y = cur.y;
			maze[cur.x][cur.y+1] = 2;
		}
		if(cur.x > 0 && maze[cur.x-1][cur.y] == 0) {
			queue[alloc_cnt].coord.x = cur.x-1, queue[alloc_cnt].coord.x = cur.y;
			push_back(&head, &tail, &queue[alloc_cnt]);
			alloc_cnt++;
			prev[cur.x-1][cur.y].x = cur.x, prev[cur.x-1][cur.y].y = cur.y;
			maze[cur.x-1][cur.y] = 2;
		}

		if(cur.y > 0 && maze[cur.x][cur.y-1] == 0) {
			queue[alloc_cnt].coord.x = cur.x, queue[alloc_cnt].coord.x = cur.y-1;
			push_back(&head, &tail, &queue[alloc_cnt]);
			alloc_cnt++;
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