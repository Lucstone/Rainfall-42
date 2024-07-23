
void run(void)

{
  fwrite("Good... Wait what?\n",1,0x13,stdout);
  system("/bin/sh");
  return;
}


void main(void)

{
  char exploit_buffer[76];
  
  gets(exploit_buffer);
  return;
}