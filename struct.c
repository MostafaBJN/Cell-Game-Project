#include "struct.h"

extern struct Head *pth;

void Make_A_List(){
    pth=malloc(sizeof(struct Head));
    pth->head=NULL;
    pth->length=0;
}

struct cells *Make_A_Cell(struct position pos,char name[256]){
    struct cells *my_cell=malloc(sizeof(struct cells));
    my_cell->energy = 0;
    my_cell->energy_limit = 100;
    my_cell->level = 1;
    my_cell->pos.x = pos.x;
    my_cell->pos.y = pos.y;
    strcpy(my_cell->name,name);
    return my_cell;
};

void addFront(struct cells *cell){
    struct node * new_node = malloc(sizeof(struct node));
    pth->length++;
    new_node->cell = cell;
    new_node->next = pth->head;
    pth->head = new_node;
}

void addEnd(struct cells *cell){
    struct node * new_node = malloc(sizeof(struct node));
    pth->length++;
    new_node->cell = cell;
    new_node->next = NULL;
    if(pth->head==NULL)
        pth->head = new_node;
    else{
        struct node *cur = pth->head;
        for(;cur->next!=NULL;cur = cur->next);
        cur->next = new_node;
    }
}

void deleteNode(char name[256],struct position pos){
    if((!strcmp(pth->head->cell->name,name))&&(pth->head->cell->pos.x==pos.x)&&(pth->head->cell->pos.y==pos.y)){
        struct node *tmp=pth->head;
        pth->length--;
        pth->head=pth->head->next;
        free(tmp->cell);
        free(tmp);
        return;
    }
    struct node* cur = pth->head;
    struct node* last = NULL;
    for(;cur!=NULL;last=cur,cur=cur->next){
        if((!strcmp(cur->cell->name,name))&&(cur->cell->pos.x==pos.x)&&(cur->cell->pos.y==pos.y)){
            last->next = cur->next;
            free(cur->cell);
            free(cur);
            return;
        }
    }
}

void printNode(){
    struct node *cur = pth->head;
    printf("Nodes :\n\n");
    printf("lenght = %d\n",pth->length);
    for(int i=0;(cur!=NULL)||(i<pth->length);cur=cur->next,i++){
        printf("Energy : %d\n",cur->cell->energy);
        printf("Energy Limit : %d\n",cur->cell->energy_limit);
        printf("LVL : %d\n",cur->cell->level);
        printf("X Pos : %d\n",cur->cell->pos.x);
        printf("Y Pos : %d\n",cur->cell->pos.y);
        printf("Name : ");
        puts(cur->cell->name);
        printf("\n\n");
    }
}
/*testing structures
void str_main(){
    int i;
    Make_A_List();
    printf("How many you want ? ");
    scanf("%d",&i);
    struct position pos;
    char name[256],c;
    for(;i>0;i--){
        printf("Cell number %d\n\n",i);
        printf("X : ");
        scanf("%d",&pos.x);
        printf("Y : ");
        scanf("%d",&pos.y);
        printf("Name : ");
        scanf("%c",&c);
        gets(name);
        printf("READY\n");
        addEnd(Make_A_Cell(pos,name));
        printf("DONE\n");
    }
    printf("\nDONE\n\n");
    printf("X : ");
    scanf("%d",&pos.x);
    printf("Y : ");
    scanf("%d",&pos.y);
    printf("Name : ");
    scanf("%c",&c);
    gets(name);
    deleteNode(name,pos);
    printNode();
}
*/
