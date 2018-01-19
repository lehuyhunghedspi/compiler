#include<stdio.h>
#include<stdlib.h>
int  isdauphancach(char c,char* dauphancach){
  int i=0;
  for(i=0;i<8;i++){
    if(c==dauphancach[i])
      return 1;
   
  }
  return 0;
}
char * doctuvakytuketthuc(FILE *filevanban,char *dauphancach){
  char *a=(char *)malloc(sizeof(char) * 30);
  int i=0;
  char c;
  int dacochucaihoacso=0;
  int check=0;
  while(!feof(filevanban)){
    
    c=fgetc(filevanban);
    check=isdauphancach(c,dauphancach);
    if(check==0){
     
      dacochucaihoacso=1;
      //printf("%c\n",c);
    }
     if(dacochucaihoacso){
       if(feof(filevanban)){
	 a[i]='\n';
	 i++;
	 break;
       }
       else{
	 if(check){
	
	   a[i]=c;
	   i++;
	   break;
	 }
	 else{
	   a[i]=c;
	   i++;
	 }
       }
     }
     
      
     
   
    
  }
  if(dacochucaihoacso){

    
  a[i++]='\0';
  return a;
  }
  else return NULL;
}

int main(){
  // dinh nghia cac input cho chuong trinh
  FILE *fstopw = fopen("stopw.txt", "r");
  FILE *fvanban = fopen("testvanban.txt", "r");
  char dauphancach[8] = {' ','\n','\t','.',',',';',':',EOF};
  // xu li du lieu tho

  char stopw[50][30];
  int stopwlen=0;
  while(1){
    if(feof(fstopw))break;
    fscanf(fstopw,"%s%*[\n]",stopw[stopwlen]);
    stopwlen++;
   
  }
  stopwlen--;
  /* for(int i=0;i<stopwlen;i++) */
  /*   { */
  /*     printf("%d %s\n",i,stopw[i] ); */
  /*   } */
    
    


  
  //su li tu dau tien
  
  char * chudautien;
  //laplaiquatrinhchohetfile
  
    //laplaichohetfile
  int i=0;
  while(!feof(fvanban)){
      chudautien=doctuvakytuketthuc(fvanban,dauphancach);
      if(chudautien==NULL){
	//	printf("tra ve null\n");
      }
      else{
	printf("%d %s--",i, chudautien);

      }
      	i++;
      if(i==6) break;
      //layra mot tu va ky tu ket thuc truoc no

      // kiemtra xem tu co phai la ten rieng hay tu bi cam khong

      // format thanhchuthuong

      //them tu vao danh sach hoac thay doi chi so

      // sap xep neu can

      
      //kiemtraketthuc
    }



  // dua ra ket qua
  
  //

  return 0;
}
