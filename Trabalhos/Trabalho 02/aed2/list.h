typedef struct Charge {
    int value;
    struct Charge *next;
} ChargeNode;

typedef struct ChargeList {
    int size;
    ChargeNode *head;
    ChargeNode *tail;
} ChargeList;

ChargeList *createList() {
    ChargeList *list = (ChargeList*) malloc(sizeof(ChargeList));
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

ChargeNode *createElement(int element) {
    ChargeNode *newCharge = (ChargeNode*) malloc(sizeof(ChargeNode));
    newCharge->value = element;
    newCharge->next = NULL;
    return newCharge;
}

void insertList(ChargeList *list, ChargeNode *charge) {
    if (list->size == 0) {
        list->head = charge;
        list->tail = charge;
    } else {
        list->tail->next = charge;
        list->tail = charge;
    }
    list->size ++;
}

void removeChargeNodeFromBegin(ChargeList *list) {
    ChargeNode *temp = list->head->next;
    free(list->head);
    list->head = temp;
    list->size --;
}

int isEmptyList(ChargeList *list) {
    return list->size == 0 ? 1 : 0;
}

void printList(ChargeList *list) {
    ChargeNode *walker = list->head;
    while (walker != NULL) {
        printf("%d ", walker->value);
        walker = walker->next;
    }
}