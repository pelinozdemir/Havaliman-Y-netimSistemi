 #include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

/*Pelin Ozdemir 210201102
* Baran Guzelgul 190201036
*Prolab 1 / 3. Proje
*/



int boyut=10;
int num=0;
int sayi=0;
int sayac=0;
struct inis_pisti_kullanim_sirasi *inis_pisti;
struct kalkis_pisti_kullanim_sirasi *kalkis_pisti;


struct inis_pisti_kullanim_sirasi{

  int *oncelik_id;
  int *ucak_id;
  int *inis_saati;
  struct inis_pisti_kullanim_sirasi *next;


}*rear=NULL,*front=NULL;


struct ucak{

  int *oncelik_id;
  int *ucak_id;
  int *inis_saati;
}ucaklar;


struct temp_ucak{
  int *oncelik_id;
  int *ucak_id;
  int *inis_saati;
}temp_ucak;

struct kalkis_pisti_kullanim_sirasi{

  int *oncelik_id;
  int *ucak_id;
  int *talep_edilen_inis_saati;
  int *inis_saati;
  int *gecikme_suresi;
  int *kalkis_saati;
  struct kalkis_pisti_kullanim_sirasi *next;


}*son=NULL,*on=NULL;

int ucak_onceligi(int ucak_index);
int ekle(int oncelik,int ucak_id,int inis);
int kuyruktaki_ucagi_ertele(int i);
int yazdir();
int kuyruktaki_ucak(int ucak_id);
int erteleme_suresi(int i);
int kuyruktaki_ucaklari_karsilastir(int ucak_index,int oncellikli_ucak);
int kuyruktaki_ucak_saati_degistir(int ucak_index,int oncellikli_ucak);
int ucak_saati_degistir(int ucak_index);
int boyutu_asan_oncelikli_ucaklar(int ucak_index);
int input_dosyasi_oku(FILE *input);
int kalkis_pistini_hazirla();
int kalkis_pisti_olustur(int oncelik,int ucak,int tinis,int inis,int gecikme,int kalkis);





int main(void)
{

    FILE *input;
    input=fopen("input.txt","r+");
    rear=(struct inis_pisti_kullanim_sirasi*)malloc(1*sizeof(struct inis_pisti_kullanim_sirasi));
    rear->inis_saati=malloc(1*sizeof(int));
    rear->oncelik_id=malloc(1*sizeof(int));
    rear->ucak_id=malloc(1*sizeof(int));
    inis_pisti=malloc(1*sizeof(struct inis_pisti_kullanim_sirasi));
    inis_pisti->inis_saati=malloc(boyut*sizeof(int));
    inis_pisti->oncelik_id=malloc(boyut*sizeof(int));
    inis_pisti->ucak_id=malloc(boyut*sizeof(int));
    kalkis_pisti=(struct kalkis_pisti_kullanim_sirasi*)malloc(1*sizeof(struct kalkis_pisti_kullanim_sirasi));
    kalkis_pisti->inis_saati=malloc(boyut*sizeof(int));
    kalkis_pisti->oncelik_id=malloc(boyut*sizeof(int));
    kalkis_pisti->ucak_id=malloc(boyut*sizeof(int));
    kalkis_pisti->gecikme_suresi=malloc(boyut*sizeof(int));
    kalkis_pisti->talep_edilen_inis_saati=malloc(boyut*sizeof(int));
    kalkis_pisti->kalkis_saati=malloc(boyut*sizeof(int));
    son=(struct kalkis_pisti_kullanim_sirasi*)malloc(1*sizeof(struct kalkis_pisti_kullanim_sirasi));
    son->inis_saati=malloc(boyut*sizeof(int));
    son->oncelik_id=malloc(boyut*sizeof(int));
    son->ucak_id=malloc(boyut*sizeof(int));
    son->gecikme_suresi=malloc(boyut*sizeof(int));
    son->talep_edilen_inis_saati=malloc(boyut*sizeof(int));
    son->kalkis_saati=malloc(boyut*sizeof(int));
    if(input==NULL){
        printf("HATA");

        return -1;
     }
     else{

        if(input_dosyasi_oku(input)==1){
             kalkis_pistini_hazirla();

        }

     }




    return 0;
}

int kalkis_pistini_hazirla(){
int oncelik,ucak,tinis,inis,gecikme,kalkis;


for (int i=0;i<sayi;i++){

        for(int z=0;z<=num;z++){
            if(inis_pisti->ucak_id[i]==ucaklar.ucak_id[z]){
                oncelik=inis_pisti->oncelik_id[i];
                ucak=inis_pisti->ucak_id[i];
                tinis=temp_ucak.inis_saati[z];
                inis=inis_pisti->inis_saati[i];
                gecikme=((inis_pisti->inis_saati[i])-(temp_ucak.inis_saati[z]));
                kalkis=((inis_pisti->inis_saati[i])+1);
                if(kalkis>24){
                    kalkis=(kalkis-24);
                }
                kalkis_pisti_olustur(oncelik,ucak,tinis,inis,gecikme,kalkis);
            }
        }

    }


yazdir();
return 0;

}



int kalkis_pisti_olustur(int oncelik,int ucak,int tinis,int inis,int gecikme,int kalkis){


  if(sayac>=boyut){
     printf("DOLU");

     return 0;
   }
   else if(son==NULL){

    son->next=NULL;
    son->oncelik_id[sayac]=oncelik;
    son->ucak_id[sayac]=ucak;
    son->talep_edilen_inis_saati[sayac]=tinis;
    son->inis_saati[sayac]=inis;
    son->gecikme_suresi[sayac]=gecikme;
    son->kalkis_saati[sayac]=kalkis;

    son->next=kalkis_pisti;

    on=son;
   }

    kalkis_pisti->oncelik_id[sayac]=oncelik;
    kalkis_pisti->ucak_id[sayac]=ucak;
    kalkis_pisti->inis_saati[sayac]=inis;
    kalkis_pisti->talep_edilen_inis_saati[sayac]=tinis;
    kalkis_pisti->gecikme_suresi[sayac]=gecikme;
    kalkis_pisti->kalkis_saati[sayac]=kalkis;
    kalkis_pisti->next=NULL;
    son=kalkis_pisti;
    sayac++;



    return 0;


}

int ekle(int oncelik,int ucak_id,int inis){
int oncelik_id=0,inis_saat=0,id=0;
   if(sayi>=boyut){
     printf("DOLU");

     return 0;
   }
  else if(rear==NULL){

    rear->next=NULL;
    rear->oncelik_id[sayi]=oncelik;
    rear->ucak_id[sayi]=ucak_id;
    rear->inis_saati[sayi]=inis;
    rear->next=inis_pisti;

    front=rear;


 }




    inis_pisti->oncelik_id[sayi]=oncelik;
    inis_pisti->ucak_id[sayi]=ucak_id;
    inis_pisti->inis_saati[sayi]=inis;
    inis_pisti->next=NULL;
    rear=inis_pisti;
    sayi++;

  for(int i=0;i<sayi;i++){
    for(int z=0;z<sayi;z++){
        if(inis_pisti->inis_saati[i]<inis_pisti->inis_saati[z] && i!=z){
            if(i>z){
                oncelik_id=inis_pisti->oncelik_id[i];
                id=inis_pisti->ucak_id[i];
                inis_saat=inis_pisti->inis_saati[i];
                inis_pisti->inis_saati[i]=inis_pisti->inis_saati[z];
                inis_pisti->oncelik_id[i]=inis_pisti->oncelik_id[z];
                inis_pisti->ucak_id[i]=inis_pisti->ucak_id[z];
                inis_pisti->inis_saati[z]=inis_saat;
                inis_pisti->oncelik_id[z]=oncelik_id;
                inis_pisti->ucak_id[z]=id;
            }
            else{
                break;
            }
        }
    }
  }


   return 0;

}

 int kuyruktaki_ucagi_ertele(int i){
     for(int x=0;x<sayi;x++){

        if(inis_pisti->ucak_id[x]==ucaklar.ucak_id[i]){
            if((inis_pisti->inis_saati[x])-(temp_ucak.inis_saati[i])==3){
            inis_pisti->inis_saati[x]=ucaklar.inis_saati[i];
            printf("Maximum ertelenmeden dolayi %d id'li ucagin inisi gerceklesti***\n",ucaklar.ucak_id[i]);
           return 1;
         }
         else{
          (ucaklar.inis_saati[i])+=1;
          inis_pisti->inis_saati[x]=ucaklar.inis_saati[i];
          printf("%d id'li ucagin inisi %d 'ye ertelendi\n",ucaklar.ucak_id[i],ucaklar.inis_saati[i]);
          ucak_onceligi(i);
          }
        }
     }




   return 0;






}



int kuyruktaki_ucak(int ucak_id){


for(int i=0;i<sayi;i++){

    if(inis_pisti->ucak_id[i]==ucaklar.ucak_id[ucak_id]){
        inis_pisti->inis_saati[i]==ucaklar.inis_saati[ucak_id];
        return 1;

    }



}


   return 0;



}



int erteleme_suresi(int i){



      if((ucaklar.inis_saati[i])-(temp_ucak.inis_saati[i])==3){
       printf("Erteleme suresinden dolayi %d oncelikli ucak baska havalimanina yonlendirildi.****\n",temp_ucak.ucak_id[i]);
        return 1;

      }
      else {
        (ucaklar.inis_saati[i])+=1;
        printf("%d id'li ucagin inisi %d 'ye ertelendi\n",ucaklar.ucak_id[i],ucaklar.inis_saati[i]);
        ucak_onceligi(i);

      }




   return 0;
}






int ucak_onceligi(int ucak_index){

int f=0;

 for(int x=0;x<num;x++){
          if((ucaklar.inis_saati[x]==ucaklar.inis_saati[ucak_index]) && (kuyruktaki_ucak(ucak_index)!=1) && (x!=ucak_index)&& (kuyruktaki_ucak(x)==1) ){
                f++;
                if(ucaklar.oncelik_id[x]<ucaklar.oncelik_id[ucak_index]){

                     erteleme_suresi((ucak_index));
                     break;


                      //ucagin inisini ertele kuyruga ekleme
                }
                else if( (ucaklar.oncelik_id[x]>ucaklar.oncelik_id[ucak_index]) && (kuyruktaki_ucak(ucak_index)!=1) && (kuyruktaki_ucak(x)==1)){


                      if(kuyruktaki_ucagi_ertele(x)==1){
                        erteleme_suresi(ucak_index);
                      }
                      else{
                        printf("%d id'li ucaga %d icin inis izni verildi.\n",ucaklar.ucak_id[ucak_index],ucaklar.inis_saati[ucak_index]);
                        ekle(ucaklar.oncelik_id[ucak_index],ucaklar.ucak_id[ucak_index],ucaklar.inis_saati[ucak_index]);
                        break;
                    }





                 // yeni ucagi kuyruga ekle diger ucagin saatini değistir

                }
                else if(ucaklar.oncelik_id[x]==ucaklar.oncelik_id[ucak_index] && (kuyruktaki_ucak(x)==1)){


                         erteleme_suresi((ucak_index));
                         break;


                        //ucagin inisini ertele kuyruga ekleme

                }

            }
        else if( (ucaklar.inis_saati[x]==ucaklar.inis_saati[ucak_index]) && (kuyruktaki_ucak(ucak_index))==1 && (x!=ucak_index)&& (kuyruktaki_ucak(x))==1 ){
                f++;
               if(ucaklar.oncelik_id[x]<ucaklar.oncelik_id[ucak_index]){

                     if(kuyruktaki_ucagi_ertele(ucak_index)==1){
                        kuyruktaki_ucagi_ertele(x);
                      }
                      else{
                        kuyruktaki_ucak(x);

                      }
                    }



                    //ucagin inisini ertele kuyruga ekleme

                else if(ucaklar.oncelik_id[x]>ucaklar.oncelik_id[ucak_index]){


                     if(kuyruktaki_ucagi_ertele(x)==1){
                        //ucaklar.inis_saati[ucak_index]=((ucaklar.inis_saati[ucak_index])+1);
                        kuyruktaki_ucagi_ertele(ucak_index);

                      }
                      else{
                         kuyruktaki_ucak(ucak_index);

                        break;
                      }



                    // yeni ucagi kuyruga ekle diger ucagin saatini değistir

                }
                else if(ucaklar.oncelik_id[x]==ucaklar.oncelik_id[ucak_index]){

                 if(ucaklar.ucak_id[x]<ucaklar.ucak_id[ucak_index]){

                    if(kuyruktaki_ucagi_ertele(ucak_index)==1){
                        kuyruktaki_ucagi_ertele(x);
                      }
                      else{
                        break;
                      }


                 }
                 else if(ucaklar.ucak_id[x]>ucaklar.ucak_id[ucak_index]){
                    if(kuyruktaki_ucagi_ertele(x)==1){
                        kuyruktaki_ucagi_ertele(ucak_index);
                      }
                      else{
                        break;
                      }
                 }






            }
        }
        else if(kuyruktaki_ucak(ucak_index)==1){
            f++;

        }


   }

   if(f==0 && (kuyruktaki_ucak(ucak_index)!=1)){
       printf("%d id'li ucaga %d icin inis izni verildi.\n",ucaklar.ucak_id[ucak_index],ucaklar.inis_saati[ucak_index]);
       ekle(ucaklar.oncelik_id[ucak_index],ucaklar.ucak_id[ucak_index],ucaklar.inis_saati[ucak_index]);
   }





 return 0;

}

int kuyruktaki_ucaklari_karsilastir(int ucak_index,int oncelikli_ucak){
int f=0;

for(int i=0;i<sayi;i++){

  if(inis_pisti->inis_saati[i]==ucaklar.inis_saati[ucak_index]){
    f++;
    printf("Acil inis yapmasi gereken %d id'li ucagi nedeniyle inis izniniz iptal edilmistir.\n",ucaklar.ucak_id[oncelikli_ucak]);
    printf("Sabiha Gokcen havalimanina yonlendiriliyorsunuz\n ");

  }
}


if(f==0){
  if(sayi<boyut){
        printf("%d id'li ucaga %d icin inis izni verildi.\n",ucaklar.ucak_id[ucak_index],ucaklar.inis_saati[ucak_index]);
        ekle(ucaklar.oncelik_id[ucak_index],ucaklar.ucak_id[ucak_index],ucaklar.inis_saati[ucak_index]);

}
}


return 0;
}

int kuyruktaki_ucak_saati_degistir(int ucak_index,int oncelikli_ucak){

 for(int i=0;i<sayi;i++){
   if(ucaklar.ucak_id[i]==ucak_index){
      (ucaklar.inis_saati[i])+=1;
        kuyruktaki_ucaklari_karsilastir(i,oncelikli_ucak);

   }
 }



return 0;

}

int ucak_saati_degistir(int ucak_index){
 for(int i=0;i<=num;i++){

   if(ucaklar.ucak_id[i]==ucak_index ){


      if(((ucaklar.inis_saati[i])-(temp_ucak.inis_saati[i]))>=3){
        printf("%d Ucak maximum ertelemeden dolayi baska havalimanina yonlendiriliyor.\n",ucaklar.ucak_id[i]);
        return 1;
      }
      else{
        (ucaklar.inis_saati[i])+=1;
        boyutu_asan_oncelikli_ucaklar(i);
        return -1;
      }

   }
 }



return 0;

}

int boyutu_asan_oncelikli_ucaklar(int ucak_index){
int k=0;
for(int i=0;i<sayi;i++){

    if(ucaklar.inis_saati[ucak_index] == inis_pisti->inis_saati[i]){
       k++;

        if((ucaklar.oncelik_id[ucak_index])< (inis_pisti->oncelik_id[i])){
           k=inis_pisti->ucak_id[i];
           inis_pisti->oncelik_id[i]=ucaklar.oncelik_id[ucak_index];
           inis_pisti->ucak_id[i]=ucaklar.ucak_id[ucak_index];
           inis_pisti->inis_saati[i]=ucaklar.inis_saati[ucak_index];
           kuyruktaki_ucak_saati_degistir(k,ucak_index);
           break;
        }
        else if((ucaklar.oncelik_id[ucak_index])>= (inis_pisti->oncelik_id[i])){

            ucak_saati_degistir(ucaklar.ucak_id[ucak_index]);
            break;
        }

    }



}

if(k==0 && ((ucaklar.inis_saati[ucak_index]-temp_ucak.inis_saati[ucak_index])<4)){
    printf("%d idli ucaga %d icin inis izni verildi.\n",ucaklar.ucak_id[ucak_index],ucaklar.inis_saati[ucak_index]);
    ekle(ucaklar.oncelik_id[ucak_index],ucaklar.ucak_id[ucak_index],ucaklar.inis_saati[ucak_index]);
}

return 0;



}





int input_dosyasi_oku(FILE *input){

ucaklar.inis_saati=malloc(boyut*sizeof(int));
ucaklar.oncelik_id=malloc(boyut*sizeof(int));
ucaklar.ucak_id=malloc(boyut*sizeof(int));
temp_ucak.inis_saati=malloc(boyut*sizeof(int));
temp_ucak.oncelik_id=malloc(boyut*sizeof(int));
temp_ucak.ucak_id=malloc(boyut*sizeof(int));


int oncelik=0,inis=0,ucak_id=0,a=0,y=0;



fseek(input,42,SEEK_SET);

    while(!feof(input)){

     if(y%3==0){
       fscanf(input,"%d",&a);
       oncelik=a;
       ucaklar.oncelik_id[num]=oncelik;
       temp_ucak.oncelik_id[num]=oncelik;

     }
     else if(y%3==1){
        fscanf(input,"%d",&a);
        ucak_id=a;
        ucaklar.ucak_id[num]=ucak_id;
        temp_ucak.ucak_id[num]=ucak_id;
     }
     else if(y%3==2 ){
         fscanf(input,"%d",&a);
         inis=a;
         ucaklar.inis_saati[num]=inis;
         temp_ucak.inis_saati[num]=inis;

            if((num)<1 ){
                 printf("%d idli ucaga %d icin inis izni verildi\n",oncelik,inis);
                 ekle(oncelik,ucak_id,inis);

             }
             else if(sayi>=1 && sayi<boyut){

                 ucak_onceligi(num);
                 //yazdir();



             }
             else if(sayi>=boyut){

                boyutu_asan_oncelikli_ucaklar(num);


             }

          num++;
        }

     y++;

    }
    fclose(input);



    return 1;

}

int yazdir(){
FILE *outputf =fopen("output.txt","w+");
fprintf(outputf,"%s\t","Oncelik_id");
fprintf(outputf,"%s\t","Ucak_id");
fprintf(outputf,"%s\t","Talep_edilen_inis_saati");
fprintf(outputf,"%s\t","Inis_saati");
fprintf(outputf,"%s\t","Gecikme_suresi");
fprintf(outputf,"%s\n","Kalkis_saati");
int i=0;
while(i<boyut){
   printf("Oncelik:%d\t",kalkis_pisti->oncelik_id[i]);
   printf("Ucak:%d\t",kalkis_pisti->ucak_id[i]);
   printf("Talep Edilen Inis:%d\t",kalkis_pisti->talep_edilen_inis_saati[i]);
   printf("Inis:%d\t",kalkis_pisti->inis_saati[i]);
   printf("Gecikme:%d\t",kalkis_pisti->gecikme_suresi[i]);
   printf("Kalkis:%d\n",kalkis_pisti->kalkis_saati[i]);
   fprintf(outputf,"%d\t\t",kalkis_pisti->oncelik_id[i]);
   fprintf(outputf,"%d\t\t",kalkis_pisti->ucak_id[i]);
   fprintf(outputf,"%d\t\t",kalkis_pisti->talep_edilen_inis_saati[i]);
   fprintf(outputf,"%d\t\t",kalkis_pisti->inis_saati[i]);
   fprintf(outputf,"%d\t\t",kalkis_pisti->gecikme_suresi[i]);
   fprintf(outputf,"%d\n",kalkis_pisti->kalkis_saati[i]);

   i++;
}
fclose(outputf);
return 0;
}



