int main(int param_1,int param_2)

{
  int uVar1;
  char string [40];
  int number;
  
  number = atoi(*(char **)(param_2 + 4));
  if (number < 10) {
    memcpy(string,*(void **)(param_2 + 8),number * 4);
    if (number == 0x574f4c46) {
      execl("/bin/sh","sh",0);
    }
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}
