/* 第一引数:読み込むテキストファイル*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define PHONE_NUM 53             /*音素の種類*/
void bubbleSort(double *N, int len); //バブルソート関数のprototype宣言
int main(int argc,char *argv[]){

  FILE *fp_in, *fp_in2,*result;             /*ファイルポインタ*/
  int i,j,count=0;                 /*ループカウンタ、音素の種類*/
  int freq[PHONE_NUM][PHONE_NUM];             //出現回数のカウンタ
  double freqsum=0.0;              //全体の出現回数のカウンタ
  char onso[PHONE_NUM][5];        //音素を格納する変数
  double bigram[PHONE_NUM][PHONE_NUM];      //ユニグラムを格納する配列
  double bigram_sort[PHONE_NUM*PHONE_NUM];//ソートしたユニグラムを格納する配列
  int word=0,word1=0;            //ファイルで読み込むint型の変数
  char word2[5];                 //ファイルで読み込むchar型の変数
  int word_pre = 0;
  int bigram_counter= 0,bigram_counter2 =0;

  for(j=0;j<PHONE_NUM;j++){
    for(i=0;i<PHONE_NUM;i++){
      freq[j][i] = 0;
      bigram[j][i] = 0.0;
    }
  }

  if(argc != 3){		   /* 引数が不適切だった場合に */
    fprintf(stderr, "引数が不適切です。\n"); /* エラー文を表示し */
    return -1;		           /* 異常終了 */
  }

  fp_in2 = fopen(argv[2], "r");     /*音素ファイルを読み込み*/

  if(fp_in2 == NULL){		   /* fopenが失敗している場合 */
  fprintf(stderr, "Cannot open file:%s\n", argv[2]); /* エラー文を表示し */
    return -1;		           /* 異常終了 */
  }

  while(fscanf(fp_in2,"%d%s", &word1,word2) != EOF){ /*ファイルデータが読み終わるまで*/
      memcpy(onso[count],word2,sizeof(word2)); //音素ファイルのデータを配列に格納
      count++;
  }
  count = 0;

  fp_in = fopen(argv[1], "r");     /*辞書ファイルを読み込み*/

  if(fp_in == NULL){		   /* fopenが失敗している場合 */
    fprintf(stderr, "Cannot open file:%s\n", argv[1]); /* エラー文を表示し */
    return -1;		           /* 異常終了 */
  }

  word =0;
  word_pre =0;
  while(fscanf(fp_in,"%d",&word) != EOF){ /*ファイルデータが読み終わるまで*/
    if(word == 999){
      word_pre = 0;
    }else{
      freq[word_pre][word]++;   //出現した文字をカウント
      freqsum++;    //全体の文字数をカウント
      word_pre = word;
    }
  }


  for(j=0;j<PHONE_NUM;j++){
    for(i=0;i<PHONE_NUM;i++){
      bigram[j][i] = freq[j][i]/freqsum;   //ユニグラムを計算
      if(bigram[j][i] != 0){
      // printf("bigram[%d][%d]:%lf",j,i,bigram[j][i]);
      // printf("\n");
      }
    }
  }

  for(j=0;j<PHONE_NUM;j++){
    for(i=0;i<PHONE_NUM;i++){
      bigram_sort[j*PHONE_NUM+i] = bigram[j][i];
      bigram_counter = j*PHONE_NUM+i;
      //printf("%d ",bigram_counter);
      //printf("%lf",bigram_sort[bigram_counter]);
   }
 }

  bubbleSort(bigram_sort, PHONE_NUM*PHONE_NUM);  //ユニグラムをバブルソート関数を呼び出し、ソート

  for(bigram_counter=0;bigram_counter<10;bigram_counter++){
      for(j=0;j<PHONE_NUM;j++){
        for(i = 0;i<PHONE_NUM;i++){
          if(bigram_sort[bigram_counter] == bigram[j][i] && bigram[j][i] != 0){
           printf("higher order bigram[%d]:%lf\n",bigram_counter,bigram_sort[bigram_counter]);
          }
        }
      }
    }
    printf("\n");

  count = 1;
  bigram_counter = PHONE_NUM*PHONE_NUM-1;
  while(count < 10){
    for(j=0;j<PHONE_NUM;j++){
      for(i = 0;i<PHONE_NUM;i++){
          if(bigram_sort[bigram_counter] == bigram[j][i] && bigram_sort[bigram_counter] != 0){
            printf("lower order bigram[%d]:%lf\n",count,bigram_sort[bigram_counter]);
            count++;
            if(bigram_sort[bigram_counter-1] == bigram_sort[bigram_counter]){
              printf("%sto%s bigram[%d]:%lf\n", onso[j], onso[i],bigram_counter,bigram_sort[bigram_counter]);
              bigram_counter--;
              break;
              break;
            }

          }
        }
      }
      bigram_counter--;

    }


    return - 1;

}

//バブルソート関数
void bubbleSort(double *N, int len){
  int i,j;
  double temp = 0;
  for(i=0; i<len; i++){
    for(j=i+1; j<len; j++){
      if(N[i] < N[j]){
        temp = N[i];
        N[i] = N[j];
        N[j] = temp;
      }
    }
  }
}
