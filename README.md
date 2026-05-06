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
├── architecture.md
├── assets/
├── include/
│   ├── App.hpp
│   ├── Game.hpp
│   ├── Input.hpp
│   ├── Logger.hpp
│   ├── Renderer.hpp
│   ├── Time.hpp
│   └── Window.hpp
├── src/
│   ├── App.cpp
│   ├── Game.cpp
│   ├── Input.cpp
│   ├── Logger.cpp
│   ├── Renderer.cpp
│   ├── Time.cpp
│   ├── Window.cpp
│   └── main.cpp
├── third_party/
│   └── glad/
└── while_true_colony_gdd.md
```

## Architecture actuelle

Le projet est decoupe en petites classes :

- `App` gere l'initialisation, le cycle de vie global et la boucle principale.
- `Window` encapsule la fenetre GLFW et le contexte OpenGL.
- `Renderer` initialise OpenGL, GLAD, les shaders et dessine la scene.
- `Game` contient l'etat et la logique de simulation.
- `Input` centralise le polling des evenements GLFW.
- `Time` calcule le delta time entre les frames.
- `Logger` fournit une sortie de logs simple.

Le flux principal est :

```text
main()
  -> App app
  -> app.run()
     -> init GLFW / window / renderer / game / input / time
     -> boucle principale
        -> update time
        -> poll input
        -> game.update(dt)
        -> renderer.beginFrame()
        -> renderer.render(game)
        -> window.swapBuffers()
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

Recompiler depuis zero :

```bash
make re
```

Formater les sources :

```bash
make format
```

## État actuel

Le depot contient maintenant un socle technique fonctionnel :

- build **C++23** avec `make`
- fenetre **GLFW**
- chargement OpenGL via **GLAD**
- boucle principale avec delta time
- logs configurables
- rendu OpenGL moderne minimal avec VAO/VBO/EBO et shaders
- affichage d'un premier carre de validation

## Suite proposée pour le MVP

Les prochaines etapes logiques sont maintenant cote gameplay :

1. ajouter des types de base (`Vec2`, `Robot`, `Resource`, `Base`)
2. stocker un premier etat de monde dans `Game`
3. faire bouger un robot entre une ressource et la base
4. etendre `Renderer` pour dessiner plusieurs objets simples
5. ajouter un controle clavier minimal pour quitter, mettre en pause ou changer la vitesse
6. introduire une premiere queue de taches simple
