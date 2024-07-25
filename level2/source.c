/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaidu <lnaidu@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:18:07 by lnaidu            #+#    #+#             */
/*   Updated: 2024/07/23 21:21:58 by lnaidu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void p(void)
{
  int addr_mdfy;
  char buffer[76];
  
  fflush(stdout);
  gets(buffer);
  if ((addr_mdfy & 0xb0000000) == 0xb0000000) {
    printf("(%p)\n", &addr_mdfy);
                    /* WARNING: Subroutine does not return */
    _exit(1);
  }
  puts(buffer);
  strdup(buffer);
  return;
}

void main(void)
{
  p();
  return;
}