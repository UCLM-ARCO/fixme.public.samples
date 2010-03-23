#include <stdio.h>
#include <static/static.h>

int main(int argc, char *argv[])
{
  printf("Static: %d", dup(gimme_five()));
  return 0;
}
