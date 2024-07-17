/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnaidu <lnaidu@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:21:56 by lnaidu            #+#    #+#             */
/*   Updated: 2024/07/17 21:27:11 by lnaidu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#define _GNU_SOURCE


int main(int ac,char **av)
{
  int str423;
  char *execshell[2];
  uid_t uid;
  gid_t gid;
  
  str423 = atoi(av[1]);
  if (str423 == 423) {
    execshell[0] = strdup("/bin/sh");
    execshell[1] = NULL;
    
    gid = getegid();
    uid = geteuid();
    setresgid(gid,gid,gid);
    setresuid(uid,uid,uid);
    execv("/bin/sh",execshell);
  }
  else {
    fwrite("No !\n",1,5, stderr);
  }
  return 0;
}