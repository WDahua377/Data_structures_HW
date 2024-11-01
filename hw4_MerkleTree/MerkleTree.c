#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

unsigned long hash(char* key);

typedef struct nodes{
        int ID, level, levelNum;
        char *string;
        unsigned long value;
        struct nodes* left;
        struct nodes* right;
    }nodes;

int ConstructTree(int strings, int StrMaxLen, nodes *node){
    unsigned long hashvalue;
    int childID = 0, nextID = strings;
    int lastnodeID = strings - 1;   // 上一個 node

    while(lastnodeID != childID){

        // check if the tree isn't balance，i.e when the number of strings is odd (lastnode is even)
        if(lastnodeID % 2 == 0 && lastnodeID != 0){
            node[nextID].value = node[lastnodeID].value;  // copy the last node (sibling node)
            node[nextID].ID = nextID;
            node[nextID].right = NULL;
            node[nextID].left = NULL;
            nextID++;
            lastnodeID++;
        }

        // construct parent node 

        /* Hashing Function :
           1. Adding two unsigned long hash values
           2. Transform the unsigned long hash value to a char string
           3. Hash the char string to acquire the hashed value */

        memset(node[nextID].string, 0, StrMaxLen*sizeof(node[nextID].string[0]));   // initialize

        hashvalue = node[childID].value + node[childID+1].value;
        sprintf(node[nextID].string, "%lu", hashvalue);   // set node[parentID].string  snprintf?
        node[nextID].value = hash(node[nextID].string); // Hash the char string
        node[nextID].left = &node[childID];
        node[nextID].right = &node[childID+1];
        node[nextID].ID = nextID;
        
        if(childID == lastnodeID-1){    // level end, update lastnodeID
            lastnodeID = nextID;
        }

        // construct next parent node, nextID is patentID
        childID += 2;   nextID++;
    }

    return lastnodeID;
}

void CheckNode(nodes *ptr, nodes *node, int *queue, int *tail, int checkID, int leftFlag){
    nodes nextNode;
    unsigned long hashvalue;

    if(ptr != NULL){    // null表示該點為複製的 不往下檢查 不加入queue
        nextNode = (*ptr);
        if(strlen(nextNode.string) != 0){
            node[nextNode.ID].level = node[checkID].level + 1;
            if(leftFlag == 1)
                node[nextNode.ID].levelNum = node[checkID].levelNum * 2;
            else
                node[nextNode.ID].levelNum = (node[checkID].levelNum * 2) + 1;
            
            printf("1 %d %d\n", node[nextNode.ID].level, node[nextNode.ID].levelNum);
            fflush(NULL);
            scanf("%lu", &hashvalue);
            if(node[nextNode.ID].value != hashvalue){
                queue[++(*tail)] = nextNode.ID;  // push
            }
        }
    }
}

int main(){
    int strings, StrMaxLen;
    int incorrect_strings = 0;
    scanf("%d%d", &strings, &StrMaxLen);

    char answer[StrMaxLen*strings];
    memset(answer, 0, StrMaxLen*strings*sizeof(answer[0]));    // initialize

    if(StrMaxLen < 21)
        StrMaxLen = 21; // for 8-byte unsigned long

    // n is the max number of nodes in the tree
    int n = ceil(log10(strings)/log10(2));  // mind the parameter type of the function
    n = pow(2, n+1) - 1;
    nodes node[n];

    // input
    for(int i = 0; i < strings; i++){
        node[i].ID = i;
        node[i].string = malloc(StrMaxLen * sizeof(char));
        memset(node[i].string, 0, StrMaxLen * sizeof(char));
        scanf("%s", node[i].string);
        node[i].value = hash(node[i].string);
    }

    // construct tree
    int lastnodeID = ConstructTree(strings, StrMaxLen, node);
    

    // Query
    int checkID  = lastnodeID;
    int queue[n], front = -1, tail = -1;
    nodes *ptr;
    char s[StrMaxLen];
    unsigned long hashvalue;

    printf("1 0 0\n");  // "1" for query action, "1 0 0" means asking for root (0,0)
    fflush(NULL);
    scanf("%lu", &hashvalue);   // origin hashvalue

    node[checkID].level = 0;
    node[checkID].levelNum = 0;
    if(node[checkID].value != hashvalue){    // 如果 root 有錯誤，push root in queue
        queue[++tail] = checkID;
    }   //if not, then queue is empty: front == tail == -1

    // while queue is not empty
    while(front != tail){
        checkID = queue[++front];    // pop

        // 如果此點表示的是原始數據（node[0]~node[strings]）
        if(checkID < strings){
            memset(s, 0, StrMaxLen*sizeof(s[0]));
            sprintf(s, "\n%s", node[checkID].string);
            strcat(answer, s);
            incorrect_strings++;
        }

        // 否，則繼續檢查
        else{
            // 檢查左邊，錯誤則放入Q
            ptr = node[checkID].left;
            int leftFlag = 1;
            CheckNode(ptr, node, queue, &tail, checkID, leftFlag);
            

            // 檢查右邊，錯誤則放入Q
            ptr = node[checkID].right;
            leftFlag = 0;
            CheckNode(ptr, node, queue, &tail, checkID, leftFlag);
        }
    }
    printf("2 %d", incorrect_strings);
    printf("%s",answer);
    fflush(NULL);

    // release memory
    for(int i = 0; i < strings; i++){
        free(node[i].string);
    }

    return 0;
}

unsigned long hash(char* key){
    unsigned long h = 3323198485ul;
    for (; *key; ++key) {
        h ^= *key;
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    return h;
}
