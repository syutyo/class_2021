#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//DPマッチングの最終版

struct tango_data{
	char file_name[20];
	char loc[20];
	int  size;
	double data[150][15];
};
struct tango_data t_data[100], input_data[100];

double kyori_data[150][150];
double tan_kyori;

void file_read(void);
void kyori(int num_1, int num_2);
void dynamic(int num_1, int num_2);

int main(void){
	double min = 10000;
	int i,j, num_1, num_2, min_num_2, correct = 0;

	//100単語読み込み
	file_read();
	//1万通り試す
	printf("~~~~~単語音声認識を開始します~~~~~\n");
	printf("----誤認リスト----\n");
	for(num_1=0;num_1<100;num_1++){
		tan_kyori = 0;
		min = 10000;
		for(num_2=0;num_2<100;num_2++){
			kyori(num_1, num_2);
			dynamic(num_1, num_2);
			if(min > tan_kyori){
				min = tan_kyori;
				min_num_2 = num_2;
			}
		}
		if(!strcmp(t_data[num_1].loc, input_data[min_num_2].loc)){
			correct++;
		}else{
			printf("%s %s\n",t_data[num_1].loc,input_data[min_num_2].loc);
		} 
		//printf("%s  %s\n", t_data[num_1].loc,input_data[min_num_2].loc);	
	}
	printf("認識率 : %d％\n", correct);

	return 0;
}
//ファイルの読み込み関数
void file_read(void){
	FILE *fp1;
	char path[100];
	int i,j, num=0, count;
	for(num = 0;num < 100; num++){
		sprintf(path, "./city_mcepdata/city022/city022_%.3d.txt", num+1);
		if((fp1 = fopen(path,"r")) == NULL){
			printf("ファイルを開けませんでした\n");
			exit(1);
		};
	//読み込んだものを構造体に格納
		fscanf(fp1,"%s%s%d", t_data[num].file_name, t_data[num].loc, &t_data[num].size);

		for(i=0;i<t_data[num].size;i++){
			for(j=0;j<15;j++){
				fscanf(fp1, "%lf", &t_data[num].data[i][j]);
			}
		}
		fclose(fp1);
	}
	for(num = 0;num < 100; num++){
		sprintf(path, "./city_mcepdata/city021/city021_%.3d.txt", num+1);
		if((fp1 = fopen(path,"r")) == NULL){
			printf("ファイルを開けませんでしたyo\n");
			exit(1);
		};
	//読み込んだものを構造体に格納
		fscanf(fp1,"%s%s%d", input_data[num].file_name, input_data[num].loc, &input_data[num].size);

		for(i=0;i<input_data[num].size;i++){
			for(j=0;j<15;j++){
				fscanf(fp1, "%lf", &input_data[num].data[i][j]);
			}
		}
		fclose(fp1);
	}
}

void kyori(int num_1, int num_2){
	int i,j,k;
	
	for(i=0;i<t_data[num_1].size;i++){
		for(j=0;j<input_data[num_2].size;j++){
			kyori_data[i][j] = 0;
			for(k=0;k<15;k++){
				kyori_data[i][j] += pow(t_data[num_1].data[i][k] - input_data[num_2].data[j][k] , 2);
			}
			kyori_data[i][j] = sqrt(kyori_data[i][j]);
		}
	}
}

void dynamic(int num_1,int num_2){
	int i, j, count;
	double result[150][150];

	//計算ルール　1.横,縦移動の場合 足す　2.斜め移動の場合 移動先の数字の2倍の値を足す
	//計算部分の実装
	i = 0;

	//初期処理として最初の縦と横の計算を先にしておく
	result[0][0] = kyori_data[0][0];
	for(j=0;j<input_data[num_2].size; j++){
		result[i][j+1] = result[i][j] + kyori_data[i][j+1]; 
	}
	for(j=0;i<t_data[num_1].size;i++){
		result[i+1][j] = result[i][j] + kyori_data[i+1][j];
	}
	//計算部分
	double vertical, side, diagonal, min;

	for(i=0;i<t_data[num_1].size-1;i++){
		for(j=0;j<input_data[num_2].size-1;j++){
			vertical = result[i][j+1] + kyori_data[i+1][j+1];
			side = result[i+1][j] + kyori_data[i+1][j+1];
			diagonal = result[i][j] + kyori_data[i+1][j+1]*2;
			min = vertical;
			if(min > side)
				min = side;
			if(min > diagonal)
				min = diagonal;
			result[i+1][j+1] = min;
		}
	}
	tan_kyori = result[t_data[num_1].size-1][input_data[num_2].size-1] / (t_data[num_1].size + input_data[num_2].size);
}