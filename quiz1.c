//202113387 ��ȣ��

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_LENGTH 20

// ť ����ü ����
typedef struct {
    char words[MAX_WORDS][MAX_LENGTH];
    int front, rear;
} Queue;

// ť �ʱ�ȭ �Լ�
void initQueue(Queue* q) {
    q->front = q->rear = 0;
}

// ť�� ���� �߰� �Լ�
void enqueue(Queue* q, char* word) {
    strcpy(q->words[q->rear++], word);
}

// ť���� ���� ���� �Լ�
void dequeue(Queue* q) {
    q->front++;
}

// ť�� ����ִ��� Ȯ���ϴ� �Լ�
int isEmpty(Queue* q) {
    return q->front == q->rear;
}

// ���� ���� ���� ���θ� Ȯ���ϴ� �Լ�
int reconstructSentence(int n_students, int n_words) {
    char words[MAX_WORDS][MAX_LENGTH];
    int i, j;
    Queue q;
    initQueue(&q);

    // �� �л��� �ʱ��� �ܾ� �Է¹ޱ�
    for (i = 0; i < n_students; i++) {
        for (j = 0; j < n_words; j++) {
            char word[MAX_LENGTH];
            scanf("%s", word);
            enqueue(&q, word);
        }
    }

    // ���� ����
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
            return 0; // ���� �Ұ���
        }
        // ���� �ܾ ť�� �߰�
        for (j = 0; j < n_students; j++) {
            if (!isEmpty(&q) && strcmp(next_word, q.words[q.front]) != 0) {
                strcpy(words[j], q.words[q.front]);
                dequeue(&q);
            }
        }
        // ���� �ܾ ���� ���
        if (isEmpty(&q)) {
            break;
        }
        // ť�� ���� �ܾ���� ����
        while (!isEmpty(&q)) {
            dequeue(&q);
        }
        // ���� �ܾ ť�� �߰�
        for (j = 0; j < n_students; j++) {
            if (strlen(words[j]) > 0) {
                enqueue(&q, words[j]);
            }
        }
    }
    return 1; // ���� ����
}

int main() {
    int n_sentences;
    scanf("%d", &n_sentences);

    // ���帶�� ���� ���� ���� Ȯ�� �� ���
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
