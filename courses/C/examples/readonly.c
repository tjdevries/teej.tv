int main() {
  // This is fine, and will be OK.
  //  This is in mutable memory
  char x[] = "hello world";
  x[0] = 'j';

  // This will segfault with a bus error
  //  The string literal is actually in read only memory
  char *pointer = "hello";
  pointer[0] = 'j';

  return 0;
}
