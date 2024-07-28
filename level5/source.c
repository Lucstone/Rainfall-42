/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaidu <lnaidu@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:20:49 by lnaidu            #+#    #+#             */
/*   Updated: 2024/07/28 20:22:10 by lnaidu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void main(void)

{
  n();
  return;
}

void n(void)
{
  char buffer [520];
  
  fgets(buffer,0x200,stdin);
  printf(buffer);
                    /* WARNING: Subroutine does not return */
  exit(1);
}

void o(void)
{
  system("/bin/sh");
                    /* WARNING: Subroutine does not return */
  _exit(1);
}