# Architecture OpenGL / GLFW en C++98

Pour une implementation OpenGL / GLFW en C++98, l'objectif est de garder une architecture simple, lisible et facile a faire evoluer. La separation importante est entre la fenetre, la boucle principale, le rendu, l'input et la logique du jeu.

## Structure recommandee

```text
include/
  App.hpp
  Window.hpp
  Renderer.hpp
  Game.hpp
  Input.hpp
  Vec2.hpp

src/
  App.cpp
  Window.cpp
  Renderer.cpp
  Game.cpp
  Input.cpp
  main.cpp
```

## Responsabilites des classes

### App

`App` gere le cycle de vie global de l'application.

- initialise GLFW
- cree `Window`, `Renderer`, `Game` et `Input`
- contient la boucle principale
- appelle `update` et `render`
- nettoie les ressources a la fin

### Window

`Window` encapsule `GLFWwindow*`.

- creation et destruction de la fenetre
- `shouldClose()`
- `swapBuffers()`
- acces controle au handle GLFW si necessaire
- callbacks de resize et d'input

### Renderer

`Renderer` est responsable uniquement du dessin OpenGL.

- setup OpenGL
- nettoyage de l'ecran
- dessin de primitives, sprites ou formes
- gestion future des shaders, textures et buffers

En C++98, il est acceptable de commencer avec OpenGL immediat pour prototyper rapidement, puis de migrer vers VBO, shaders et textures quand le rendu devient plus serieux.

### Game

`Game` contient la logique du jeu.

- etat du monde
- update avec delta time
- appels de rendu haut niveau
- pas de dependance directe a GLFW si possible

### Input

`Input` centralise l'etat clavier et souris.

- touches pressees
- position souris
- boutons souris
- callbacks GLFW qui mettent a jour un etat simple

### Vec2 / Color / Rect

Ces types peuvent rester de petites structs utilitaires.

```cpp
struct Vec2 {
    float x;
    float y;

    Vec2();
    Vec2(float x, float y);
};
```

## Flux principal

```text
main()
  -> App app;
  -> app.run();

App::run()
  -> init
  -> while window ouverte
       poll input
       game.update(dt)
       renderer.beginFrame()
       game.render(renderer)
       renderer.endFrame()
```

## Dependances recommandees

```text
App possede Window, Renderer, Game et Input

Game utilise Renderer pour dessiner
Game lit Input pour decider quoi faire
Renderer ne connait pas Game
Window ne connait pas Game
```

## A eviter au debut

- heritage profond
- singletons globaux
- templates compliques
- ownership flou avec des pointeurs partout
- callbacks GLFW qui accedent directement a toute l'application

## Point de depart conseille

Pour ce projet, commencer avec ces classes suffit :

```text
App
Window
Renderer
Game
```

`Input` peut etre ajoute ensuite, lorsque les controles deviennent plus importants.
