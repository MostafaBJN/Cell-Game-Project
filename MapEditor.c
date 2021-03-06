#include <stdio.h>
#include <string.h>

void new_map(){
    unsigned int n=0;
    char c,name[256];
    printf("Enter Name of File (.bin): ");
    scanf("%c",&c);
    gets(name);
    if(name[0]=='\0'){
        strcpy(name,"map.bin");
        puts(name);
    }
    while(!(n>0&&n<100)){
        if(n>=100)
            printf("ZIADE!!!");
        printf("Tole Ab-Ade Zamin ra Vared Konid : ");
        scanf("%u",&n);
    }
    FILE *f=fopen(name,"w+b");
    fwrite(&n, sizeof(unsigned int), 1, f);
    char mp[n*n];
    for(int i=0;i<n*n;i++){
        char c=0;
        printf("Blocke Satre %d Sotoone %d :\nENERGY = 1\nMITOSIS = 2\nFORBIDDEN = 3\nNORMAL = 4\n",(i/n)+1,(i%n)+1);
        while(!(c==49||c==50||c==51||c==52)){
            scanf(" %c",&c);
        }
        mp[i]=c;
    }
    fwrite(mp, sizeof(char), n*n,f);
    fclose(f);
    return;
}

void random_map(){
    int n=-1;
    char c,name[256];
    printf("Enter Name of File (.bin): ");
    scanf("%c",&c);
    gets(name);
    if(name[0]=='\0'){
        strcpy(name,"map.bin");
        puts(name);
    }
    while(!(n>-1&&n<100)){
        if(n>=100)
            printf("ZIADE!!!");
        printf("Tole Ab-Ade Zamin ra Vared Konid\n(Agar Mikhaid Random Bashe 0 ra Vared Konid):\n");
        scanf("%d",&n);
    }
    if(n==0)
        n=rand_beetwin(6,99);
    FILE *f=fopen(name,"w+b");
    fwrite(&n, sizeof(unsigned int), 1, f);
    char mp[n*n];
    for(int i=0;i<n*n;i++)
        mp[i]=rand_beetwin(1,4)+48;
    fwrite(mp, sizeof(char), n*n,f);
    fclose(f);
    return;
}

void editor(){
    unsigned int n;
    char name[256],c;
    printf("Enter Name of File (.bin): ");
    scanf("%c",&c);
    gets(name);
    if(name[0]=='\0'){
        strcpy(name,"map.bin");
        puts(name);
    }
    FILE *f=fopen(name,"rb");///{why?
    if(f==NULL)
        return;
    fread(&n, sizeof(unsigned int), 1, f);
    fclose(f);
    f=fopen(name,"w+b");
    fwrite(&n, sizeof(unsigned int), 1, f);///}
    char mp[n*n];
    for(int i=0;i<n*n;i++){
        char c=0;
        while(!(c==49||c==50||c==51||c==52)){
            printf("Blocke Satre %d Sotoone %d :\nENERGY = 1\nMITOSIS = 2\nFORBIDDEN = 3\nNORMAL = 4\n",(i/n)+1,(i%n)+1);
            scanf(" %c",&c);
        }
        mp[i]=c;
    }
    fwrite(&mp, sizeof(char), n*n,f);
    fclose(f);
    return;
}

void view(){
    unsigned int n;
    char name[256],c;
    printf("Enter Name of File (.bin): ");
    scanf("%c",&c);
    gets(name);
    if(name[0]=='\0'){
        strcpy(name,"map.bin");
        puts(name);
    }
    FILE *map_file = fopen(name,"r+b");
    if(map_file==NULL)
        return;
    fread(&n, sizeof(unsigned int), 1, map_file);
    char mp[n*n];
    system("cls");
    printf("n = %u \n\n",n);
    fread(mp, sizeof(char), n*n,map_file);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%c ",mp[i*n+j]);
        }
        printf("\n");
    }
    fclose(map_file);
    strcat(name,".txt");
    FILE *f=fopen(name,"wb");
    fprintf(map_file,"n = %u \n\n",n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(mp[i*n+j]=='1')
                fprintf(map_file,"X ");
            else if(mp[i*n+j]=='2')
                fprintf(map_file,"S ");
            else if(mp[i*n+j]=='3')
                fprintf(map_file,"E ");
            else if(mp[i*n+j]=='4')
                fprintf(map_file,"' ");
        }
        fprintf(map_file,"\n");
    }
    printf("\n\n");
    fprintf(map_file,"\n\n");
    printf("Guide :\nENERGY = 1\nMITOSIS = 2\nFORBIDDEN = 3\nNORMAL = 4\n");
    fprintf(f,"Guide :\nENERGY = E\nMITOSIS = S\nFORBIDDEN = X\nNORMAL = '\n");
    fclose(f);
    Sleep(4000);
}

void Map_Editor(){
    int a=0;
    system("cls");
    while(!(a==1||a==2||a==3||a==4)){
        printf("***MAP EDITOR***\n\n1)Make a New Map\n2)Make a Random Map\n3)Edit an Exist Map\n4)View Map\n");
        scanf("%d",&a);
    }
    switch(a){
        case 1:
            new_map();
            break;
        case 2:
            random_map();
            break;
        case 3:
            editor();
            break;
        case 4:
            view();
            break;
    }

}

/*{check if done
        FILE *map_file = fopen("map.bin","rb+");
        fread(&n, sizeof(unsigned int), 1, map_file);
        char mp[n*n];
        printf("n = %d \n",n);
        fread(mp, sizeof(char), n*n,map_file);
        for(int i=0;i<n*n;i++)
            printf("c[%d] = %c \n",i,mp[i]);
    }*/
