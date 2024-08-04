#### Etape 1 : Décompilation 

Le binaire commence par afficher le pointeur de 2 variable,puis effectue une grande boucle avec différent check de string comparable a un switch case, qui se base sur l'input d'un fgets.
Il y a 4 instructions possibles : 
- ***auth*** qui alloue 4 bytes avec malloc et met à 0 la valeur de la variable globale auth. Pour finir il y a un strcpy de l'input.
- ***reset*** qui effectue un free de *auth*.
- ***service*** qui effectue un strdup de l'input.  
- ***login*** qui check si le 33e caractère de après le début de auth est différent de 0. Si tel est le cas il éxécute un /bin/sh autrement il print un message.

#### Etape 2 : Objectif

Il faut faire en sorte d'écrire 32 caractéres après auth.

#### Etape 3 : Tests 

Si l'on fait d'abord une instruction *auth* puis une instruction service on aperçoit que la mémoire se suit et que 16 bits les sépares.

```bash
level8@RainFall:~$ ./level8 
(nil), (nil) 
auth 
0x804a008, (nil) 
service
0x804a008, 0x804a018
```

#### Etape 4 : Explications

La mémoire est aligné (graçe au settings de l'OS et de compilation du binaire).
Le strdup alloue les caractères de l'input + un nombre de bytes définie par malloc afin de faciliter le remplissage et la gestion mémoire, par exemple un minimum de 16 bytes.

#### Etape 5 : Plan d'action

La mémoire étant alignée il nous suffira d'écrire 32 bytes dans celle-ci.
Il est possible de le faire en faisant 2 fois l'instruction service ou encore en ajoutant le nombre de caractères nécessaires derrieres l'instruction service.
Et pour finir de lancer l'instruction login.

# Etape 6 : Execution

```bash
level8@RainFall:~$ ./level8 
(nil), (nil) 
auth 
0x804a008, (nil) 
service
0x804a008, 0x804a018 
service
0x804a008, 0x804a028 
login
$ whoami
level9
$ cat /home/user/level9/.pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
```