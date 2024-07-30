void main(undefined4 param_1,int param_2)

{
  char *__dest;
  function **ppcVar1;
  
  __dest = (char *)malloc(0x40);
  ppcVar1 = (function **)malloc(4);
  *ppcVar1 = m;
  strcpy(__dest,*(char **)(param_2 + 4));
  (**ppcVar1)();
  return;
}


void n(void)

{
  system("/bin/cat /home/user/level7/.pass");
  return;
}
