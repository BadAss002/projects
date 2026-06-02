#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

//минимальная куча
typedef struct {
    unsigned long long* arr;
    int size;
    int cap;
} Heap;

Heap* heap_create(int cap) {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->arr = (unsigned long long*)malloc(sizeof(unsigned long long) * cap);
    h->size = 0;
    h->cap = cap;
    return h;
}

void heap_push(Heap* h, unsigned long long val) {
    if (h->size >= h->cap) {
        h->cap *= 2;
        h->arr = (unsigned long long*)realloc(h->arr, sizeof(unsigned long long) * h->cap);
    }
    int i = h->size++;
    h->arr[i] = val;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->arr[p] <= h->arr[i]) break;
        unsigned long long t = h->arr[p];
        h->arr[p] = h->arr[i];
        h->arr[i] = t;
        i = p;
    }
}

unsigned long long heap_pop(Heap* h) {
    unsigned long long min = h->arr[0];
    h->arr[0] = h->arr[--h->size];
    int i = 0;
    while (1) {
        int l = 2 * i + 1, r = 2 * i + 2, smallest = i;
        if (l < h->size && h->arr[l] < h->arr[smallest]) smallest = l;
        if (r < h->size && h->arr[r] < h->arr[smallest]) smallest = r;
        if (smallest == i) break;
        unsigned long long t = h->arr[i];
        h->arr[i] = h->arr[smallest];
        h->arr[smallest] = t;
        i = smallest;
    }
    return min;
}
int heap_empty(Heap* h) { return h->size == 0; }
void heap_free(Heap* h) { free(h->arr); free(h); }
unsigned long long get_nth(int n, int* overflow) {
    if (n <= 0) return 0;
    Heap* heap = heap_create(256);
    heap_push(heap, 1);

    int count = 0;
    unsigned long long last = 0, cur;

    while (!heap_empty(heap)) {
        cur = heap_pop(heap);
        //пропускаем дубликаты
        if (cur == last) continue;
        last = cur;

        if (cur > 1) {
            count++;
            if (count == n) {
                *overflow = 0;
                heap_free(heap);
                return cur;
            }
        }
        //потомки
        if (cur <= ULLONG_MAX / 3) heap_push(heap, cur * 3);
        if (cur <= ULLONG_MAX / 5) heap_push(heap, cur * 5);
        if (cur <= ULLONG_MAX / 7) heap_push(heap, cur * 7);
    }
    *overflow = 1;
    heap_free(heap);
    return 0;
}

int is_number_ok(const char* s) {
    if (!s || *s == '\0') return 0;
    //отрицательное
    if (*s == '-') {
        s++;
        if (*s == '\0') return 0;
    }
    //цифры
    for (; *s; s++) {
        if (*s < '0' || *s > '9') return 0;
    }
    return 1;
}

//ручной парсинг числа из строки
long long parse_ll(const char* s) {
    long long result = 0;
    int sign = 1;
    if (*s == '-') {
        sign = -1;
        s++;
    }
    while (*s >= '0' && *s <= '9') {
        result = result * 10 + (*s - '0');
        s++;
    }
    return result * sign;
}

int main() {
    FILE* output;
    output = fopen("compare.txt", "w");
    char line[256];
    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = '\0';
        if (strlen(line) == 0) continue;
        if (!is_number_ok(line)) {
            fprintf(output,"error\n");
            continue;
        }
        long long n = parse_ll(line);
        if (n <= 0) {
            fprintf(output,"error\n");
            continue;
        }
        int overflow = 0;
        unsigned long long res = get_nth((int)n, &overflow);
        if (overflow || res == 0) {
            fprintf(output,"overflow\n");
        }
        else {
            fprintf(output, "%llu\n", res);
        }
    }
    return 0;
}