Wesh

git log --> pour savoir ou on est
git pull --> recupere les infos
git push origine master --> push vers la branche main
git revert <id_commit> --> revient sur une etape precedente
---------------------------- git en groupe ----------------------------------
git branche --> liste des branches dispo
git branche <name> --> creer une nouvelle branche
git checkout <name> --> change de branche courante
!!! il faut commit avant de changer de branche !!!
git merge <nom_de_la_branche> --> pour changer les modifs : on retourne sur la branche master puis on le fait
(a faire qund le fichier est finis)
creer 2 branches, 1 pour theo une pour kyllian
les branches servent a changer le code sans affecter le main/master(test, debug, nv fonction),

!!!! pour mettre a jour le git_main !!!!
1- git add
2- git commit -m ""j
3- git checkout main
4- git pull origin main (evite les conflits)
5- git merge <nom_branche>
6- git push

!!!! pour push notre branche !!!!
1- git add
2- git commit -m ""
3- git push origin nom_de_branche

ATTENTION : 
git push origin ma_branche:main --> push forcer mais si d'autre commit sont en cour ou que quelqu'un push en meme temps c'est la merde
