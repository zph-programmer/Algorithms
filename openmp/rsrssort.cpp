#include<iostream>
#include<cmath>
#include<string>
#include<omp.h>
#include<cstdlib>
#include<ctime>
using namespace std;
int w;
class list {
	public:  double *data;
			 int length;  
	list(int n) {
			length = n;
			data = new double[n];
		}
	~list() {

	}
	void output() {
		for (int i = 0; i < length; i++) {
			
			cout << data[i] << ' ';
			if ((i+1)%w== 0) cout << endl;
		}
	}
	void sort(int m, int n) { //��m��ʼ��m�������оֲ���������
		double temp;
		if ((m + n )> length) n = length-m;
		for (int i = 0; i < n-1; i++) {
			for (int j = i + 1; j < n;j++) {
				if (data[m + j] < data[m + i]) {
					temp=data[m+i];
					data[m + i] = data[m + j];
					data[m + j] = temp;
				}
			}
		}
	}
	
};
void merge(double b[], int p, int q, int r) {
	double *temp;
	temp = new double[r-p+1];
	int i = p, j = q + 1;
	int m = q, n = r;
	int k = 0;
	while (i <= m&&j <= n) {
		if (b[i] <= b[j])  temp[k++] = b[i++];
		else temp[k++] = b[j++];
	}
	while (i <= m)
		temp[k++] = b[i++];

	while (j <= n)
		temp[k++] = b[j++];

	for (i = 0; i < k; i++)
		b[p + i] = temp[i];
	free(temp);
}
void mergesort(double b[], int p, int r) { //�鲢����
	if (p < r) {
		int q = (p + r) / 2;
		mergesort(b, p, q);
		mergesort(b, q + 1, r);
		merge(b, p, q, r);
	}
}

int main() {
	int n,p,tid;
	cout << "input the list length and thread numble"<<endl;
	cin >> n>>p;
	w = n / p;  //���Ȼ���
	list List(n);
	list Sample(p*p);

	srand((unsigned)time(NULL));
	for (int i=0; i < n; i++) {
		List.data[i] = rand()%100+1;
	}
	cout << "a.���Ȼ���" << endl;
	List.output();

	omp_set_num_threads(p);
#pragma omp parallel shared(List) private(tid)
	{
		tid = omp_get_thread_num();
		List.sort(tid*w, w);    //�ֲ�����
	}
	cout << "b.�ֲ�����" << endl;
	List.output();

#pragma omp parallel shared(List,p,Sample) private(tid)
	{
		tid = omp_get_thread_num();
		for (int i = 0; i < p; i++) {
			Sample.data[tid*p + i] = List.data[tid*w + i*p];
		}
	}
	cout << "c.�������" << endl;
	Sample.output();
	Sample.sort(0, Sample.length);
	cout << "d.��������" << endl;
	Sample.output();

	cout << "e.ѡ����Ԫ" << endl;

	list elem(p - 1);

	for (int i=0; i < p - 1; i++) {
		elem.data[i] = Sample.data[i*p+p];
	}
	elem.output();
	//��Ԫ����
	int **send_buf= new int*[p];   //����send_buf[][],������¼ÿ�����������ݶεĻ���λ��,��һά��ʾ���������ڶ�ά��ʾ��0����p������λ��
	for (int i=0; i < p; i++) {
		send_buf[i] = new int[p + 1];
		for (int j=0; j < p + 1; j++) {
			send_buf[i][j] = 0;
		}
	}
	
#pragma omp parallel shared(List,w,elem,send_buf) private(tid)
	{
		tid = omp_get_thread_num();
		send_buf[tid][0] = 0;   //��һ����λ��Ϊ0
		send_buf[tid][p] = w;   //��󻮷�Ϊ��Ϊ�ν�ֹ��+1��(w=n/p)  
		int  i = 1, j = 0;
		while (i < p&&j < w) {
			if (List.data[tid*w + j] > elem.data[i-1]) {
				send_buf[tid][i] = j; //�����������������Ԫ�����軮�ֵ�Ϊ����
				i++; //Ѱ����һ�����ֵ�
			}
			else j++;
		}
		while (i < p) {
			send_buf[tid][i] = w;//��ʣ�µĻ��ֵ�ȫ����Ϊw
			i++;
		}
	}
	//ͨ�����ϼ��㣬�ҵ�ÿһ�����ֶ��������е�λ��Ϊ��[send_buf[tid][i],sendbuf[tid][i+1]) ,����ɼ���γ���
	int *length;
	length = new int[p];
	double *rec_buf;
#pragma omp parallel shared(List,w,send_buf,length) private(tid,rec_buf)//��ÿһ��������ջ���
	{
		tid = omp_get_thread_num();
		length[tid] = 0;
		for (int i=0; i < p; i++) {
			length[tid] += send_buf[i][tid + 1] - send_buf[i][tid];  //��¼ÿ��������Ҫ���յ����ݳ���
		}
		rec_buf = new double[length[tid]];
		int k=0;
		for (int i=0; i < p; i++) {
			for (int j = send_buf[i][tid ]; j < send_buf[i][tid+1]; j++) {
				rec_buf[k] = List.data[i*w + j]; k++;  //��ԭ����List�н������ݵ�rec_buf��
			}
		}
		mergesort(rec_buf, 0, length[tid] - 1);//ÿһ����������ʼ���й鲢����
#pragma omp barrier  //����ͬ��·�ϣ��ȴ����ϼ������
		{
			int sum = 0;
			for (int i = 0; i < tid; i++) {
				sum += length[i];  //����ÿһ���������ͻ����ݵ��ܳ���
			}
			for (int i = 0; i < length[tid]; i++) {
				List.data[sum + i] = rec_buf[i];  //ԭ���н���ÿһ������������Ľ��
			}
		}
	}	
	cout << endl << "h.������" << endl;
	List.output();
	return 0;
}
