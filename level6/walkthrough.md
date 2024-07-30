#### Etape 1 : Décompilation / Compréhension

Le binaire posséde une callback, qu'il appelle après un strcpy.
Il y a aussi une fonction *n* qui n'est pas appelé mais qui éxécute un cat du .pass du level suivant.

#### Etape 2 : Vulnérabilité

Le strcpy n'étant pas limité par un nombre de caractéré écris, il est sujet au buffer overflow.
Nous pouvons donc réécrire les adresses qui suivent le buffer.

#### Etape 3 : Objectif

Réecrire l'adresse du pointeur de fonction éxécuté après le strcpy.

#### Etape 4 : Informations manquantes

Il me manque l'offset pour déterminé a combien de caractère ce trouvera la nouvelle adresse a écrire
J'ai généré un buffer grâce à : https://wiremask.eu/tools/buffer-overflow-pattern-generator
En éxécutant le programme depuis gdb avec le buffer en question j'obtiens une adresse qui correspond au dernier caractère écrit avant le SegFault. Ce qui me permet de les identifier et obtenir la valeur de 72.

#### Etape 5 : Execution

Il ne reste plus qu'a éxecuter le programme avec un buffer de 72 caractère + l'adresse de la fonction n.
```bash
./level6 $(python -c 'print "A" * 72 + "\x54\x84\x04\x08"')
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```