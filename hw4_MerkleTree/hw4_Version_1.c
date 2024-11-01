#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

unsigned long hash(char* key);

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

    struct nodes{
        int ID, level, levelNum;
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
    int childID = 0, nextID = strings;
    int lastnodeID = strings - 1;   // 上一個 node

    while(lastnodeID != childID){

        // check if the tree isn't balance，i.e when the number of strings is odd (lastnode is even)
        if(lastnodeID % 2 == 0 && lastnodeID != 0){
            node[nextID].value = node[lastnodeID].value;  // copy the last node
            node[nextID].ID = nextID;
            node[nextID].right = NULL;
            node[nextID].left = NULL;
            nextID++;
            lastnodeID++;
        }

        memset(node[nextID].string, 0, StrMaxLen*sizeof(node[nextID].string[0]));   // initialize

        // construct parent node 

        /* Hashing Function :
           1. Adding two unsigned long hash values
           2. Transform the unsigned long hash value to a char string
           3. Hash the char string to acquire the hashed value */

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

    // Query
    nextID = lastnodeID;
    int queue[n], front = -1, tail = -1;
    struct nodes *ptr, temp;
    char s[StrMaxLen];

    printf("1 0 0\n");  // "1" for query action, "1 0 0" means asking for root (0,0)
    fflush(NULL);
    scanf("%lu", &hashvalue);   // origin hashvalue

    node[nextID].level = 0;
    node[nextID].levelNum = 0;
    if(node[nextID].value != hashvalue){    // 如果 root 有錯誤，push root in queue
        queue[++tail] = nextID;
    }   //if not, then queue is empty: front == tail == -1

    // while queue is not empty
    while(front != tail){
        nextID = queue[++front];    // pop

        // 如果此點表示的是原始數據（node[0]~node[strings]）
        if(nextID < strings){
            memset(s, 0, StrMaxLen*sizeof(s[0]));
            sprintf(s, "\n%s", node[nextID].string);
            strcat(answer, s);
            incorrect_strings++;
        }

        // 否，則繼續檢查
        else{
            // 檢查左邊，錯誤則放入Q
            ptr = node[nextID].left;
            if(ptr != NULL){    // null表示該點為複製的 不往下檢查 不加入queue
                temp = (*ptr);
                if(strlen(temp.string) != 0){
                    node[temp.ID].level = node[nextID].level + 1;
                    node[temp.ID].levelNum = node[nextID].levelNum * 2;
                    printf("1 %d %d\n", node[temp.ID].level, node[temp.ID].levelNum);
                    fflush(NULL);
                    scanf("%lu", &hashvalue);
                    if(node[temp.ID].value != hashvalue){
                        queue[++tail] = temp.ID;  // push
                    }
                }
            }

            // 檢查右邊，錯誤則放入Q
            ptr = node[nextID].right;
                if(ptr != NULL){
                temp = (*ptr);
                if(strlen(temp.string) != 0){
                    node[temp.ID].level = node[nextID].level + 1;
                    node[temp.ID].levelNum = (node[nextID].levelNum * 2) + 1;
                    printf("1 %d %d\n", node[temp.ID].level, node[temp.ID].levelNum);
                    fflush(NULL);
                    scanf("%lu", &hashvalue);
                    if(node[temp.ID].value != hashvalue){
                        queue[++tail] = temp.ID;  // push
                    }
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
