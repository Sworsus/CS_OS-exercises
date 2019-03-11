#include "_aux.h"


// Bucle de espera SW corto
void short_wait(void)
{
  int w;
  for (w=0; w<100; w++)
  { w++;
    w--;
  }
}

// Bucle de espera SW largo
void long_wait(void)
{
	int w;
    for (w=-800000; w<800000; w++)
    { w++;
      w--;
    }
}
