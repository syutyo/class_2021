#include <stdio.h>
#include <stdlib.h>
//ファイル読み込みに関してのプログラム

struct tango_data{
	char file_name[20];
	char loc[10];    //locは locateからつけた
	int  size;
	double data[150][15];
};

//t_data はターゲットデータ　, input_dataは入力データを表している
struct tango_data t_data[100], input_data[100];
void file_read(void);

int main(void){
	int i,j;
	file_read();

	//確認用コード
	//t_data内の数字を任意に選べば単語のデータがみられる
	for(j=0;j<t_data[45].size;j++){
		for(i=0;i<15;i++){
			printf("%lf", t_data[45].data[j][i]);
		}
		printf("\n");
	}
	printf("\n");
	for(j=0;j<input_data[3].size;j++){
		for(i=0;i<15;i++){
			printf("%lf", input_data[3].data[j][i]);
		}
		printf("\n");
	}

	return 0;
}

//ファイルの読み込み関数(指定されたファイルを使う感じ？)
void file_read(void){
	FILE *fp1, *fp2;
	char path[100];
	int i,j, num=0, count;
	//ターゲットデータの読み込み
	for(num = 0;num < 100; num++){
		sprintf(path, "./city_mcepdata/city011/city011_%.3d.txt", num+1);  // ここをいじってファイル12,21,22を選んでる(scanfを使って指定できるかも)
		//ファイルのエラーを知らせるコード
		if((fp1 = fopen(path,"r")) == NULL){
			printf("ファイルを開けませんでした\n");
			exit(1);
		};
	//読み込んだものを構造体に格納
		fscanf(fp1,"%s%s%d", t_data[num].file_name, t_data[num].loc, &t_data[num].size);

		for(j=0;j<t_data[num].size;j++){
			for(i=0;i<15;i++){
				fscanf(fp1, "%lf", &t_data[num].data[j][i]);
			}
		}
		fclose(fp1);
	}

	//入力データの読み込み
	for(num = 0;num < 100; num++){
		sprintf(path, "./city_mcepdata/city012/city012_%.3d.txt", num+1);
		if((fp2 = fopen(path,"r")) == NULL){
			printf("ファイルを開けませんでしたyo\n");
			exit(1);
		};
	//読み込んだものを構造体に格納
		fscanf(fp2,"%s%s%d", input_data[num].file_name, input_data[num].loc, &input_data[num].size);

		for(j=0;j<input_data[num].size;j++){
			for(i=0;i<15;i++){
				fscanf(fp2, "%lf", &input_data[num].data[j][i]);
			}
		}
		fclose(fp2);
	}
}
//    fopen をつかったら fcloseで閉じる