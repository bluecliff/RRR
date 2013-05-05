#include <iostream>
using namespace std;
#include "bitvector.h"
#include "commons.h"

int main()
{
    bitvec_t v;
    for(int i=0; i< 100;i++)
    {
        v.setbits(blog(i)+1,(u64)i);
    }
	int offset=0;
    for(int i=0;i < 100;i++)
    {
		int k=blog(i)+1;
        cout<<v.getbits(offset,k)<<" ";
		offset+=k;
    }
    cout<<endl;
    return 0;
}
