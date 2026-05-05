# While(True): Colony

Prototype de jeu d'automation / idle / programmation en **C++23** avec **OpenGL** et **GLFW**.

Le projet part du document de design [`while_true_colony_gdd.md`](/home/skydogzz/moneymaking/whileTrueColony/while_true_colony_gdd.md) et vise un **MVP** technique simple avant d'attaquer les systèmes de gameplay plus avancés.

## Vision

Dans *While(True): Colony*, le joueur programme une colonie de robots capables d'explorer, récolter, construire et automatiser un monde procédural ouvert.

Pour le MVP, l'objectif est de poser une base de travail claire :

- un socle **C++23**
- une fenêtre via **GLFW**
- un rendu via **OpenGL**
- une structure de build simple avec `make`

## Structure

```text
.
├── Makefile
├── README.md
├── src/
│   └── main.cpp
└── while_true_colony_gdd.md
```

## Prérequis

Sous Linux, il faut au minimum :

- un compilateur compatible **C++23** (`g++` ou `clang++`)
- `make`
- `pkg-config`
- `glfw3`
- les bibliothèques OpenGL du système

Exemple Debian/Ubuntu :

```bash
sudo apt install build-essential pkg-config libglfw3-dev libgl1-mesa-dev
```

## Build

Compiler le projet :

```bash
make
```

Lancer l'exécutable :

```bash
make run
```

Nettoyer les fichiers générés :

```bash
make clean
```

## État actuel

Le dépôt contient pour l'instant une base minimale :

- un `Makefile` orienté **C++23**
- un point d'entrée `src/main.cpp`
- un premier exécutable de validation

## Suite proposée pour le MVP

Les prochaines étapes logiques :

1. ouvrir une fenêtre GLFW
2. initialiser un contexte OpenGL
3. afficher une couleur de fond puis une boucle de rendu
4. introduire une boucle de jeu minimale
5. ajouter les premiers systèmes de monde / robots
