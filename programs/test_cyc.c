#include "sampler.h"

#ifndef SIZE
#define SIZE 10000
#endif

int main()
{
    int i, tmp, dim[SIZE];

    SAMPLE;
    for (i=0; i<SIZE/10; i++) { tmp=dim[0]; dim[0]=dim[i]; dim[i]=tmp; }
    SAMPLE;
    for (i=0; i<SIZE/5; i++) { tmp=dim[0]; dim[0]=dim[i]; dim[i]=tmp; }
    SAMPLE;
    for (i=0; i<SIZE/2; i++) { tmp=dim[0]; dim[0]=dim[i]; dim[i]=tmp; }
    SAMPLE;
    for (i=0; i<SIZE; i++) { tmp=dim[0]; dim[0]=dim[i]; dim[i]=tmp; }
    SAMPLE;
    for (i=0; i<SIZE/10; i++)
        { tmp=dim[0]; dim[0]=dim[i]; dim[i]=tmp; }
    SAMPLE;
    for (i=0; i<SIZE/5; i++)
        { tmp=dim[0]; dim[0]=dim[i]; dim[i]=tmp; }
    SAMPLE;
    for (i=0; i<SIZE/2; i++)
        { tmp=dim[0]; dim[0]=dim[i]; dim[i]=tmp; }
    SAMPLE;
    for (i=0; i<SIZE; i++)
        { tmp=dim[0]; dim[0]=dim[i]; dim[i]=tmp; }
    SAMPLE;
    for (i=0; i<SIZE/10; i++)
        { tmp=dim[0];
            dim[0]=dim[i];
            dim[i]=tmp;
        }
    SAMPLE;
    for (i=0; i<SIZE/5; i++)
        { tmp=dim[0];
            dim[0]=dim[i];
            dim[i]=tmp;
        }
    SAMPLE;
    for (i=0; i<SIZE/2; i++)
        { tmp=dim[0];
            dim[0]=dim[i];
            dim[i]=tmp;
        }
    SAMPLE;
    for (i=0; i<SIZE; i++)
        { tmp=dim[0];
            dim[0]=dim[i];
            dim[i]=tmp;
        }
    SAMPLE;
}
