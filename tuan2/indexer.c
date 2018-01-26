#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int  isdauphancach(char c,char* dauphancach){
  int i=0;
  for(i=0;i<18;i++){
    if(c==dauphancach[i])
      return 1;
   
  }
  return 0;
}
typedef struct treenode{
  struct treenode *left;
  struct treenode *right;
  char * key;
  int tongsoluong;
  int mangvitri[2][1000];
}treenode;

void duyetcay(treenode *root){
  if(root!=NULL)
    {
       duyetcay(root->left);
      
       printf("%s %d ",root->key,(root->tongsoluong));
       for(int i=0;i<root->tongsoluong;i++)
	{
	  printf("(%d,%d)", (root->mangvitri)[0][i],(root->mangvitri)[1][i]);
	  }
      printf("\n");
      duyetcay(root->right);
    }
}
void inserttotree(treenode **root,char *key,int donghientai,int columnhientai){
  if((*root)==NULL){
    int a=0;
    
    *root=(treenode *)malloc(sizeof(treenode));
    (*root)->key=(char *)malloc(sizeof(char)*(strlen(key)+3));
    strcpy((*root)->key,key);
    //printf("%d %s\n",(int )strlen((*root)->key),(*root)->key);
    
    ((*root)->mangvitri)[0][0]=donghientai;
    ((*root)->mangvitri)[1][0]=columnhientai;
    (*root)->tongsoluong=1;
    (*root)->left=NULL; 
    (*root)->right=NULL;
   
  }
  else{
    int c=strcmp((char *)(*root)->key,key);
    if(c==0){
     
	  ((*root)->mangvitri)[0][(*root)->tongsoluong]=donghientai;
	  ((*root)->mangvitri)[1][(*root)->tongsoluong]=columnhientai;
	  (*root)->tongsoluong++;
    }
    else
      if(c>0){
	inserttotree(&((*root)->left),key,donghientai,columnhientai);
      }
      else{
	inserttotree(&((*root)->right),key,donghientai,columnhientai);
      }
  
  }
}

int main(){
  // dinh nghia cac input cho chuong trinh
  FILE *fstopw = fopen("stopw.txt", "r");
  FILE *fvanban = fopen("vanban.txt", "r");
  char dauphancach[] = {' ','\n','\t','.',',',';',':','\'','1','2','3','4','5','6','7','8','9','0',EOF};


  // xu li du lieu tho

  char stopw[50][30];
  int stopwlen=0;
  while(1){
    if(feof(fstopw))break;
    fscanf(fstopw,"%s%*[\n]",stopw[stopwlen]);
    stopwlen++;
   
  }
  stopwlen--;



// tao hash table

treenode * tree=NULL;

int i=0;
char c;
int ketthuccau=0;
int donghientai=1;
int columnhientai=1;
char word[100];
char f=' ';
 char* strtemp,*strtemp2;
 while(!feof(fvanban)){
   ketthuccau=0;
   //bo qua cac ky hieu, lưu lại xem co dau cham hay khong+
   //luu so dong hien tai+luu lai ky tu chu dau tien
   if(f=='.'||f=='!'||f=='?') ketthuccau=1;
   if(f=='\n') donghientai++;
     if(feof(fvanban))
     printf("ket thuc file lan 0\n");
   do{c=fgetc(fvanban);
     if(c=='.'||c=='!'||c=='?')
       ketthuccau=1;
     if(c=='\n') {
       columnhientai=1;donghientai++;
     }
      if(feof(fvanban)) break;
      
   }
   while(isdauphancach(c,dauphancach));

     if(feof(fvanban)) goto a;
   if(feof(fvanban))
     printf("ket thuc file lan 1\n");

 
   //doc het tu + luu ky tu phan cach dau tien lai
   //printf("%c %d %d\n",c,ketthuccau,donghientai);
   if(!feof(fvanban))
      word[0]=c;
   i=0;
   do{
     f=fgetc(fvanban);

     if(!isdauphancach(f,dauphancach))
       {//printf("%d\n", f);
	 word[++i]=f;}
     else break;
     if(f==EOF)
       break;
   }
   while(1);
   if(feof(fvanban))
     //   printf("%c\n",word[i+2]);
   word[++i]='\0';

   if(feof(fvanban))
     printf("ket thuc file lan 1\n");

   if(feof(fvanban)) break;
   if( ketthuccau==1||(word[0]>='a' && word[0]<='z')||(word[0]>='A' && word[0]<='Z'))
     {// neu khong phai thi them vao cay nhi phan

   
       for(int i=0;i<sizeof(word);i++)
	 {
	   word[i]=tolower(word[i]);
	 }
	 
       int checkstopword=0;



       
       // printf("truoc khi insert  %s\n", word);
       
       for(int j=0;j<stopwlen;j++)
	 {
	   // printf("%-10s %s\n",word,stopw[j] );
	     if(strcmp(stopw[j],word)==0 && !feof(fvanban))
	     {
	       checkstopword=1;
	       printf("trung stop word\n");
	       }
	   
	 
	 }
       //  printf(" test %s\n",word);

       //printf("truoc khi insert  %s\n", word);
      
       
       if(checkstopword==0)
	 {
	   inserttotree(&tree,word,donghientai,columnhientai);
	   //printf("insert %s %d %d\n",word,donghientai,columnhientai); 
	 }
       checkstopword=0;
       

     }
  
    
 columnhientai++;
 }
a:;
 duyetcay(tree);

  return 0;
}
