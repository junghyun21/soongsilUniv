#include "types.h" // for uint size at memsize() in sysproc.c   
#include "user.h"

#define SIZE 2048

int main(void)
{
   int msize = memsize();
   printf(1, "The process is using %dB\n", msize);

   char *tmp = (char*)malloc(SIZE * sizeof(char));

   printf(1, "Allocating more memory\n");
   msize = memsize();
   printf(1, "The process is using %dB\n", msize);

   free(tmp);
   printf(1, "Freeing memory\n");
   msize = memsize();
   printf(1, "The process is using %dB\n", msize);

   exit();
}
