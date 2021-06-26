#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

char input[200][20]; //���뱣��
char str[20]; //ÿ�������
char files[200][20]; //����Ҫ������ļ���ֻ�������Ŀ¼�µģ����������ã�
int blank;//�ո�Ĵ���
int dirs[200]; //������ʾǶ�׵ĵڼ����ļ���ÿ���¼���ǵ�ǰĿ¼��input�е�����
int dnum; //��ǰ���ĸ�Ŀ¼�£���dirs����ʹ��
/*����ո�*/
void printBlank(){ 
	for(int i=0;i<blank;i++){
	printf("| ");
	}
}
/**����ĺ���������qsort*/

int compare(const void *elem1,const void *elem2)
{
	return (strcmp((char*)elem1,(char*)elem2));
}

//�����������д���
void process(int pos){
	switch(input[pos][0]){
	case '*':{ //������β�Ĵ����ӵ�ǰλ����������ͷ������file�ͱ��棬׼�����
			int i=pos;
			int j=0;
			while(i>=0){
			if(input[i][0]=='f'){
			strcpy(files[j++],input[i]);
			}	
			i--;
			}	
			qsort(files,j,20,compare);
			for(i=0;i<j;i++){
				printBlank();
				puts(files[i]);
				}
			break;
		}	
	case 'd':{ //����Ŀ¼�����
			blank++;
			printBlank();
			printf("%s\n",input[pos]);
			dirs[dnum++]=pos;
			process(pos+1);
			break;
		}
	case 'f':{ //�����ļ�������
		process(pos+1);
		break;
	}
	case ']':{ //����]׼����ӡ��ǰĿ¼�µ��ļ�
		int i=pos;
		int j=0;
		while(i>dirs[dnum-1]){
			if(input[i][0]=='f'){
			strcpy(files[j++],input[i]);
			input[i][0]='s';
			}
		i--;
		}
		qsort(files,j,20,compare);
		for(i=0;i<j;i++){
		printBlank();
		puts(files[i]);
	}
	if(dnum>1) dnum--;
	blank--;
	process(pos+1);
	break;
	}
	}
}

int main(){
	int i=0;
	int flag=0;
	int n=1;
	while(scanf("%s",str)!=EOF){ //�����ַ���
		if(str[0]=='#') break; //����
		if(str[0]!='*'){ //һֱ����
		strcpy(input[i++],str);
		}else{
		strcpy(input[i],"*"); //����һ�������׼������
		printf("DATA SET %d:\n",n++);
		printf("ROOT\n");
		blank=0;
		process(0);
		i=0;	
		puts("");	
	}
	}
	system("pause");
	return 0;
}
