
void main(void)
{
  n();
  return;
}

void n(void)
{
  char exploit_buffer [520];
  
  fgets(exploit_buffer,0x200,stdin);
  p(exploit_buffer);
  if (global_variable == 0x1025544) {
    system("/bin/cat /home/user/level5/.pass");
  }
  return;
}


void p(char *param_1)
{
  printf(param_1);
  return;
}
