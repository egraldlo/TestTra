#include <string>
using namespace std;
#include <memory.h>
#include <malloc.h>
#include <fcntl.h>
#include <sys/mman.h>

void insertion_sort(string file, int first, int last)
{      //0 4
	printf("cao ni mage bi\n");
	char *base=0;
	unsigned file_length_=1024*1024*1024;
	int fd_=open(file.c_str(),O_RDONLY);
	base= (char*) mmap(0, file_length_, PROT_READ, MAP_PRIVATE, fd_, 0);
	printf("cao ni mage bi\n");
	int i,j;
	int temp;
	printf("cao ni mage bi\n");
	for (i = first+1; i<=last;i++)
	{
		printf("cao ni mage bi\n");
		temp = *(reinterpret_cast<int*>(base)+i);//array[i];
		printf("cao ni mage bi%d \n",temp);
		j=i-1;
		printf("cao ni mage bi\n");
		//與已排序的數逐一比較，大於temp時，該數向後移
		while((j>=first) && (*(reinterpret_cast<int*>(base)+j) > temp))  //当first=0，j循环到-1时，由于[[短路求值]]，不会运算array[-1]
		{
			printf("cao ni mage bi cao \n");
			int *val=(reinterpret_cast<int*>(base)+j);
			*(reinterpret_cast<int*>(base)+j+1)= *val;
			j--;
		}
		printf("cao ni mage bi cao \n");
		int *v=(reinterpret_cast<int*>(base)+i);
		*(reinterpret_cast<int*>(base)+j+1)=*v;
	}
	for(int i=0;i<4;i++){
		printf("data: %d\n",*(reinterpret_cast<int*>(base)+i));
	}
}
