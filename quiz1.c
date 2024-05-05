//202113387 김호영

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_LENGTH 20

// 큐 구조체 정의
typedef struct {
    char words[MAX_WORDS][MAX_LENGTH];
    int front, rear;
} Queue;

// 큐 초기화 함수
void initQueue(Queue* q) {
    q->front = q->rear = 0;
}

// 큐에 원소 추가 함수
void enqueue(Queue* q, char* word) {
    strcpy(q->words[q->rear++], word);
}

// 큐에서 원소 제거 함수
void dequeue(Queue* q) {
    q->front++;
}

// 큐가 비어있는지 확인하는 함수
int isEmpty(Queue* q) {
    return q->front == q->rear;
}

// 문장 복원 가능 여부를 확인하는 함수
int reconstructSentence(int n_students, int n_words) {
    char words[MAX_WORDS][MAX_LENGTH];
    int i, j;
    Queue q;
    initQueue(&q);

    // 각 학생이 필기한 단어 입력받기
    for (i = 0; i < n_students; i++) {
        for (j = 0; j < n_words; j++) {
            char word[MAX_LENGTH];
            scanf("%s", word);
            enqueue(&q, word);
        }
    }

    // 문장 복원
    for (i = 0; i < n_words; i++) {
        char next_word[MAX_LENGTH];
        int word_exist = 0;
        for (j = 0; j < n_students; j++) {
            if (!isEmpty(&q)) {
                strcpy(next_word, q.words[q.front]);
                dequeue(&q);
                word_exist = 1;
                break;
            }
        }
        if (!word_exist) {
            return 0; // 복원 불가능
        }
        // 다음 단어를 큐에 추가
        for (j = 0; j < n_students; j++) {
            if (!isEmpty(&q) && strcmp(next_word, q.words[q.front]) != 0) {
                strcpy(words[j], q.words[q.front]);
                dequeue(&q);
            }
        }
        // 다음 단어가 없는 경우
        if (isEmpty(&q)) {
            break;
        }
        // 큐에 남은 단어들을 버림
        while (!isEmpty(&q)) {
            dequeue(&q);
        }
        // 다음 단어를 큐에 추가
        for (j = 0; j < n_students; j++) {
            if (strlen(words[j]) > 0) {
                enqueue(&q, words[j]);
            }
        }
    }
    return 1; // 복원 가능
}

int main() {
    int n_sentences;
    scanf("%d", &n_sentences);

    // 문장마다 복원 가능 여부 확인 후 출력
    for (int i = 0; i < n_sentences; i++) {
        int n_students, n_words;
        scanf("%d %d", &n_students, &n_words);

        if (reconstructSentence(n_students, n_words)) {
            printf("1\n");
        }
        else {
            printf("0\n");
        }
    }

    return 0;
}
