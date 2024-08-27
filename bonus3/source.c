/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaidu <lnaidu@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:43:51 by lnaidu            #+#    #+#             */
/*   Updated: 2024/08/27 18:51:46 by lnaidu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int ac, char **av)
{
  int uVar1;
  int iVar2;
  int *puVar3;
  int bVar4;
  char local_98 [16];
  char local_57;
  char local_56 [66];
  FILE *pass = fopen("/home/user/end/.pass","r");
  
  bVar4 = 0;
  puVar3 = local_98;
  for (iVar2 = 0x21; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + bVar4 * -2 + 1;
  }
  if ((!pass) || (ac != 2)) {
    uVar1 = 0xffffffff;
  }
  else {
    fread(local_98,1,0x42,pass);
    local_57 = 0;
    iVar2 = atoi(*(char **)(av[1] + 4));
    *(int*)((int)local_98 + iVar2) = 0;
    fread(local_56,1,0x41,pass);
    fclose(pass);
    iVar2 = strcmp((char *)local_98,*(char **)(av[1] + 4));
    if (iVar2 == 0) {
      execl("/bin/sh","sh",0);
    }
    else {
      puts(local_56);
    }
    uVar1 = 0;
  }
  return uVar1;
}
