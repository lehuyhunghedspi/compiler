#include<stdio.h>

char * doctuvakytuketthuc(FILE *filevanban,char * dauphancach){
  char *a=(char *)malloc(sizeof(char) * 30);
  int i=0;
  while(1){
    c=fgetc(filevanban);
    if(foef(filevanban)){
      a[i]='\n';
      i++;
      break;
    }
    else{
      if(checkdauphancach(c,dauphancach)){
	 a[i]=c;
	 i++;
	 break;
      };
      else{
	a[i]=c;
	i++;
      }
    }
    
  }
  a[i++]='\0';
  return a;
}
int main(){
  // dinh nghia cac input cho chuong trinh
  FILE *fstopw = fopen("stopw.txt", "r");
  FILE *fvanban = fopen("vanban.txt", "r");
  char dauphancach[7] = {' ','\n','\t','.',',',';',':'};

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
  
  char * chudautien=doctuvakytuketthuc(fvanban,dauphancach);
 printf("%s\n", chudautien);  
  //printf("%s\n", docchudautien);
  //laplaiquatrinhchohetfile
  
    //laplaichohetfile
    while(1){
      //layra mot tu va ky tu ket thuc truoc no

      // kiemtra xem tu co phai la ten rieng hay tu bi cam khong

      // format thanhchuthuong

      //them tu vao danh sach hoac thay doi chi so

      // sap xep neu can

      
      //kiemtraketthuc
      break;
    }



  // dua ra ket qua
  
  //

  return 0;
}
