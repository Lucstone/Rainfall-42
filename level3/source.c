
void v(void)

{
  char exploit_buffer [520];
  
  fgets(exploit_buffer,0x200,stdin);
  printf(exploit_buffer);

  if (global_variable == 0x40) {
    fwrite("Wait what?!\n",1,0xc,stdout);
    system("/bin/sh");
  }
  return;
}


void main(void)
{
  v();
  return;
}
