#include <stdio.h>
#include <string.h>

int main(void){
    int resourceY, resourceX, users;
    int id, shapeX = 0, ans = 0, posX = 0;
    char str[30] = {0}, c[10] = {0}, finalAns[100000] = {0};

    /* initialize variable
     memset(str, '\0', sizeof(str));
     memset(c, '\0', sizeof(c));*/

    scanf("%d%d%d", &resourceY, &resourceX, &users);

    // request
    for(int i = 0; i < users; i++){
        scanf("%d", &id);
        getchar();  // 去掉gets抓到的空格
        fgets(str, sizeof(str), stdin); 

        /*if(str[3] == '1')   // 16x1
            shapeX = 1;
        if(str[3] != 'x' && str[3] != '1')  // 4x4, 2x8, 8x2
            shapeX = str[2] - '0';
        if(str[3] == '6')   // 1x16
            shapeX = 16;*/

        if(str[2] == 'x')   // 16x1
            shapeX = 1;
        else if(str[2] == '1')  // 1x16
            shapeX = 16;
        else
            shapeX = str[2] - '0';     // 4x4, 2x8, 8x2
        
        // can be put in
        if( resourceX - shapeX >= 0 && resourceY >= (16/shapeX) ){  // 16/shapeX is shapeY
            resourceX -= shapeX;    // shapeY doesn't need to be reduced
            ans += 1;

            sprintf(c, "%d ", id);
            strcat(finalAns, c);

            if(str[0] == '1'){  // 1x16, 16x1
                strncpy(c, str, 4);
                c[4] = '\0';    // strncpy需手動加上終止符
                strcat(finalAns, c);
            }
            else{   // 4x4, 2x8, 8x2
                strncpy(c, str, 3);
                c[3] = '\0';
                strcat(finalAns, c);
            }

            // show shapes' positions
            sprintf(c, " 0 %d\n", posX);
            strcat(finalAns, c);
            posX += shapeX;
        }
    }

    printf("%d\n%s",ans, finalAns);
}