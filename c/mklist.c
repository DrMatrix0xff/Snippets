#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *next;
    int val;
};

struct node *make_node(int val) {
    struct node *p;
    p = (struct node *) malloc(sizeof (*p));
    if (p != NULL) {
        p->val = val;
        p->next = NULL;
    }
    return p;
}

struct node *merge_sorted_lists(struct node *sl1, struct node *sl2) {
    struct node *p;
    struct node **pp = &p;
    for (; ;) {
        if (! sl1) { *pp = sl2; break; }
        if (! sl2) { *pp = sl1; break; }
        if (sl1->val <= sl2->val) { *pp = sl1; sl1 = sl1->next; } else { *pp = sl2; sl2 = sl2->next; }
        pp = &(*pp)->next;
    }
    return p;
}

int main(int argc, char *argv[]) {
    struct node *head = NULL, *head1 = NULL, *p;
    struct node **pp;
    int i;

    for (i = 1; i < 100; i += 2) {
        p = make_node(i);
        if (! p) {
            fprintf(stderr, "malloc error\n");
            exit(1);
        }
        pp = &head;
        while (*pp)
            pp = &(*pp)->next;
        *pp = p;
    }

    for (i = 2; i < 100; i += 2) {
        p = make_node(i);
        if (! p) {
            fprintf(stderr, "malloc error\n");
            exit(1);
        }
        pp = &head1;
        while (*pp)
            pp = &(*pp)->next;
        *pp = p;
    }

    head = merge_sorted_lists(head, head1);

    pp = &head;
    while (*pp) {
        if ((*pp)->next)
            printf(" %d --> ", (*pp)->val);
        else
            printf(" %d\n", (*pp)->val);
        pp = &(*pp)->next;
    }

    return 0;
}
