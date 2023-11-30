#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int get_line(int partitions) {
  int c = 0;
  int parsingId = 1;
  int sum = 0;
  int hashcode = 0;
  int index = 1;
  char buf[65536]; // store the ID
  while ((c = getc(stdin)) != EOF) {
    if (index >= 65535) { // if on the off chance we exceeded space for ID chars
      //TODO: print something?
      buf[index-1] = 0; // add null byte
      printf("0\t%s",buf);
      parsingId = 0;
    }
    switch (c) {
    case ' ':
    case EOF:
    case '\t':
    case '\n':
      if (parsingId) {
        buf[index-1] = 0; // add null byte
        hashcode = sum % partitions;
        printf("%d\t%s", hashcode, buf); // print line
        parsingId = 0;
      }
      if (c != EOF) putc(c, stdout);
      break;
    default:
      if ( parsingId ) {
        sum += c * index;
        buf[index-1] = c; // save the ID to buffer
      } else {
        putc(c, stdout);
      }
      break;
    }
    if (c == '\n' || c == EOF) return c;
    index++;
  }
}

int main(int argc, char **argv)
{
  int c = 0;
  int partitions = atoi(getenv("partitions"));
  
  while (get_line(partitions) != EOF) {
    fflush(stdin);
  }
  return 0;
}
