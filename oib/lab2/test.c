#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>


typedef struct CharFreq {
    wchar_t ch;
    int count;
    struct CharFreq *next;
} CharFreq;

typedef struct WordNode {
    wchar_t *word;
    struct WordNode *next;
} WordNode;

typedef struct Group {
    int length;
    WordNode *words;
    struct Group *next;
} Group;

void add_char(CharFreq **head, wchar_t ch) {
    CharFreq *current = *head;

    while (current) {
        if (current->ch == ch) {
            current->count++;
            return;
        }
        current = current->next;
    }

    CharFreq *node = malloc(sizeof(CharFreq));
    node->ch = ch;
    node->count = 1;
    node->next = *head;
    *head = node;
}



void add_word(Group **groups, wchar_t *word, int length) {
    Group *g = *groups;

    while (g) {
        if (g->length == length)
            break;
        g = g->next;
    }

    if (!g) {
        g = malloc(sizeof(Group));
        g->length = length;
        g->words = NULL;
        g->next = *groups;
        *groups = g;
    }

    WordNode *node = malloc(sizeof(WordNode));
    node->word = wcsdup(word);
    node->next = g->words;
    g->words = node;
}



void free_charfreq(CharFreq *head) {
    while (head) {
        CharFreq *tmp = head;
        head = head->next;
        free(tmp);
    }
}

void free_groups(Group *groups) {
    while (groups) {
        WordNode *w = groups->words;
        while (w) {
            WordNode *tmpw = w;
            w = w->next;
            free(tmpw->word);
            free(tmpw);
        }
        Group *tmpg = groups;
        groups = groups->next;
        free(tmpg);
    }
}



int main() {
    setlocale(LC_ALL, "");

    FILE *file = fopen("input.txt", "r");
    wchar_t *text = NULL;
    size_t size = 0;
    size_t len = 0;

    wint_t ch;
    while ((ch = fgetwc(file)) != WEOF) {
        if (len + 1 >= size) {
            size = size == 0 ? 16 : size * 2;
            text = realloc(text, size * sizeof(wchar_t));
        }
        text[len++] = (wchar_t)ch;
    }

    if (text)
        text[len] = L'\0';

    fclose(file);

    int total_chars = len;



    CharFreq *freq_list = NULL;

    for (size_t i = 0; i < len; i++) {
        if (text[i] != L' ')
            add_char(&freq_list, text[i]);
    }

    Group *groups = NULL;

    wchar_t *word = NULL;
    size_t word_size = 0;
    size_t word_len = 0;

    for (size_t i = 0; i <= len; i++) {

        if (text[i] != L' ' && text[i] != L'\0' && text[i] != L'\n') {

            if (word_len + 1 >= word_size) {
                word_size = word_size == 0 ? 8 : word_size * 2;
                word = realloc(word, word_size * sizeof(wchar_t));
            }

            word[word_len++] = text[i];

        } else {

            if (word_len > 0) {
                word[word_len] = L'\0';
                add_word(&groups, word, word_len);
                word_len = 0;
            }
        }
    }



    wprintf(L"Частота символов:\n");

    CharFreq *cf = freq_list;
    while (cf) {
        wprintf(L"%lc : %.6f\n",
                cf->ch,
                (double)cf->count / total_chars);
        cf = cf->next;
    }



    wprintf(L"\nГруппы слов по длине:\n");

    Group *g = groups;
    while (g) {
        wprintf(L"%d букв: ", g->length);

        WordNode *w = g->words;
        while (w) {
            wprintf(L"%ls ", w->word);
            w = w->next;
        }

        wprintf(L"\n");
        g = g->next;
    }

    free(text);
    free(word);
    free_charfreq(freq_list);
    free_groups(groups);

    return 0;

}