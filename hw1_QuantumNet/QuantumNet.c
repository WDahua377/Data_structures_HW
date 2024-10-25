#include <stdio.h>
#include <string.h>

int nodes, reqs, links;

int GetPath(int ID, int source, int destination, int* front, int* channels_ptr, int* nodeMem_ptr, char* accreq){
    char c[10];
    int predecessor = destination, path[nodes], distance = 0;

    while( *(front+predecessor) != -1 ){
        path[distance++] = predecessor;     // get path from front[], it is reversed
        predecessor = *(front+predecessor);
    }
    path[distance] = source;

    // check if the resource is enough, if not, return 0
    if(distance != 0){
        if( *(nodeMem_ptr+path[0]) >= 1 && *(nodeMem_ptr+path[distance]) >= 1 && 
        *(channels_ptr + path[1]*nodes + path[0]) >= 1 ){
            for(int i = 1; i <= distance-1; i++){
                if( *(nodeMem_ptr+path[i]) < 2 )
                    return 0;
                if( *(channels_ptr + path[i]*nodes + path[i-1]) < 1 )
                    return 0;
            }

            // resources are enough for this path
            sprintf(c, "%d ", ID);  // strcat ID
            strcat(accreq, c);
            sprintf(c, "%d ", path[distance]);  // strcat src
            strcat(accreq, c);

            //channel[ path[distance] ][ path[distance-1] ]    (src and rep1)
            *(channels_ptr + path[distance]*nodes + path[distance-1]) -= 1;
            *(channels_ptr + path[distance-1]*nodes + path[distance]) -= 1;

            for(int i = distance-1; i > 0; i--){
                *(nodeMem_ptr+path[i]) -= 2;
                *(channels_ptr + path[i]*nodes + path[i-1]) -= 1;
                *(channels_ptr + path[i-1]*nodes + path[i]) -= 1;
                sprintf(c, "%d ", path[i]);     // strcat path between src and dst
                strcat(accreq, c);
            }

            *(nodeMem_ptr+path[0]) -= 1;
            *(nodeMem_ptr+path[distance]) -= 1;
            sprintf(c, "%d\n", path[0]);    // strcat dst
            strcat(accreq, c);
            return 1;
        }
    }

    // front[destination] == -1 if and only if when there isn't any path for src to dst 
    // unless dst is src, then front[destination] equal to front[source] is -1
    return 0;
}

void BFS(int source, int destination, int* channels_ptr, int* front){
    int queue[nodes], visited[nodes], queue_end = 0, queue_start = 0;

    // initialize queue, visited and front for every request
    for(int i = 0; i < nodes; i++){
        queue[i] = 0;
        visited[i] = 0;
        front[i] = -1;
    }
    queue[queue_end++] = source;

    while(queue_end > queue_start){     // while queue is not empty
        int start = queue[queue_start++];
        visited[start] = 1;

        // check if start and (every)node are connected, if so, put it in queue
        for(int node = 0; node < nodes; node++){
            if( *(channels_ptr+start*nodes+node) > 0 && visited[node] == 0 ){
                queue[queue_end++] = node;
                visited[node] = 1;
                *(front+node) = start;    // predecessor of node is start
            }
        }
    }
}

int main(void){
    scanf("%d%d%d", &nodes, &links, &reqs);
    int quantumMemories[nodes], channels[nodes][nodes], front[nodes], ori_channels[nodes][nodes];
    int reqID = 0, reqSrc, reqDst, ans = 0;
    char accreq[100000];

    // initialize variable
    for(int i = 0; i < nodes; i++){
        for(int j = 0; j < nodes; j++){
            channels[i][j] = 0;
            ori_channels[i][j] = 0;
        } }
    memset(accreq, '\0', sizeof(accreq));

    // input G(V, E)
    for(int i = 0; i < nodes; i++){
        int nodeID;

        scanf("%d", &nodeID);
        scanf("%d", &quantumMemories[nodeID]);
    }
    for(int i = 0; i < links; i++){
        int linkID, linkEnd1, linkEnd2, value;

        scanf("%d%d%d",&linkID, &linkEnd1, &linkEnd2);
        scanf("%d", &value);
        channels[linkEnd1][linkEnd2]  = channels[linkEnd2][linkEnd1]= value;
        ori_channels[linkEnd1][linkEnd2] = ori_channels[linkEnd2][linkEnd1] = value;
    }

    // input request
    for(int i = 0; i < reqs; i++){
        scanf("%d%d%d", &reqID, &reqSrc, &reqDst);
        if(reqSrc == reqDst){
            ans += 1;
            char c[5];
            sprintf(c, "%d\n", reqDst);
            strcat(accreq, c);
        }
        else{
            // Find a shortest path from source to destination
            BFS(reqSrc, reqDst, ori_channels[0], front);
            // Check if the resource is enough and get the available path
            ans += GetPath(reqID, reqSrc, reqDst, front, channels[0], quantumMemories, accreq);
        }
    }

    // output
    printf("%d\n%s", ans, accreq);
    return 0;
}