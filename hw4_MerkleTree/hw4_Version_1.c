#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

unsigned long hash(char* key);

int main(){
    int strings, StrMaxLen;
    scanf("%d%d", &strings, &StrMaxLen);

    if(StrMaxLen < 21)
        StrMaxLen = 21; // for 8-byte unsigned long

    //n is the max number of nodes in the tree
    int n = ceil(log10(strings)/log10(2));  // minded the parameter type of the function
    n = pow(2,n+1)-1;
    char answer[StrMaxLen*strings];
    memset(answer, 0, StrMaxLen*strings*sizeof(answer[0]));    // initialize
    int incorrect_strings = 0;

    struct nodes{
        int ID, level, nodeID;
        char string[StrMaxLen];
        unsigned long value;
        struct nodes* left;
        struct nodes* right;
    }node[n];

    // input
    for(int i = 0; i < strings; i++){
        node[i].ID = i;
        memset(node[i].string, 0, StrMaxLen*sizeof(node[i].string[0]));
        scanf("%s", node[i].string);
        node[i].value = hash(node[i].string);
    }

    // construct tree
    unsigned long hashvalue;
    int childID = 0, parentID = strings;
    int lastnodeID = strings-1;

    while(lastnodeID != childID){
        if(lastnodeID % 2 == 0 && lastnodeID != 0){    // check if the tree isn't balance
            node[parentID].value = node[lastnodeID].value;  // copy the last node
            node[parentID].ID = parentID;
            node[parentID].right = NULL;
            node[parentID].left = NULL;
            parentID++;
            lastnodeID++;
        }
        hashvalue = node[childID].value + node[childID+1].value;    // adding the two unsigned long hash values
        memset(node[parentID].string, 0, StrMaxLen*sizeof(node[parentID].string[0]));
        sprintf(node[parentID].string, "%lu", hashvalue);           // I2S get node[parentID].string    snprintf?
        node[parentID].value = hash(node[parentID].string); // Hash the char string
        node[parentID].left = &node[childID];
        node[parentID].right = &node[childID+1];
        node[parentID].ID = parentID;
        
        if(childID == lastnodeID-1){    // level end
            lastnodeID = parentID;
        }
        childID += 2;   parentID++;
    }

    // for(int i = 0; i < n;i++){
    //     printf("string[%d]: %s\n", i, node[i].string);
    //     printf("value[%d]: %lu\n", i, node[i].value);
    // }

    // Query
    parentID = lastnodeID;
    int queue[n], front = -1, tail = -1;
    struct nodes *ptr, temp;
    char s[StrMaxLen];

    printf("1 0 0\n");
    fflush(NULL);
    scanf("%lu", &hashvalue);   // correct hashvalue
    node[parentID].level = 0;
    node[parentID].nodeID = 0;
    if(node[parentID].value != hashvalue){    // 如果root有錯誤
        queue[++tail] = parentID;  // push root in queue
    }   //if not, then queue is empty: front == tail == -1

    while(front != tail){
        parentID = queue[++front];    // pop
        // printf("checkid: %d\n", parentID);
        // 如果此點表示的是原始數據
        if(parentID < strings){
            // printf("len[%d]: %d\n", parentID, strlen(node[parentID].string));
            memset(s, 0, StrMaxLen*sizeof(s[0]));
            sprintf(s, "\n%s", node[parentID].string);
            strcat(answer, s);
            incorrect_strings++;
        }
        else{   // 否則繼續檢查
            // 檢查左邊，錯誤則放入Q
            ptr = node[parentID].left;
            if(ptr != NULL){    // null表示該點為複製來的 不往下檢查
                temp = (*ptr);
                node[temp.ID].level = node[parentID].level + 1;
                node[temp.ID].nodeID = node[parentID].nodeID * 2;
                printf("1 %d %d\n", node[temp.ID].level, node[temp.ID].nodeID);
                fflush(NULL);
                scanf("%lu", &hashvalue);
                if(node[temp.ID].value != hashvalue){
                    queue[++tail] = temp.ID;  // push
                }
            }

            // 檢查右邊，錯誤則放入Q
            ptr = node[parentID].right;
                if(ptr != NULL){
                temp = (*ptr);
                node[temp.ID].level = node[parentID].level + 1;
                node[temp.ID].nodeID = (node[parentID].nodeID * 2) + 1;
                printf("1 %d %d\n", node[temp.ID].level, node[temp.ID].nodeID);
                fflush(NULL);
                scanf("%lu", &hashvalue);
                if(node[temp.ID].value != hashvalue){
                    queue[++tail] = temp.ID;  // push
                }
            }
        }
    }
    printf("2 %d", incorrect_strings);
    printf("%s",answer);
    fflush(NULL);
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
