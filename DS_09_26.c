#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    int data;
    struct treeNode* left, * right;
} treeNode;

int visitNodes = 0;

// 트리 생성
treeNode n14 = { 64, NULL, NULL };
treeNode n13 = { 62, NULL, NULL };
treeNode n12 = { 42, NULL, NULL };
treeNode n11 = { 70, NULL, NULL};
treeNode n10 = { 63, &n13, &n14};
treeNode n9 = { 55, NULL, NULL};
treeNode n8 = { 46, &n12, NULL};
treeNode n7 = { 25, NULL, NULL};
treeNode n6 = { 65, &n10, &n11};
treeNode n5 = { 53, &n8, &n9};
treeNode n4 = { 16, NULL, &n7};
treeNode n3 = { 74, &n6, NULL};
treeNode n2 = { 41, &n4, &n5};
treeNode n1 = { 60, &n2, &n3};
treeNode* root = &n1;

treeNode* minvalue_node(treeNode* node) {
    treeNode* curr = node;
    while (curr->left != NULL)
        curr = curr->left;
    return curr;
}

treeNode* new_node(int key) {
    treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
    newNode->data = key;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// 반복적 방법
treeNode* search(treeNode* root, int key) {
    visitNodes = 0;

    while (root != NULL) {
        visitNodes++;

        if (key == root->data)
            return root;
        else if (key < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

treeNode* insert_node(treeNode* node, int key) {
    if (node == NULL)
        return new_node(key);
    if (node->data > key)
        node->left = insert_node(node->left, key);
    else if (node->data < key)
        node->right = insert_node(node->right, key);
    return node;
}

treeNode* delete_node(treeNode* root, int key) {
    if (root == NULL) return root;
    if (key < root->data)
        root->left = delete_node(root->left, key);
    else if (key > root->data)
        root->right = delete_node(root->right, key);
    else {
        if (root->left == NULL) {
            treeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            treeNode* temp = root->left;
            free(root);
            return temp;
        }
        treeNode* temp = minvalue_node(root->right);
        root->data = temp->data;
        root->right = delete_node(root->right, temp->data);
    }
    return root;
}

void inorder_iter(treeNode* root) {
    if (root) {
        inorder_iter(root->left);
        printf("%d ", root->data);
        inorder_iter(root->right);
    }
}

int main(void) {
    printf(" s : 검색\n i : 노드 추가\n d : 노드 삭제\n t : 중위 순회\n I : 노드 추가(반복)\n D : 노드 삭제(반복)\n c : 종료\n");
    char item;
    scanf_s(" %c", &item, sizeof(item));

    switch (item) {
        case 's':
            printf("검색할 값 입력: ");
            int key_s = 0;
            scanf_s("%d", &key_s);
            search(&root, key_s);
            printf("방문한 노드의 수: %d\n", visitNodes);
            printf("나머지 노드: ");
            inorder_iter(root->right);
            printf("\n");
            break;
        case 'i':
            printf("삽입할 값 입력: ");
            int key_i = 0;
            scanf_s("%d", &key_i);
            insert_node(&root, key_i);
            break;
        case 'd':
            printf("삭제할 값 입력: ");
            int key_d = 0;
            scanf_s("%d", &key_d);
            delete_node(&root, key_d);
            break;
        case 't':
            inorder_iter(&root);
            break;
        default:
            printf("error\n");
                   
    }
        

    return 0;
}