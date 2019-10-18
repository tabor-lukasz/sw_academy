#include "judge.h"
#include <cstdio>
using namespace std;

char in_buff[6666];
char out_buff[6666];

void judge::run(iKAL* solution){
	int N, pos, len;
	char type;
	scanf("%d ", &N);
	for (int i = 0; i < N; i++) {
		scanf("%c %d %d ", &type, &pos, &len);
		int type_int = type;
		printf("%c(%d)\n", type, type_int);
		if(type == 'I'){
			scanf("%s ", in_buff);
			printf("insert(%s, %d, %d, ...)\n", in_buff, pos, len);
			solution->insert(in_buff, pos, len, out_buff);
		} else {
			printf("remove(%d, %d, ...)\n", pos, len);
			solution->remove(pos, len, out_buff);
		}
		printf("%s\n", out_buff);
	}
}