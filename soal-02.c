/*EL2208 Praktikum Pemecahan Masalah dengan C 2020/2021
*Modul            : 4
*Percobaan        : -
*Hari dan Tanggal : Minggu, 21 Februari 2021
*Nama (NIM)       : -
*Asisten (NIM)    : Dismas Widyanto (13218065)
*Nama File        : -
*Deskripsi        : Menghitung jarak, waktu tempuh, dan total bahan bakar untuk sebuah perjalanan
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//tipe bentukan
typedef struct{
    float x;
    float y;
    float speed;
    float dist;
}Travel;

//fungsi untuk mendapat total jarak
float distance(Travel *arr, int count){
    float total_jarak;
    float temp;
    int i;

    //hitung jarak antar titik kemudian jumlahkan
    temp=pow(arr[0].x,2)+pow(arr[0].y,2);
    arr[0].dist=sqrt(temp);
    total_jarak=sqrt(temp);
    for(i=1;i<count;i++){
        temp=pow(arr[i].x-arr[i-1].x,2)+pow(arr[i].y-arr[i-1].y,2);
        arr[i].dist=sqrt(temp);
        total_jarak+=sqrt(temp);
    }

    return total_jarak;
}

//fungsi untuk mendapat waktu tempuh
float time(Travel *arr, int count){
    float total_waktu;
    int i;

    total_waktu=0;
    for(i=0;i<count;i++){
        total_waktu+=arr[i].dist/arr[i].speed;
    }

    return total_waktu;
}

//fungsi untuk mendapat banyak bahan bakar
float bahanbakar(Travel *arr, int count){
    float total_bensin=0;
    int i;

    for(i=0;i<count;i++){
        total_bensin+=arr[i].dist/10;
    }

    return total_bensin;
}
int main(){
    //variabel
    Travel *jalur;
    int count,i;
    char filename[20],temp[30];
    char *token;
    float jarak,waktu,bensin;
    FILE* fp;

    //input filename
    printf("Masukkan jalur: ");
    scanf("%s",&filename);

    fp=fopen(filename, "r");
    count=0;

    //input data
    jalur = (Travel *) malloc(count+1);
    while(fgets(temp, sizeof(temp),fp)){
        jalur = realloc(jalur,(count+1)*sizeof(Travel));

        //input koordinat x
        token=strtok(temp,",");
        jalur[count].x=atof(token);

        //input koordinat y
        token=strtok(NULL,",");
        jalur[count].y=atof(token);

        //input speed
        token=strtok(NULL,",");
        jalur[count].speed=atof(token);

        count+=1;
    }

    fclose(fp);

    //proses perhitungan
    jarak=distance(jalur, count);
    waktu=time(jalur, count);
    bensin=bahanbakar(jalur,count);

    //output
    printf("Jarak yang ditempuh adalah: %.2f KM\n",jarak);
    printf("Waktu yang dibutuhkan adalah: %.0f Jam %.0f Menit\n",floor(waktu),(waktu-floor(waktu))*60);
    printf("Bahan bakar yang dibutuhkan adalah: %.2f Liter",bensin);

    free(jalur);
    return 0;
}
