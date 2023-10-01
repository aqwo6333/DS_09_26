#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct treeNode {
    int data;
    struct treeNode* left, * right;
} treeNode;

treeNode* createNode(int data, treeNode* left, treeNode* right) {
    treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
    if (newNode == NULL) {
        printf("메모리 할당에 실패했습니다.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

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

// 재귀적 방법
treeNode* search(treeNode* root, int key, int* visitNodes) {
    if (root == NULL) return NULL;
    (*visitNodes)++;

    if (key == root->data) return root;
    else if (key < root->data)
        return search(root->left, key, visitNodes);
    else
        return search(root->right, key, visitNodes);
}

treeNode* insert_node(treeNode* root, int key, int* visitNodes) {
    (*visitNodes)++;
    if (root == NULL)
        return new_node(key);
    if (key < root->data)
        root->left = insert_node(root->left, key, visitNodes);
    else if (key > root->data)
        root->right = insert_node(root->right, key, visitNodes);

    return root;
}

treeNode* delete_node(treeNode* root, int key, int* visitNodes) {
    if (root == NULL) return root;
    (*visitNodes)++;

    if (key < root->data)
        root->left = delete_node(root->left, key, visitNodes);
    else if (key > root->data)
        root->right = delete_node(root->right, key, visitNodes);
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
        root->right = delete_node(root->right, temp->data, visitNodes);
    }
    return root;
}


void inorder_iter(treeNode* root, int* visitNodes) {
    if (root != NULL) {
        inorder_iter(root->left, visitNodes);
        printf("%d ", root->data);
        (*visitNodes)++;
        inorder_iter(root->right, visitNodes);
    }
}

treeNode* insert_node_iter(treeNode* root, int key, int* visitNodes) {
    (*visitNodes)++;
    treeNode* newNode = createNode(key, NULL, NULL);
    if (root == NULL)
        return newNode;
    treeNode* current = root;
    treeNode* parent = NULL;
    while (current != NULL) {
        parent = current;
        if (key < current->data)
            current = current->left;
        else if (key > current->data)
            current = current->right;
        else {
            free(newNode);
            return root;
        }
    }
    if (key < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;
    return root;
}

treeNode* delete_node_iter(treeNode* root, int key, int* visitNodes) {
    treeNode* parent = NULL;
    treeNode* current = root;

    while (current != NULL) {
        (*visitNodes)++;

        if (key == current->data)
            break;
        parent = current;
        if (key < current->data)
            current = current->left;
        else
            current = current->right;
    }
    if (current == NULL)
        return root;
    if (current->left == NULL && current->right == NULL) {
        if (current != root) {
            if (parent->left == current)
                parent->left = NULL;
            else
                parent->right = NULL;
        }
        else
            root = NULL;
        free(current);
    }
    else if (current->left == NULL) {
        if (current != root) {
            if (parent->left == current)
                parent->left = current->right;
            else
                parent->right = current->right;
        }
        else
            root = current->right;
        free(current);
    }
    else if (current->right == NULL) {
        if (current != root) {
            if (parent->left == current)
                parent->left = current->left;
            else
                parent->right = current->left;
        }
        else
            root = current->left;
        free(current);
    }
    else {
        treeNode* temp = minvalue_node(current->right);
        current->data = temp->data;
        current->right = delete_node_iter(current->right, temp->data, visitNodes);
    }
    return root;
}


int main(void) {
    // 트리 생성
    treeNode* n14 = createNode(64, NULL, NULL);
    treeNode* n13 = createNode(62, NULL, NULL);
    treeNode* n12 = createNode(42, NULL, NULL);
    treeNode* n11 = createNode(70, NULL, NULL);
    treeNode* n10 = createNode(63, n13, n14);
    treeNode* n9 = createNode(55, NULL, NULL);
    treeNode* n8 = createNode(46, n12, NULL);
    treeNode* n7 = createNode(25, NULL, NULL);
    treeNode* n6 = createNode(65, n10, n11);
    treeNode* n5 = createNode(53, n8, n9);
    treeNode* n4 = createNode(16, NULL, n7);
    treeNode* n3 = createNode(74, n6, NULL);
    treeNode* n2 = createNode(41, n4, n5);
    treeNode* n1 = createNode(60, n2, n3);

    // 루트 노드 설정
    treeNode* root = n1;

    int visitNodes = 0;

    printf(" s : 검색\n i : 노드 추가\n d : 노드 삭제\n t : 중위 순회\n I : 노드 추가(반복)\n D : 노드 삭제(반복)\n c : 종료\n");
    char item;
    while (1) {
        printf("메뉴 입력 : ");
        scanf_s(" %c", &item, sizeof(item));

        switch (item) {
        case 's':
            printf("검색할 값 입력: ");
            int key_s = 0;
            scanf_s("%d", &key_s);
            treeNode* result_s = search(root, key_s, &visitNodes);
            if (result_s) {
                printf("방문한 노드의 수: %d\n", visitNodes);
                printf("검색 결과: %d\n", result_s->data);
            }
            else {
                printf("노드를 찾을 수 없습니다.\n");
            }
            visitNodes = 0;
            inorder_iter(root, &visitNodes);
            printf("\n");
            break;
        case 'i':
            printf("삽입할 값 입력: ");
            int key_i = 0;
            scanf_s("%d", &key_i);
            root = insert_node(root, key_i, &visitNodes);
            printf("방문한 노드의 수: %d\n", visitNodes);
            visitNodes = 0;
            inorder_iter(root, &visitNodes);
            printf("\n");
            break;
        case 'd':
            printf("삭제할 값 입력: ");
            int key_d = 0;
            scanf_s("%d", &key_d);
            root = delete_node(root, key_d, &visitNodes);
            printf("방문한 노드의 수: %d\n", visitNodes);
            visitNodes = 0;
            inorder_iter(root, &visitNodes);
            printf("\n");
            break;

        case 't':
            printf("중위 순회 결과: ");
            visitNodes = 0;
            inorder_iter(root, &visitNodes);
            printf("\n");
            printf("방문한 노드의 수: %d\n", visitNodes);
            printf("\n");
            break;
        case 'I':
            printf("삽입할 값 입력: ");
            int key_I = 0;
            scanf_s("%d", &key_I);
            root = insert_node_iter(root, key_I, &visitNodes);
            printf("방문한 노드의 수: %d\n", visitNodes);
            visitNodes = 0;
            inorder_iter(root, &visitNodes);
            printf("\n");
            break;
        case 'D':
            printf("삭제할 값 입력: ");
            int key_D = 0;
            scanf_s("%d", &key_D);
            root = delete_node_iter(root, key_D, &visitNodes);
            printf("방문한 노드의 수: %d\n", visitNodes);
            visitNodes = 0;
            inorder_iter(root, &visitNodes);
            printf("\n");
            break;

        case 'c':
            exit(0);
        default:
            printf("잘못된 입력입니다. 다시 시도하세요.\n");
            break;
        }
    }

    return 0;
}
