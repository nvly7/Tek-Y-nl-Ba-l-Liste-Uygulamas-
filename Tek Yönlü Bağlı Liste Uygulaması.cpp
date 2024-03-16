/*Uygulamamýz tek yönlü baðlý liste yapýsýný kullanarak aþaðýda verildiði þekilde text dosyasýnda bulunan 
bilgileri baðlý listeye aktaracaktýr. Dosyanýn her bir satýrýnda “Numara”, “Ad” ve “Soyad” bilgileri aralarýnda 
“#” olacak þekilde bulunmaktadýr.Örnek bir text dosya içeriði: 
 251#Ali#Can
 123#Cemil#Ates¸
 858#Ahmet#Kurt
 ...
 322#Eda#Kahveci
Uygulama çalýþtýðýnda ilk olarak text dosyasýnda bulunan bilgiler tek yönlü baðlý listeye text dosyasýnda 
verilen sýrasýyla eklenecektir. Daha sonra kullanýcýya yapmak istediði iþlem aþaðýda verilen menü þeklinde 
sorulacaktýr:
1. Listeleme
2. Ekleme
3. Arama
4. Silme
5. Taþýma
6. Çýkýþ
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ogrenci {
    int numara;
    char ad[50];
    char soyad[50];
    struct ogrenci*sonraki;
};

struct ogrenci*ilk=NULL;

void ekle(int numara,char ad[],char soyad[]){
    struct ogrenci* yeniogrenci=(struct ogrenci*)malloc(sizeof(struct ogrenci));
    yeniogrenci->numara=numara;
    strcpy(yeniogrenci->ad,ad);
    strcpy(yeniogrenci->soyad,soyad);
    yeniogrenci->sonraki=NULL;

    if(ilk==NULL){
        ilk=yeniogrenci;
        return;
    }

    struct ogrenci*temp=ilk;
    while(temp->sonraki!=NULL){
        if(temp->numara==numara){
            printf("Bu numaraya ait bir kayit vardir!\n");
            free(yeniogrenci);
            return;
        }
        temp=temp->sonraki;
    }
    temp->sonraki=yeniogrenci;
}

void arama(char soyad[]) {
    struct ogrenci*temp=ilk;
    int bul=0;
	int sira=1;

    while(temp!=NULL){
        if(strcmp(temp->soyad,soyad)==0){
            char cevap;
            printf("Aramak istenen kayit bulundu mu?(e/h):");
            scanf("%c",&cevap);
            if(cevap=='e'){
            	bul=1;
                printf("Aranan kayit bulundu!\n");
                printf("Numara:%d,Ad:%s,Soyad:%s\n",temp->numara,temp->ad,temp->soyad);
                printf("Listenin %d.sirasinda bulundu.\n",sira);
                return;
            }
        }
        temp=temp->sonraki;
        sira++;
    }

    if (!bul){
        printf("Aranilan kayit bulunamadi!\n");
    }
}

void listele() {
    struct ogrenci*temp=ilk;
    int sira=1;
    while(temp!=NULL){
        printf("%d. Numara:%d,Ad:%s,Soyad:%s\n", sira,temp->numara,temp->ad,temp->soyad);
        temp=temp->sonraki;
        sira++;
    }
}

void silme(int numara) {
    struct ogrenci*temp=ilk;
    struct ogrenci*onceki=NULL;
    int bul=0;

    if(temp!=NULL && temp->numara==numara){ 
        ilk= temp->sonraki;
        free(temp);
        printf("Kayit silindi!\n");
        return;
    }

    while(temp!=NULL && temp->numara!=numara){
        onceki=temp;
        temp=temp->sonraki;
    }

    if(temp==NULL){
        printf("Aranilan kayit bulunamadi!\n");
        return;
    }

    onceki->sonraki=temp->sonraki;
    free(temp);
    printf("Kayit silindi.\n");
}


void tasima(int numara,int x){
    struct ogrenci*temp=ilk;
    struct ogrenci*onceki=NULL;
    int uzunluk=0;
    int sira=1;
    while(temp!=NULL){
    	uzunluk++;
    	temp=temp->sonraki;
	}
	temp=ilk;
	if(x>uzunluk){
		printf("Liste boyutu disinda bir deger girdiniz!");
	}
	if(x==1){
		if(temp->numara==numara){
			printf("Kayit zaten istenen yerdedir!");
			return;
		}
		
	}
	else{
		struct ogrenci*simdiki=ilk;
		if(simdiki->numara==numara){
		    while(simdiki!=NULL && sira){
		    	simdiki=simdiki->sonraki;
		    	sira++;
			}
		}
	}
}
void dosyayaekle(){
    FILE*dosya=fopen("kayitlar.txt", "w");

    if (dosya==NULL){
        printf("Dosya olusturulamadi!\n");
        return;
    }

    struct ogrenci*temp=ilk;

    while(temp!=NULL){
        fprintf(dosya, "%d#%s#%s\n",temp->numara,temp->ad,temp->soyad);
        temp=temp->sonraki;
    }

    fclose(dosya);
}
int main() {
    FILE*dosya=fopen("kayitlar.txt", "r");

    if(dosya==NULL){
        printf("Dosya bulunamadi veya acilamadi!\n");
        return 1;
    }

    while(!feof(dosya)){
        int numara;
        char ad[50];
        char soyad[50];

        fscanf(dosya,"%d#%[^#]#%[^#\n]\n",&numara,ad,soyad);
        ekle(numara,ad,soyad);
    }

    fclose(dosya);

    int secim;
    int numara;
    char ad[50];
    char soyad[50];
    char aranansoyad[50];
    int x;

    do{
        printf("1.Listeleme\n2.Ekleme\n3.Arama\n4.Silme\n5.Tasima\n6.Cikis\nSeciminiz: ");
        scanf("%d",&secim);
        switch(secim){
            case 1:
                listele();
                break;
            case 2:
                printf("Numara:");
                scanf("%d",&numara);
                printf("Ad:");
                scanf("%s",ad);
                printf("Soyad:");
                scanf("%s",soyad);
                ekle(numara,ad,soyad);
                listele();
                break;
            case 3:
                printf("Aranan Soyad:");
                scanf("%s",aranansoyad);
                arama(aranansoyad);
                break;
            case 4:
                printf("Silinecek Numara:");
                scanf("%d",&numara);
                silme(numara);
                break;
            case 5:
                printf("Tasima islemi yapilamamaktadir!\n");
                break;
            case 6:
                dosyayaekle();
                printf("Programdan ciktiniz.\n");
                break;
            default:
                printf("Gecersiz secim!\n");
        }
    }while(secim!=6);
    return 0;
}

