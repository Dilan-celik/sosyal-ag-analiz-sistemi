#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED 0
#define BLACK 1
#define MAX_USERS 100
#define MAX_ID 1000

typedef struct Node {
    int id;
    struct Node* next;
} Node;

typedef struct RBNode {
    int id;
    int color;
    struct RBNode *left, *right, *parent;
    Node* friends;
} RBNode;

RBNode* root = NULL;

RBNode* create_node(int id) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->id = id;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
    node->friends = NULL;
    return node;
}

void rotate_left(RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rotate_right(RBNode* x) {
    RBNode* y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void fix_insert(RBNode* node) {
    while (node != root && node->parent->color == RED) {
        RBNode* grandparent = node->parent->parent;
        if (node->parent == grandparent->left) {
            RBNode* uncle = grandparent->right;
            if (uncle && uncle->color == RED) {
                node->parent->color = uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rotate_left(node);
                }
                node->parent->color = BLACK;
                grandparent->color = RED;
                rotate_right(grandparent);
            }
        } else {
            RBNode* uncle = grandparent->left;
            if (uncle && uncle->color == RED) {
                node->parent->color = uncle->color = BLACK;
                grandparent->color = RED;
                node = grandparent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotate_right(node);
                }
                node->parent->color = BLACK;
                grandparent->color = RED;
                rotate_left(grandparent);
            }
        }
    }
    root->color = BLACK;
}

void add_user(int id) {
    RBNode* new_node = create_node(id);
    RBNode* y = NULL;
    RBNode* x = root;

    while (x) {
        y = x;
        if (id < x->id) x = x->left;
        else if (id > x->id) x = x->right;
        else {
            free(new_node);
            return;
        }
    }

    new_node->parent = y;
    if (!y) root = new_node;
    else if (id < y->id) y->left = new_node;
    else y->right = new_node;

    fix_insert(new_node);
}

RBNode* find_user(int id) {
    RBNode* current = root;
    while (current) {
        if (id == current->id) return current;
        else if (id < current->id) current = current->left;
        else current = current->right;
    }
    return NULL;
}

void add_friendship(int id1, int id2) {
    if (id1 == id2) return;

    RBNode* u1 = find_user(id1);
    RBNode* u2 = find_user(id2);
    if (!u1 || !u2) return;

    Node* temp = u1->friends;
    while (temp) {
        if (temp->id == id2) return;
        temp = temp->next;
    }

    Node* f1 = (Node*)malloc(sizeof(Node));
    f1->id = id2;
    f1->next = u1->friends;
    u1->friends = f1;

    Node* f2 = (Node*)malloc(sizeof(Node));
    f2->id = id1;
    f2->next = u2->friends;
    u2->friends = f2;
}

void dfs_distance(RBNode* node, int depth, int current, int* visited, int* result, int* count) {
    if (!node || visited[node->id] || current > depth) return;

    visited[node->id] = 1;
    if (current == depth) {
        result[(*count)++] = node->id;
        return;
    }

    Node* f = node->friends;
    while (f) {
        RBNode* next = find_user(f->id);
        if (next && !visited[next->id])
            dfs_distance(next, depth, current + 1, visited, result, count);
        f = f->next;
    }
}

void find_friends_at_distance(int id, int dist) {
    int visited[MAX_ID] = {0}, result[MAX_USERS], count = 0;

    RBNode* start = find_user(id);
    if (!start) return;

    visited[id] = 1;
    Node* f = start->friends;
    while (f) {
        RBNode* friend_node = find_user(f->id);
        if (friend_node && !visited[friend_node->id]) {
            dfs_distance(friend_node, dist, 1, visited, result, &count);
        }
        f = f->next;
    }

    printf("Mesafe %d arkadaslar: ", dist);
    if (count == 0) printf("Yok");
    int i;
    for ( i = 0; i < count; i++) printf("%d ", result[i]);
    printf("\n");
}

void mutual_friends(int id1, int id2) {
    RBNode* u1 = find_user(id1);
    RBNode* u2 = find_user(id2);
    if (!u1 || !u2) return;

    int mutual = 0;
    Node* f1 = u1->friends;
    printf("Ortak Arkadaslari Bulunan ID'ler (%d %d):\n", id1, id2);
    while (f1) {
        Node* f2 = u2->friends;
        while (f2) {
            if (f1->id == f2->id) {
                printf("%d ", f1->id);
                mutual++;
                break;
            }
            f2 = f2->next;
        }
        f1 = f1->next;
    }

    printf("\nOrtak arkadas sayisi: %d\n", mutual);
}

void dfs_community(RBNode* node, int* visited, int* members, int* count) {
    if (!node || visited[node->id]) return;

    visited[node->id] = 1;
    members[(*count)++] = node->id;

    Node* f = node->friends;
    while (f) {
        RBNode* friend_node = find_user(f->id);
        if (friend_node && !visited[friend_node->id])
            dfs_community(friend_node, visited, members, count);
        f = f->next;
    }
}

void find_communities() {
    int visited[MAX_ID] = {0};
    int members[MAX_USERS], count;
    printf("Topluluk tespitine geciliyor:\n");
    void traverse(RBNode* node) {
        if (!node) return;
        traverse(node->left);
        if (!visited[node->id]) {
            count = 0;
            dfs_community(node, visited, members, &count);
            printf("Topluluk: ");
            int i;
            for (i = 0; i < count; i++) printf("%d ", members[i]);
            printf("\n");
        }
        traverse(node->right);
    }
    traverse(root);
}

int influence(int id) {
    int visited[MAX_ID] = {0}, members[MAX_USERS], count = 0;
    RBNode* user = find_user(id);
    if (!user) return 0;
    dfs_community(user, visited, members, &count);
    return count - 1;
}

void load_data(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        perror("Dosya acilamadi");
        exit(1);
    }

    char line[100];
    while (fgets(line, sizeof(line), f)) {
        int id1, id2;
        if (sscanf(line, "USER %d", &id1) == 1) {
            add_user(id1);
        } else if (sscanf(line, "FRIEND %d %d", &id1, &id2) == 2) {
            add_friendship(id1, id2);
        }
    }

    fclose(f);
}

int main() {
    load_data("veriseti.txt");

    int id;
    printf("Arkadaslarini analiz etmek istediginiz kullanici ID'sini girin: ");
    scanf("%d", &id);

    printf("Kullanici ID: %d\n", id);
    find_friends_at_distance(id, 1);
    find_friends_at_distance(id, 2);
    printf("Kullanici etkisi: %d\n", influence(id));

    int id2;
    printf("Ortak arkadas analizi icin ikinci ID'yi girin: ");
    scanf("%d", &id2);
    mutual_friends(id, id2);

    find_communities();

    return 0;
}

