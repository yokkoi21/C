/* 第一引数:読み込むテキストファイル*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define PHONE_NUM 53             /*音素の種類*/

double* bubbleSort(double* , int ); //バブルソート関数のprototype宣言

int main(int argc,char *argv[]){

  FILE *fp_in, *fp_in2,*result;             /*ファイルポインタ*/
  int i,j,count=0;                 /*ループカウンタ、音素の種類*/
  int freq[PHONE_NUM];             //出現回数のカウンタ
  double freqsum=0.0;              //全体の出現回数のカウンタ
  char onso[PHONE_NUM][5];        //音素を格納する変数
  double unigram[PHONE_NUM];      //ユニグラムを格納する配列
  double unigram_sort[PHONE_NUM];//ソートしたユニグラムを格納する配列
  int word=0,word1=0;            //ファイルで読み込むint型の変数
  char word2[5];                 //ファイルで読み込むchar型の変数

  for(i=0;i<PHONE_NUM;i++){
    freq[i] = 0;
    unigram[i] = 0.0;
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

  while(fscanf(fp_in,"%d",&word) != EOF){ /*ファイルデータが読み終わるまで*/
    if(word != 999){          /*行末を表す999でなければカウント*/
      freq[word]++;   //出現した文字をカウント
      freqsum++;    //全体の文字数をカウント
    }
  }



  for(i=0;i<PHONE_NUM;i++){
    unigram[i] = freq[i]/freqsum;   //ユニグラムを計算
    unigram_sort[i] = freq[i]/freqsum;    ////別の配列にも格納
  }

  bubbleSort(unigram_sort, PHONE_NUM);  //ユニグラムをバブルソート関数を呼び出し、ソート

  for(j=0;j<PHONE_NUM;j++){
    for(i=0;i<PHONE_NUM;i++){
    if(unigram_sort[j] == unigram[i] && unigram[i] != 0 && unigram_sort[j] != 0){  //ユニグラム確率が同じ場合かつユニグラム確率が0以外の場合
        printf("onso:%s unigram[%d]:%lf count:%d \n",onso[i], i, unigram_sort[j],freq[i]);  //それぞれの音素のユニグラム確率と出現回数を表示
        unigram_sort[j] = 0.0;  //ユニグラム確率が同じ場合に2度表示しないように0で初期化を行う
        unigram[i] = 0.0;  //ユニグラム確率が同じ場合に2度表示しないように0で初期化を行う
    }
  }

}
}

//バブルソート関数
double* bubbleSort(double *N, int len){
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


  return N;
}
