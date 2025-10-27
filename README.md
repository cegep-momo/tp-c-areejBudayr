# Construire le projet
Vous pouvez utiliser un dev container de base C++ de VScode.
Le projet utilise cmake, pensez à l'inclure dans votre dev container.

Voici les lignes de commandes pour compiler le projet:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

# Répertoire data

Il contient 2 fichiers `books.txt`et `users.txt` que vous pouvez utilisez pour tester votre code.
Pour ca il suffit de les copiers dans le repertoire `build` avec l'application `bibliotheque`



Question 1 : C++ 

Une matiere qu'on a pas beaucoup aborde dans le cours cest la journalisation (logs) dactivite. Dans mon projet, j’ai ajouté une fonctionnalité qui enregistre dans un fichier " logs.txt " chaque emprunt ou retour de livre, avec le nom de l’utilisateur, le titre du livre, l’isbn et la date. J’utilise les flux de fichiers ofstream en mode ajout pour conserver tout l’historique. Le programme ajoute chaque nouvelle ligne à la suite des anciennes pour garder tout l’historique. Grâce à la bibliothèque ctime, la date et l’heure s’ajoute automatiquement. 

Question 2 : 
Pour une bibliothèque grande, j’utiliserais un système avec une base de données mysql. Ce type de base permet de gérer beaucoup de livres sans ralentir le programme. Le c++ pourrait communiquer avec un serveur créé avec node.js ou Python (flask), qui s’occuperait du stockage et des recherches de livres.Final check: Mon 27 Oct 2025 06:08:06 PM UTC
