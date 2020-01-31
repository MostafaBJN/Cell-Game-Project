#include "struct.h"
#include "MapEditor.h"
#include <windows.h>

#define BlockSize 6
#define ToleBlock 7

enum blocks {
    ENERGY = 1,
    MITOSIS,
    FORBIDDEN,
    NORMAL
};

struct MAP{
    char type;
    char player[3];
    int energy;
    struct position pos;
};

struct Head *pth;
struct Head *pth_player_1;
struct Head *pth_player_2;

int rand_beetwin(int start,int end);
void print_map(int n,struct MAP block[n][n]);
void new_load_map(int n,struct MAP block[n][n],char tmp[n*n],FILE *f);
void main_menu();
void in_game_menu();
void save_game();////
void load_game();////
int mover();////
/// move_cell();
/// remove_cell();
int gain_energy();////
int split();////
int check_forbidden_block();//////////
/// check_be_inside();
struct position rand_place(int n,struct MAP block[n][n],char cellname[],char player);
char *rand_name(int size);
void one_player();
void two_player();////
void game(int n);////
void extra();

int main(){
    time_t t=time(NULL);
    srand(t);
    main_menu();
    return 0;
}

void two_player(){
    Make_A_List();
    pth_player_1=pth;
    Make_A_List();
    pth_player_2=pth;
}

void game(int n){

}

void one_player(){
    char name[256],c;///open new map;
    unsigned int n;
    printf("Enter Name of File (.bin): ");
    scanf("%c",&c);
    gets(name);
    if(name[0]=='\0'){
        strcpy(name,"map.bin");
        puts(name);
    }
    FILE *f = fopen(name,"r+b");
    if(f==NULL){
        system("cls");
        printf("File Not Found !");
        Sleep(2000);
        main_menu();
    }
    fread(&n, sizeof(unsigned int), 1, f);
    char tmp[n*n];
    fread(tmp, sizeof(char), n*n, f);
    struct MAP block[n][n];
    new_load_map(n,block,tmp,f);


    int num,i,j,rx,ry;///making cells
    struct position pos;
    Make_A_List();
    struct Head *pth_player_1=pth;
    pth = pth_player_1;
    printf("Tedade Cell Haye Avvalye : ");
    scanf("%d",&num);
    for(i=0;i<num;i++){
        char cellname[256];
        printf("Enter Name of Cell (Enter for Random): ");
        if(i==0)
            scanf("%c",&c);
        gets(cellname);
        if(cellname[0]=='\0'){
            int r = rand_beetwin(1,12);
            char *cn = rand_name(r);
            strcpy(cellname,cn);
            puts(cellname);
        }
        addEnd(Make_A_Cell(rand_place(n,block,cellname,'0'),cellname));
    }

    print_map(n,block);
}

struct position rand_place(int n,struct MAP block[n][n],char cellname[],char player){
    int rx,ry;
    struct position place;
    do{
        rx = rand_beetwin(1,n);
        ry = rand_beetwin(1,n);
    }
    while(check_forbidden_block(rx,ry,n,block));
    get_a_place(rx,ry,&place,n,block,cellname,player);
    return place;
}

void get_a_place(int x,int y,struct position *place,int n,struct MAP block[n][n],char cellname[],char player){
    block[y-1][x-1].player[0]=cellname[0];
    if(cellname[1]=='\0'){
        block[y-1][x-1].player[1]='.';
        if(player=='0')
            block[y-1][x-1].player[2]='.';
        else if(player=='1'||player=='2')
            block[y-1][x-1].player[2]=player;
    }
    else if(cellname[2]=='\0'){
        block[y-1][x-1].player[1]=cellname[1];
        if(player=='0')
            block[y-1][x-1].player[2]='.';
        else if(player=='1'||player=='2')
            block[y-1][x-1].player[2]=player;
    }
    else{
        block[y-1][x-1].player[1]=cellname[1];
        if(player=='0')
            block[y-1][x-1].player[2]=cellname[2];
        else if(player=='1'||player=='2')
            block[y-1][x-1].player[2]=player;
    }
    place->x = x;
    place->y = y;
}

int check_forbidden_block(int x,int y,int n,struct MAP block[n][n]){
    if(block[y-1][x-1].type=='3'||block[y-1][x-1].player[0]!='.'){
        return 1;
    }

    return 0;
}

char *rand_name(int size){
    int i;
    char *name = malloc((size+1)*sizeof(char));
    char allchars[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM0123456789";
    for(i=0;i<size;i++){
        int n = rand() % (sizeof(allchars) / sizeof(char) -1);
        name[i]=allchars[n];
    }
    name[size]='\0';
    return name;
}

void main_menu(){
    int a=0;
    system("cls");
    while(!(a==1||a==2||a==3||a==4||a==5||a==6||a==7)){
        printf("***MAIN MENU***\n\n1)Load Game\n2)New Single Player Game\n3)New Multi Player Game\n4)Map Editor\n5)Setting\n6)Extra\n7)Exit\n");
        scanf("%d",&a);
    }
    switch(a){
        case 1:
            //load_game();
            break;
        case 2:
            one_player();
            break;
        case 3:
            two_player();
            break;
        case 4:
            Map_Editor();
            main_menu();
            break;
        case 5:
            main_menu();
            break;
        case 6:
            extra();
            main_menu();
            break;
        case 7:
            printf("***GoodBye***\n***See You Next Time***");
            Sleep(1000);
            exit(0);
            break;
    }
}

void print_map(int n,struct MAP block[n][n]){
    printf("\n\n***%d***\n\n",n);
    printf("Game Map\n");
    int i,j,k,u1,u2,u3,u4,u5,u6,u7,B;
    if(BlockSize%2==0)
        B=BlockSize/2;
    else
        B=(BlockSize+1)/2;
    for(i=0,u1=0;i<=n*BlockSize+B;i++,u1++){///shomare satr
        for(j=0,u2=0,u3=0,u4=0,u5=0,u6=0,u7=0;j<n;j++){///por kardane satr
            if(i<=n*BlockSize){
                if(n%2==0&&j==n-1&&u7==1){///for correct print of last wall for zoje n
                    if(i>3)
                        printf("|");
                }
                else{
                    if(u1%BlockSize==0){
                        if(u1==0&&u2%2==0){///first line //top
                            printf(" ");
                            for(k=0;k<ToleBlock;k++)
                                printf("_");
                            printf(" ");
                        }
                        else if(u2%2==0){///bottoms
                            printf("|");
                            for(k=0;k<ToleBlock;k++)
                                printf("_");
                            printf("|");
                        }
                        else{///midle of blocks , zoje ha (payintar ha)[cells]
                            for(k=0;k<ToleBlock;k++){
                                if(i!=0&&block[(i-1)/BlockSize][j].player[0]!='.'){
                                    if(k==2)
                                        printf("%c",block[(i-1)/BlockSize][j].player[0]);
                                    else if(k==3)
                                        printf("%c",block[(i-1)/BlockSize][j].player[1]);
                                    else if(k==4)
                                        printf("%c",block[(i-1)/BlockSize][j].player[2]);
                                    else
                                        printf(" ");
                                }
                                else
                                    printf(" ");
                            }
                        }
                        u2++;
                    }
                    else if(u1%BlockSize==B){
                        if(u4%2==0){///midle of blocks , fard ha (balatar ha)[cells]
                            printf("|");
                            for(k=0;k<ToleBlock;k++){
                                if(i!=0&&block[(i-1)/BlockSize][j].player[0]!='.'){
                                    if(k==2)
                                        printf("%c",block[(i-1)/BlockSize][j].player[0]);
                                    else if(k==3)
                                        printf("%c",block[(i-1)/BlockSize][j].player[1]);
                                    else if(k==4)
                                        printf("%c",block[(i-1)/BlockSize][j].player[2]);
                                    else
                                        printf(" ");
                                }
                                else
                                    printf(" ");
                            }
                            printf("|");
                        }
                        else{///top of zoje blocks
                            for(k=0;k<ToleBlock;k++)
                                printf("_");
                        }
                        u4++;
                    }
                    else{
                        if(u3%2==0){///other empty inside blocks , fard ha[type]
                            printf("|");
                            for(k=0;k<ToleBlock;k++)
                                printf(" ");//////////////////////////
                            printf("|");
                        }
                        else{///other empty inside blocks , zoje ha (WARNING :first is out side va shamele akharish nemishe)
                            if(u1==1||u1==2)///outside
                                for(k=0;k<ToleBlock;k++)
                                    printf(" ");
                            else///all insides except 2 last line
                                for(k=0;k<ToleBlock;k++)
                                    printf(" ");
                        }
                        u3++;
                    }
                    if(n%2==0&&j==n-1){///correct last wall of zoje n
                        j--;
                        u7++;
                    }
                }
            }
            else if(i==n*BlockSize+B){
                if(u6==0)
                    printf(" ");
                if(u6%2==1){///last bottom
                    printf("|");
                    for(k=0;k<ToleBlock;k++)
                        printf("_");
                    printf("|");
                }
                else{///out of map
                    for(k=0;k<ToleBlock;k++)
                        printf(" ");
                }
                u6++;
            }
            else{
                if(u5==0)
                    printf(" ");
                if(u5%2==1){///bottom inside last
                    printf("|");
                    for(k=0;k<ToleBlock;k++)
                        printf(" ");
                    printf("|");
                }
                else{///out of map
                    for(k=0;k<ToleBlock;k++)
                        printf(" ");
                }
                u5++;
            }
        }
        printf("\n");
    }
}

void new_load_map(int n,struct MAP block[n][n],char tmp[n*n],FILE *f){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            block[i][j].type=tmp[n*i+j];
            block[i][j].pos.x=j+1;
            block[i][j].pos.y=i+1;
            block[i][j].player[0]='.';
            block[i][j].player[1]='.';
            block[i][j].player[2]='.';
            if(block[i][j].type=='1')
                block[i][j].energy=100;
            else
                block[i][j].energy=0;
        }
    }
}

int rand_beetwin(int start,int end){
    return ((rand()*1.0)/(RAND_MAX+1))*(end-start+1)+start;
}

void extra(){
    system("cls");
    printf("Map of Next Version\n\n");
    printf("   _____         _____\n  /     \\       /     \\ \n /   o   \\_____/   o   \\ \n \\       /     \\       /\n  \\_____/   o   \\_____/\n  /     \\       /     \\ \n /   o   \\_____/   o   \\ \n \\       /     \\       / \n  \\_____/   o   \\_____/ \n  /     \\       /     \\ \n /   o   \\_____/   o   \\ \n \\       /     \\       / \n  \\_____/   o   \\_____/ \n        \\       / \n         \\_____/ \n");
    Sleep(4000);
    return;
}

/**void in_game_menu(){
    int a=0;
    system("cls");
    while(!(a==1||a==2||a==3||a==4||a==5)){
        printf("***MAIN MENU***\n\n1)Move\n2)Split\n3)Gain Energy\n4)Save\n5)Exit\n");
        scanf("%d",&a);
    }
    switch(a){
        case 1:
            if(mover())
                in_game_menu();
            break;
        case 2:
            if(split())
                in_game_menu();
            break;
        case 3:
            if(gain_energy())
                in_game_menu();
            break;
        case 4:
            save_game();
            in_game_menu();
            break;
        case 5:
            main_menu();
            break;
    }
}*/


///Next Version Map
/**
   _____         _____
  /     \       /     \
 /       \_____/       \
 \       /     \       /
  \_____/       \_____/
  /     \       /     \
 /       \_____/       \
 \       /     \       /
  \_____/       \_____/
  /     \       /     \
 /       \_____/       \
 \       /     \       /
  \_____/       \_____/
        \       /
         \_____/

*/

