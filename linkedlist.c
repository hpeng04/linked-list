#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct Node {
    int data;
    struct Node *next;
};

struct List {
    struct Node *head;
    size_t len;
};

struct List *createList() {
    struct List *list = malloc(sizeof(struct List));
    list->len = 0;
    list->head = NULL;
    return list;
}

void addToFront(struct List *list, int val) {
    struct Node *node = malloc(sizeof(struct Node));
    node->data = val;
    node->next = list->head;
    list->head = node;
    ++list->len;
}

void append(struct List *list, int val) {
    if (list->len == 0) {
        struct Node *node = malloc(sizeof(struct Node));
        list->head = node;
        node->data = val;
        node->next = NULL;
        ++list->len;
    }
    else {
        struct Node *cur = list->head;
        for (size_t i = 0; i < list->len-1; ++i) {
            cur = cur->next;
        }
        struct Node *node = malloc(sizeof(struct Node));
        cur->next = node;
        node->data = val;
        node->next = NULL;
        ++list->len;
    }
}

void pop(struct List *list) {
    if (list->len == 0) return;
    else if (list->len == 1) {
        struct Node *cur = list->head;
        list->head = NULL;
        free(cur);
        --list->len;
        return;
    }
    else {
        struct Node *cur = list->head;
        struct Node *prev = NULL;
        for (size_t i = 0; i < list->len-1; ++i) {
            prev = cur;
            cur = cur->next;
        }
        prev->next = NULL;
        free(cur);
        --list->len;
    }
}

void rmv(struct List *list, int index) {
    if (list->len == 0 || index < 0 || index >list->len-1) {
        printf("Invalid index\n");
        return;
    } 
    else if (index == 0) {
        struct Node *cur = list->head;
        list->head = cur->next;
        free(cur);
        --list->len;
    }
    else {
        struct Node *cur = list->head;
        struct Node *prev = NULL;
        for (size_t i = 0; i < index; ++i) {
            prev = cur;
            cur = cur->next;
        } 
        prev->next = cur->next;
        free(cur);
        --list->len; 
    }
}

int findElem(struct List *list, size_t index) {
    assert(index < list->len);
    struct Node *cur = list->head;
    for (size_t i = 0; i < index; ++i) {
        cur = cur->next;
    }
    return cur->data;
}

void printList(struct List *list) {
    printf("[");
    for (size_t i = 0; i < list->len; ++i) {
        printf("%d", findElem(list, i));
        if (i < list->len-1) printf(", ");
    }
    printf("]\n");
}

void deleteNode(struct Node *node) {
    if (!node) return;
    deleteNode(node->next);
    free(node);
}

void deleteList(struct List *list) {
    if (!list) return;
    deleteNode(list->head);
    free(list);
}

void insert(struct List *list, int val, int index) {
    if (index > list->len || index < 0 || list->len == 0) {
        printf("Invalid index\n");
    }
    else {
        struct Node *cur = list->head;
        struct Node *prev = NULL;
        for (size_t i = 0; i < index; ++i) {
            prev = cur;
            cur = cur->next;
        }
        struct Node *node = malloc(sizeof(struct Node));
        node->data = val;
        prev->next = node;
        node->next = cur;
        ++list->len;
    }
}

int main(int argc, const char **argv) {
    struct List *l = createList();
    if (argc == 2 && strcmp(argv[1], "-debug") == 0) {
        printList(l);
        printf("append 9: ");
        append(l, 9);
        printList(l);
        printf("add 1 to front: ");
        addToFront(l, 1);
        printList(l);
        printf("add 2 to front: ");
        addToFront(l, 2);
        printList(l);
        printf("add 4 to front: ");
        addToFront(l, 4);
        printList(l);
        printf("pop: ");
        pop(l);
        printList(l);
        printf("append 5: ");
        append(l, 5);
        printList(l);
        printf("remove index 1: ");
        rmv(l, 1);
        printList(l);
        printf("Insert 8 at index 1: ");
        insert(l, 8, 1);
        printList(l);
    }
    else if (argc == 1) {
        char cmd[10];
        while (strcmp(cmd, "q") != 0) {
            scanf(" %s", cmd);
            int val = 0;
            if (strcmp(cmd, "a") == 0) {
                scanf(" %d", &val);
                append(l, val);
                printf("Appended %d to linked list:\n", val);
                printList(l);
            }
            else if (strcmp(cmd, "pop") == 0) {
                pop(l);
                printf("Popped last value from linked list:\n");
                printList(l);
            }
            else if (strcmp(cmd, "r") == 0) {
                scanf(" %d", &val);
                rmv(l, val);
                printf("Removed index %d from linked list:\n", val);
                printList(l);
            }
            else if (strcmp(cmd, "af") == 0) {
                scanf(" %d", &val);
                addToFront(l, val);
                printf("Added %d to front of linked list:\n", val);
                printList(l);
            }
            else if (strcmp(cmd, "q") == 0);
            else if (strcmp(cmd, "p") == 0) {
                printList(l);
                printf("List Length: %lu\n", l->len);
            }
            else if (strcmp(cmd, "i") == 0) {
                int index = -1;
                scanf(" %d", &val);
                scanf(" %d", &index);
                insert(l, val, index);
                printList(l);
            }
            else if (strcmp(cmd, "help") == 0) {
                printf("a [x] - append x to back of list\naf [x] - append x to front of list\ni [x] [index] - insert value x at index in linked list\nr [x] - remove index x from list\npop - pop the last value from list\np - print list\nq - quit\n");
            }
            else {
                printf("Invalid command\nType 'help' for a list of commands\n");
            }
        }
    }
    else {
        printf("Usage: ./a.out {-debug}\n");
    }
    deleteList(l);
}