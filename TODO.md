# TODO - While(True): Colony

Cette todolist regroupe les prochaines taches par epics. L'objectif est de garder un chemin clair entre le prototype OpenGL actuel et un premier MVP jouable.

## Epic 1 - Socle technique

- [x] Creer le `Makefile` C++23.
- [x] Ouvrir une fenetre GLFW.
- [x] Initialiser OpenGL via GLAD.
- [x] Ajouter une boucle principale avec delta time.
- [x] Ajouter un logger simple.
- [x] Separer les responsabilites entre `App`, `Window`, `Renderer`, `Game`, `Input` et `Time`.
- [ ] Ajouter une gestion propre des erreurs OpenGL.
- [ ] Ajouter une cible de verification rapide dans le `Makefile`.
- [ ] Documenter les prerequis de developpement par distribution Linux.

## Epic 2 - Rendu minimal de gameplay

- [x] Afficher une premiere primitive de validation.
- [ ] Ajouter un type `Color`.
- [ ] Ajouter un type `Vec2`.
- [ ] Ajouter un type `Rect` ou `Circle` pour les primitives simples.
- [ ] Permettre au `Renderer` de dessiner plusieurs objets par frame.
- [ ] Dessiner la base.
- [ ] Dessiner un robot.
- [ ] Dessiner des ressources.
- [ ] Ajouter une camera 2D simple.
- [ ] Ajouter une conversion monde vers ecran.

## Epic 3 - Monde et simulation

- [ ] Definir un etat de monde minimal dans `Game`.
- [ ] Ajouter une base au centre du monde.
- [ ] Generer quelques ressources autour de la base.
- [ ] Ajouter une notion de quantite sur les ressources.
- [ ] Ajouter une vitesse de simulation.
- [ ] Ajouter pause / reprise.
- [ ] Ajouter un tick fixe pour la logique de jeu si necessaire.
- [ ] Preparer une generation procedurale simple par seed.

## Epic 4 - Robot MVP

- [ ] Creer une structure `Robot`.
- [ ] Stocker la position du robot.
- [ ] Ajouter une vitesse de deplacement.
- [ ] Ajouter un inventaire minimal.
- [ ] Faire se deplacer le robot vers une ressource.
- [ ] Faire recolter une ressource.
- [ ] Faire revenir le robot a la base.
- [ ] Faire deposer les ressources a la base.
- [ ] Afficher l'etat courant du robot dans les logs ou un overlay debug.

## Epic 5 - Queue de taches

- [ ] Creer une structure `Task`.
- [ ] Definir les premiers types de taches : `Harvest`, `Deposit`, `Explore`.
- [ ] Ajouter une queue de taches dans `Game`.
- [ ] Ajouter des priorites simples.
- [ ] Assigner une tache au robot disponible.
- [ ] Marquer une tache comme terminee.
- [ ] Gerer l'echec d'une tache.
- [ ] Preparer l'ajout futur du robot chef.

## Epic 6 - Input et debug

- [ ] Fermer proprement avec `Escape`.
- [ ] Ajouter pause / reprise avec une touche.
- [ ] Ajouter un raccourci pour regenerer le monde.
- [ ] Ajouter un raccourci pour ajouter une ressource de test.
- [ ] Ajouter un affichage FPS optionnel.
- [ ] Ajouter un mode debug visuel pour positions, rayons et cibles.

## Epic 7 - Documentation

- [x] Ecrire le GDD.
- [x] Documenter l'architecture initiale.
- [x] Mettre a jour le README avec l'etat reel du projet.
- [ ] Garder `architecture.md` coherent avec le code actuel.
- [ ] Documenter la boucle de gameplay MVP.
- [ ] Documenter les conventions de code.
- [ ] Ajouter une section "roadmap courte" dans le README.

## Epic 8 - Qualite et maintenance

- [ ] Activer ou documenter les sanitizers.
- [ ] Ajouter un formatage stable via `clang-format`.
- [ ] Ajouter une verification de compilation propre.
- [ ] Nettoyer les warnings restants.
- [ ] Eviter les ressources OpenGL non liberees.
- [ ] Ajouter des tests unitaires pour les fonctions de simulation pures quand elles existent.

## Epic 9 - MVP jouable

- [ ] Lancer le jeu et voir une base, un robot et des ressources.
- [ ] Voir le robot executer une boucle recolte/depot automatiquement.
- [ ] Voir les ressources de la base augmenter.
- [ ] Ajouter une premiere queue visible ou loggee.
- [ ] Ajouter plusieurs ressources avec distances differentes.
- [ ] Ajouter une priorisation simple des ressources.
- [ ] Valider une boucle idle minimale.
