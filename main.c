#include <stdio.h>
#include <stdlib.h>

enum blocks {
    ENERGY = 1,
    MITOSIS,
    FORBIDDEN,
    NORMAL
};

int rand_beetwin(int start,int end);
void print_map(int n);

int main()
{
    srand(time(NULL));
    //Map_Editor();
    //str_main();
    print_map(8);
    return 0;
}

#define BlockSize 6
#define ToleBlock 8

void print_map(int n){
    int m;
    if(n%2==0)
        m=n+1;
    else
        m=n;
    printf("Game Map\n\n");
    int i,j,k,u1,u2,u3,u4,u5,u6,B;
    if(BlockSize%2==0)
        B=BlockSize/2;
    else
        B=(BlockSize+1)/2;
    for(i=0,u1=0;i<=n*BlockSize+B;i++,u1++){///shomare satr
        for(j=0,u2=0,u3=0,u4=0,u5=0,u6=0;j<m;j++){///por kardane satr
            if(i<=n*BlockSize){
                if(u1%BlockSize==0){
                    if(u1==0&&u2%2==0){
                        printf(" ");
                        for(k=0;k<ToleBlock;k++)
                            printf("_");
                        printf(" ");
                    }
                    else if(u2%2==0){//
                        printf("|");
                        for(k=0;k<ToleBlock;k++)
                            printf("_");
                        printf("|");
                    }
                    else{
                        for(k=0;k<ToleBlock;k++)
                            printf(" ");
                    }
                    u2++;
                }
                else if(u1%BlockSize==B){
                    if(u4%2==0){//
                        printf("|");
                        for(k=0;k<ToleBlock;k++)
                            printf(" ");
                        printf("|");
                    }
                    else{
                        for(k=0;k<ToleBlock;k++)
                            printf("_");
                    }
                    u4++;
                }
                else{
                    if(u3%2==0){//
                        printf("|");
                        for(k=0;k<ToleBlock;k++)
                            printf(" ");
                        printf("|");
                    }
                    else{
                        for(k=0;k<ToleBlock;k++)
                            printf(" ");
                    }
                    u3++;
                }
            }
            else if(i==n*BlockSize+B){
                if(u6==0)
                    printf(" ");
                if(u6%2==1){
                    printf("|");
                    for(k=0;k<ToleBlock;k++)
                        printf("_");
                    printf("|");
                }
                else{
                    for(k=0;k<ToleBlock;k++)
                        printf(" ");
                }
                u6++;
            }
            else{
                if(u5==0)
                    printf(" ");
                if(u5%2==1){
                    printf("|");
                    for(k=0;k<ToleBlock;k++)
                        printf(" ");
                    printf("|");
                }
                else{
                    for(k=0;k<ToleBlock;k++)
                        printf(" ");
                }
                u5++;
            }
        }
        printf("\n");
    }
}

int rand_beetwin(int start,int end){
    return ((rand()*1.0)/(RAND_MAX+1))*(end-start+1)+start;
}
