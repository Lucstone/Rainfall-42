/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaidu <lnaidu@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 15:12:47 by lnaidu            #+#    #+#             */
/*   Updated: 2024/08/25 15:24:05 by lnaidu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void p(char *param_1,char *param_2)
{
    char *pcVar1;
    char buffer [4104];

    puts(param_2);
    read(0,buffer,0x1000); // 0x1000 = 4096
    pcVar1 = strchr(buffer,10);
    *pcVar1 = '\0';
    strncpy(param_1,buffer,0x14); // 0x14 = 20
    return;
}

void pp(char *param_1)
{
    char cVar1;
    int uVar2;
    char *pcVar3;
    int bVar4;
    char local_34 [20];
    char local_20 [20];
  
    p(local_34,&DAT_080486a0); // 0x080486a0 = "********* ADMIN LOGIN PROMPT *********" == " - "
    p(local_20,&DAT_080486a0); // 0x080486a0 = "********* ADMIN LOGIN PROMPT *********" == " - "
    strcpy(param_1,local_34);
    uVar2 = 0xffffffff;
    pcVar3 = param_1;
    do {
        if (uVar2 == 0) break;
        uVar2 = uVar2 - 1;
        cVar1 = *pcVar3;
        pcVar3 = pcVar3  + 1;
    }
    while (cVar1 != '\0');
    *(undefined2 *)(param_1 + (~uVar2 - 1)) = 0x20; // 0x20 = ' '
    strcat(param_1,local_20);
    return;
}

int main(void)
{
  char local_3a [54];
  
  pp(local_3a);
  puts(local_3a);
  return 0;
}