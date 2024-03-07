#include <stdio.h>  // printf().
#include <conio.h>  // clrscr() and getch().

#define LENGTH 10
#define SIZEOF_INT_IN_BYTES 2
#define LENGTH_BYTES LENGTH * SIZEOF_INT_IN_BYTES

void PrintArray(const char* name, int* array, int size) {
   printf("Array %s: ", name);
   for(int i=0; i<size; ++i)
      printf("%d ", array[i]);
   printf("\n");
}

int main() {
  clrscr();  // Clear the terminal screen.

  // Create two 1D arrays.
  int source[LENGTH]      = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  int destination[LENGTH] = { 1, 1, 0, 0, 1, 1, 0, 0, 1, 1 };

  PrintArray("source before copy", source, LENGTH);
  PrintArray("destination before copy", destination, LENGTH);

  // 1. LOOP and LEA.
  asm {
    cld
    mov cx,LENGTH_BYTES  // Arrays length * sizeof(int) = 10 * 2 = 20.
    lea si,source        // Load the address of source array into SI.
    lea di,destination   // Load the address of destination array into DI.
  };

  copyLoop: asm {
    mov ax,[si]  // Load the value at address SI into AL.
    mov [di],ax  // Store the value in AL at address DI.

    inc si  // Increment SI == shift pointer to the next element.
    inc di  // Increment DI == shift pointer to the next element.

    loop copyLoop  // Loop (goto copyLoop label) until cx value > 0.
  };

  PrintArray("source after copy", source, LENGTH);
  PrintArray("destination after copy", destination, LENGTH);

  getch();

  return 0;
}
