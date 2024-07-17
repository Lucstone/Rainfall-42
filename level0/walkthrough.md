Etape 1 : Lorsque nous nous sommes connecter au programme, nous avons vu que nous avions un binaire 'level0' 

Etape 2 : Nous avons donc commencé par lancer le binaire pour voir ce qu'il faisait. Nous avons eu les resultats suivants : 
```bash
level0@RainFall:~$ ./level0
Segmentation fault (core dumped)
level0@RainFall:~$ ./level0 asddasds
No !
level0@RainFall:~$ ./level0 asddas asdasd
No !
level0@RainFall:~$ ./level0 1234
No !
```

Etape 3 : Nous avons donc ouvert le decompileur ghidra et décompiler le binaire. Nous avons vu que le binaire prenait un argument et le comparait a une chaine de caractere. Si le resultat de la comparaison etait faux, le programme affichait 'No !' et s'arretait et si la combinaison etais 423, le programme lancerais un shell en /bin/sh.

Etape 4 : Nous avons donc lancer le programme avec l'argument 423 et nous avons eu un shell. Nous avons ensuite tenter ls mais nous n'avions pas les droits pour executer la commande. Nous avons donc lancer la commande whoami pour voir quel utilisateur nous etions et nous avons vu que nous etions l'utilisateur level1.

```bash
level0@RainFall:~$ ./level0 423
$ ls
ls: cannot open directory .: Permission denied
$ whoami
level1
```
Etape 5 : Nous avons donc lancer la commande suivante pour obtenir le flag : 
```bash
$ cat /home/user/level1/.pass
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
```
Etape 6 : Nous avons donc reussi a obtenir le pass de l'utilisateur level1. 
