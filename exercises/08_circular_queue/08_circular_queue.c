#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;
    int tail;
    int count;
} Queue;

People pop_front(Queue *q) {
    People front = q->data[q->head];
    q->head++;
    if(q->head == MAX_PEOPLE) {
        q->head = 0;
    }
    q->count--;
    return front;
}

void push_back(Queue *q, People back) {
    q->data[q->tail] = back;
    q->tail++;
    if(q->tail == MAX_PEOPLE) {
        q->tail = 0;
    }
    q->count++;
}

int main() {
    Queue q;
    int total_people=50;
    int report_interval=5;

    q.head = q.tail = q.count = 0;

    for(int i = 1; i <= total_people; i++) {
        People p = {i};
        push_back(&q, p);
    }

    while(q.count > 1) {
        for(int i = 1; i < report_interval; i++) {
            push_back(&q, pop_front(&q));
        }
        printf("淘汰: %d\n", pop_front(&q).id);
    }
    printf("最后剩下的人是: %d\n", q.data[q.head].id);

    return 0;
}