#include <stdio.h>
//DPマッチングを用いた最短経路の探索
//これは手で計算したDPマッチングの課題をプログラムで実装した物です(経路表示は無し)

//縦横斜めを計算してから代表値を決めそれを配列に格納していくやり方

int main(void){
	//問題のデータの羅列
	char data[5][6] = {{3,2,2,2,3,1},
				   	   {3,1,3,1,2,2},
				       {1,2,2,3,1,2},
				       {3,3,1,3,1,1},
				       {2,1,3,3,2,2}};

	
	int i, j;
	long result[5][6];

	//計算ルール　1.横,縦移動の場合 足す　2.斜め移動の場合 移動先の数字の2倍の値を足す
	//計算部分の実装
	i = 0; j = 0;
	
	//初期処理として最初の縦と横の計算を先にしておく
	result[0][0] = data[0][0];
	for(;j<5; j++){
		result[i][j+1] = result[i][j] + data[i][j+1]; 
	}
	for(j=0;i<4;i++){
		result[i+1][j] = result[i][j] + data[i+1][j];
	}
	//計算部分
	i = 0; j = 0;
	long vertical, side, diagonal, min;

	for(i=0;i<4;i++){
		for(j=0;j<5;j++){
			vertical = result[i][j+1] + data[i+1][j+1];
			side = result[i+1][j] + data[i+1][j+1];
			diagonal = result[i][j] + data[i+1][j+1]*2;
			min = vertical;
			if(min > side){
				min = side;
			}
			if(min > diagonal){
				min = diagonal;
			}
			result[i+1][j+1] = min;
		}
	}
	//確認
	for(i=0;i<5;i++){
		for(j=0;j<6;j++){
			printf("%.2ld,", result[i][j]);
			if(j==5)
				printf("\n");
		}
	}

	//結果表示   配列の大きさの値を初期値として入れる
		//通った座標を随時出力(随時なのでfor文)(if文で判断後に出力)
		//printf("[%d][%d]", x, y);

	return 0;
}
