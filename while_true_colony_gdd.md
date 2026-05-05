# Game Design Document — While(True): Colony

## 1. Pitch

Un jeu **idle / programmation / automation** dans lequel le joueur commence avec un seul robot programmable, puis construit progressivement une flotte de robots spécialisés capables d’explorer, récolter, construire, transporter et automatiser une colonie dans un monde ouvert généré procéduralement.

Le jeu s’inspire de l’esprit de **The Farmer Was Replaced**, mais s’en éloigne fortement grâce à trois choix majeurs :

1. Le monde n’est pas une grille : c’est une carte ouverte, continue, générée aléatoirement.
2. Le joueur ne gère pas seulement un robot, mais une flotte entière organisée par un robot chef.
3. Le cœur du gameplay repose sur un système de queues de tâches, de priorités, de dépendances et d’automatisation idle.

### Phrase de vente

> Programme une colonie de robots qui explore un monde inconnu, découvre des ressources, crée ses propres tâches, construit des routes, optimise sa production et continue de travailler pendant ton absence.

---

## 2. Piliers du jeu

## 2.1 Programmation progressive

Le joueur commence avec des instructions très simples, puis débloque des concepts plus avancés : conditions, boucles, fonctions, rôles, tâches, événements, queues, priorités, modules, communication entre robots, cartographie globale et IA de planification.

Le but n’est pas de forcer le joueur à écrire du code complexe dès le début, mais de lui faire ressentir une montée en puissance naturelle.

### Exemple débutant

```python
while True:
    target = scan.nearest("wood")
    move_to(target)
    harvest(target)
    move_to(base)
    deposit_all()
```

### Exemple avancé

```python
def on_discovery(resource):
    if resource.type == "iron" and resource.amount > 500:
        queue.add("build_road", target=resource.position, priority=80)
        queue.add("setup_mining_outpost", target=resource.position, priority=70)
```

---

## 2.2 Monde ouvert procédural

Contrairement à un jeu basé sur une grille, le monde est un espace continu avec des coordonnées, des distances, des obstacles, des biomes, des routes, des zones dangereuses et des ressources réparties naturellement.

Le joueur ne programme pas des déplacements case par case. Il programme des comportements : explorer, scanner, se déplacer vers une position, éviter un danger, établir une route, construire un avant-poste.

### Exemples de biomes

- Plaine : facile à traverser, ressources basiques.
- Forêt dense : beaucoup de bois, déplacement lent.
- Montagne : minerais rares, falaises, accès difficile.
- Marais : ressources spéciales, terrain lent et dangereux.
- Désert : faible eau, bonne énergie solaire, tempêtes.
- Ruines : technologie ancienne, dangers mécaniques.
- Zone toxique : ressources avancées, nécessite robots spécialisés.
- Caverne : minerais profonds, visibilité réduite.

---

## 2.3 Flotte de robots spécialisés

Le joueur commence avec un robot polyvalent, puis débloque plusieurs types de robots aux capacités différentes.

L’intérêt n’est pas seulement d’avoir de meilleures statistiques, mais de créer des stratégies différentes selon le terrain, la tâche et l’organisation de la colonie.

### Exemples de robots

| Robot | Rôle | Forces | Faiblesses |
|---|---|---|---|
| Worker | Récolte basique | Polyvalent, peu cher | Lent, limité |
| Explorer | Découverte | Scan large, rapide | Fragile, faible inventaire |
| Builder | Construction | Routes, bâtiments, réparations | Dépend des matériaux |
| Carrier | Logistique | Gros inventaire | Ne récolte pas |
| Flying Bot | Vol / reconnaissance | Ignore obstacles, va en ligne droite | Batterie faible, peu de charge |
| Multi‑Arm Bot | Actions multiples | Récolte/construit plus vite | Cher, lent |
| Miner Bot | Extraction | Très efficace sur minerais | Mauvais hors minage |
| Amphibious Bot | Eau / marais | Traverse l’eau | Lent sur terre |
| Spider Bot | Montagne / falaises | Grimpe, explore terrains difficiles | Fragile |
| Repair Bot | Maintenance | Répare routes et robots | Peu utile en production directe |
| Chief Bot | Coordination | Gère queues, priorités, assignations | Ne produit pas directement |

---

## 2.4 Le robot chef

Le robot chef est le cerveau de la colonie. Il ne fait pas forcément les tâches lui-même, mais il assigne les robots, lit l’état global, gère les priorités et choisit les meilleures actions.

Au début, le chef peut être très simple. Plus tard, le joueur peut programmer ses stratégies de décision.

### Exemple simple

```python
while True:
    task = queue.next()
    robot = chief.find_available_robot(task)

    if robot:
        chief.assign(robot, task)
```

### Exemple avancé

```python
def score(robot, task):
    value = task.priority
    value += robot.skill(task.type) * 50
    value -= distance(robot.position, task.position) * 0.2
    value -= task.danger * 20
    value -= robot.battery_penalty(task)
    return value
```

---

## 3. Boucle de gameplay principale

La boucle générale repose sur l’exploration, la découverte, la création de tâches et l’automatisation.

```text
Explorer découvre une zone
→ Événement généré
→ Tâches ajoutées à la queue
→ Chef priorise
→ Robots assignés
→ Ressources récoltées
→ Routes / bâtiments construits
→ Production améliorée
→ Nouvelles zones explorées
```

### Exemple concret

1. Un Explorer découvre un gisement de fer.
2. Le système ajoute une tâche `survey_iron_deposit`.
3. Si le gisement est rentable, le chef ajoute :
   - construire une route ;
   - livrer des matériaux ;
   - construire un avant-poste ;
   - envoyer des mineurs ;
   - assigner des transporteurs.
4. Les robots exécutent les tâches selon leurs rôles.
5. La production de fer augmente.
6. Le joueur débloque de nouvelles technologies.

---

## 4. Système de queue

Le système de queue est la colonne vertébrale du jeu.

Il permet de connecter le côté idle, la programmation, l’exploration, la construction, la logistique et la progression.

## 4.1 Principe

Une queue est une liste de tâches en attente. Ces tâches peuvent être créées manuellement par le joueur ou automatiquement par les scripts.

### Exemple

```python
queue.add(Task(
    type="build_road",
    from_pos=base.position,
    to_pos=iron_deposit.position,
    priority=80
))
```

Le chef regarde ensuite la queue et assigne les robots disponibles.

```python
for task in queue.pending():
    robot = chief.best_robot_for(task)

    if robot and task.can_start():
        chief.assign(robot, task)
```

---

## 4.2 Types de tâches

### Exploration

- Explorer une zone inconnue.
- Scanner un biome.
- Cartographier une montagne.
- Surveiller une zone dangereuse.
- Marquer une ressource pour plus tard.

### Récolte

- Récolter du bois.
- Miner de la pierre.
- Extraire du fer.
- Collecter des cristaux rares.
- Pomper de l’eau.

### Construction

- Construire une route.
- Construire un pont.
- Construire une station de recharge.
- Construire un avant-poste.
- Construire une mine automatisée.
- Construire un dépôt logistique.

### Logistique

- Transporter des matériaux.
- Réapprovisionner un chantier.
- Déplacer des ressources entre dépôts.
- Optimiser une route de livraison.

### Maintenance

- Réparer une route.
- Réparer un robot.
- Remplacer une batterie.
- Nettoyer une zone obstruée.

### Urgence

- Sauver un robot bloqué.
- Réparer une route critique.
- Éviter une tempête.
- Retirer des robots d’une zone dangereuse.

---

## 4.3 Priorités

Les tâches ne devraient pas fonctionner uniquement en FIFO. Une tâche peut avoir une priorité dynamique selon la situation.

### Facteurs possibles

- Priorité de base.
- Distance depuis la base.
- Danger de la zone.
- Valeur de la ressource.
- Urgence.
- Disponibilité des robots.
- Disponibilité des matériaux.
- Dépendances.
- Rentabilité estimée.

### Exemple

```python
def task_priority(task):
    priority = task.base_priority
    priority += task.resource_value
    priority -= task.distance_from_base * 0.1
    priority -= task.danger_level * 20

    if task.blocks_many_other_tasks:
        priority += 50

    return priority
```

---

## 4.4 Tâches bloquées

Une tâche peut être en attente parce qu’il manque une condition.

### Exemples de blocage

- Pas assez de matériaux.
- Aucun robot adapté disponible.
- Chemin non exploré.
- Zone trop dangereuse.
- Batterie insuffisante.
- Bâtiment prérequis manquant.
- Route détruite.

### Exemple UI

```text
[BLOCKED] Build road to Iron Deposit
Reason: missing stone
Needs: 240 stone
Suggested action: increase stone mining priority
```

Le joueur peut ensuite écrire des règles pour résoudre automatiquement ces blocages.

```python
if queue.blocked_by("stone"):
    queue.add("mine_stone", priority=95)
```

---

## 4.5 Dépendances de tâches

Certaines tâches peuvent dépendre d’autres tâches.

### Exemple

```text
Build Mining Outpost
Depends on:
- Survey area
- Build road
- Deliver 300 stone
- Deliver 100 metal plates
```

### Exemple code

```python
road = queue.add("build_road", target=iron_mine)
materials = queue.add("deliver_materials", target=iron_mine)

queue.add("build_outpost", target=iron_mine, depends_on=[road, materials])
```

---

## 5. Exploration et découverte

L’exploration est le moteur de la progression.

Les robots explorateurs parcourent le monde, scannent leur environnement et créent des événements lorsqu’ils trouvent quelque chose.

### Types de découvertes

- Ressource basique.
- Ressource rare.
- Nouveau biome.
- Ruines.
- Zone dangereuse.
- Passage naturel.
- Lac ou rivière.
- Caverne.
- Anomalie.
- Ancienne machine.

### Exemple d’événement

```python
on_discovery(event):
    if event.type == "resource_found":
        queue.add("survey_resource", target=event.position, priority=40)

        if event.resource == "iron":
            queue.add("build_road", target=event.position, priority=70)
```

---

## 6. Cartographie

Le monde commence inconnu. Les robots doivent le cartographier.

La carte globale peut contenir :

- Zones explorées.
- Zones inconnues.
- Ressources connues.
- Routes.
- Obstacles.
- Dangers.
- Bâtiments.
- Chemins optimisés.
- Biomes.

### Brouillard de guerre

Au début, le joueur ne voit que la base et ses alentours. Les explorateurs révèlent progressivement la carte.

```python
unknown = world.closest_unknown_area()
explorer.move_to(unknown)
explorer.scan(radius=50)
world.update_map(explorer.scan_data)
```

---

## 7. Routes et infrastructure

Les routes sont un élément central du jeu.

Elles permettent d’augmenter la vitesse des robots terrestres, de sécuriser les trajets, de réduire la consommation d’énergie et de faciliter la logistique.

### Types de routes

- Chemin de terre : peu cher, faible bonus.
- Route en pierre : durable, vitesse moyenne.
- Route métallique : rapide, coûteuse.
- Rail automatisé : très rapide pour transport lourd.
- Pont : permet de traverser l’eau.
- Tunnel : traverse les montagnes.
- Couloir sécurisé : protège des dangers.

### Construction de route

Une tâche `build_road` peut être composée de sous-tâches :

1. Analyser le chemin.
2. Nettoyer les obstacles.
3. Livrer les matériaux.
4. Construire les segments.
5. Vérifier la connexion.
6. Marquer la route comme active.

### Exemple

```python
queue.add(BuildRoad(
    start=base.position,
    end=iron_mine.position,
    material="stone",
    priority=80
))
```

---

## 8. Ressources

## 8.1 Ressources basiques

- Bois.
- Pierre.
- Fer.
- Cuivre.
- Eau.
- Énergie.

## 8.2 Ressources avancées

- Circuits.
- Batteries.
- Alliages.
- Cristaux.
- Composants optiques.
- Nanomatériaux.
- Données anciennes.

## 8.3 Utilisation des ressources

Les ressources servent à :

- Construire des bâtiments.
- Fabriquer des robots.
- Améliorer les robots.
- Construire des routes.
- Alimenter les machines.
- Débloquer la recherche.
- Réparer les infrastructures.

---

## 9. Énergie et batteries

Chaque robot peut avoir une batterie.

Cela crée des contraintes intéressantes sans rendre le jeu trop punitif.

### Mécaniques possibles

- Les robots consomment de l’énergie en se déplaçant.
- Les robots volants consomment plus.
- Les robots lourds consomment plus sur terrain difficile.
- Les stations de recharge permettent d’étendre la zone d’activité.
- Les routes réduisent la consommation.
- Certains biomes perturbent l’énergie.

### Exemple de comportement

```python
if robot.battery < 20:
    queue.add("recharge", robot=robot, priority=100)
```

---

## 10. Programmation

## 10.1 Philosophie

Le code doit être accessible au début, mais profond pour les joueurs avancés.

Le joueur peut programmer :

- Des robots individuels.
- Des rôles.
- Des comportements.
- Le chef.
- Les règles de queue.
- Les réactions aux événements.
- Les priorités globales.

---

## 10.2 Langage du jeu

Le langage peut ressembler à Python, avec une syntaxe simple.

### Fonctions de base

```python
move_to(position)
scan(radius)
harvest(target)
deposit_all()
recharge()
build(type, position)
```

### Fonctions de monde

```python
world.nearest("wood")
world.known_resources("iron")
world.closest_unknown_area()
world.mark_zone("danger", position)
```

### Fonctions de queue

```python
queue.add(task)
queue.pending()
queue.blocked()
queue.boost(type, amount)
queue.cancel(task)
```

### Fonctions du chef

```python
chief.assign(robot, task)
chief.best_robot_for(task)
chief.available_robots()
chief.create_zone(name, center, radius)
```

---

## 10.3 Rôles et comportements

Au lieu d’écrire un script unique pour chaque robot, le joueur peut définir des comportements réutilisables.

### Exemple

```python
behavior Explore:
    target = world.closest_unknown_area()
    move_to(target)
    scan(radius=50)
    report()

behavior HarvestWood:
    target = world.nearest("wood")
    move_to(target)
    harvest(target)
    move_to(base)
    deposit_all()
```

Le chef peut ensuite assigner ces comportements.

```python
if storage["wood"] < 1000:
    chief.assign_role("worker", HarvestWood)
else:
    chief.assign_role("explorer", Explore)
```

---

## 11. Idle progress

Le jeu doit fonctionner même lorsque le joueur est absent.

Quand le joueur revient, il reçoit un rapport clair.

### Exemple de rapport

```text
Pendant votre absence :
- 14 zones explorées
- 3 gisements découverts
- 1 route construite
- 4 robots fabriqués
- 2190 bois récoltés
- 870 pierre récoltée
- 6 tâches bloquées
- 2 robots endommagés
```

### Important

L’idle ne doit pas juste donner des ressources gratuitement. Il doit faire avancer le système que le joueur a programmé.

Si le système est bien conçu, la colonie progresse efficacement.

Si le système est mal conçu, des blocages apparaissent.

Cela donne au joueur des problèmes intéressants à résoudre quand il revient.

---

## 12. Interface utilisateur

## 12.1 Vue principale

La vue principale montre :

- La carte.
- Les robots en mouvement.
- Les routes.
- Les bâtiments.
- Les zones explorées.
- Les ressources connues.
- Les tâches actives.

## 12.2 Panneau de queue

```text
[HIGH] Repair main road                 running 1/1
[HIGH] Deliver stone to bridge site      running 2/3
[MED ] Build road to iron deposit        blocked: needs stone
[MED ] Harvest wood forest_alpha         running 4 robots
[LOW ] Explore western unknown zone      running 2 robots
```

Filtres possibles :

- Toutes.
- En cours.
- Bloquées.
- En attente.
- Terminées.
- Construction.
- Logistique.
- Exploration.
- Urgence.

## 12.3 Éditeur de code

L’éditeur doit être simple et rassurant.

Fonctions utiles :

- Autocomplétion.
- Documentation intégrée.
- Erreurs claires.
- Simulation rapide.
- Bouton pause.
- Historique des versions.
- Templates de scripts.
- Exemples intégrés.

## 12.4 Debugging visuel

Le joueur doit comprendre pourquoi un robot fait une action.

Exemples :

- Ligne de trajectoire.
- Tâche actuelle au-dessus du robot.
- Raison de blocage.
- Dernière décision du chef.
- Score d’assignation.
- Zone scannée.
- Chemin prévu.

---

## 13. Progression

## 13.1 Déblocages de programmation

Le joueur débloque progressivement :

1. Instructions simples.
2. Conditions.
3. Boucles.
4. Variables.
5. Fonctions.
6. Événements.
7. Queues.
8. Priorités.
9. Rôles.
10. Cartographie globale.
11. Communication robot‑robot.
12. Systèmes de dépendances.
13. Optimisation automatique.

## 13.2 Déblocages de robots

- Worker.
- Explorer.
- Builder.
- Carrier.
- Flying Bot.
- Miner Bot.
- Multi‑Arm Bot.
- Repair Bot.
- Amphibious Bot.
- Spider Bot.
- Chief Bot avancé.

## 13.3 Déblocages d’infrastructure

- Base.
- Stockage.
- Station de recharge.
- Route.
- Pont.
- Avant-poste.
- Mine automatique.
- Usine de robots.
- Relais de communication.
- Laboratoire.
- Centre logistique.

---

## 14. Recherche

La recherche peut être alimentée par des ressources, des données découvertes, ou des analyses effectuées par des robots scientifiques.

### Branches de recherche

#### Robotique

- Plus de batterie.
- Meilleurs moteurs.
- Bras supplémentaires.
- Capteurs avancés.
- Vol amélioré.

#### Infrastructure

- Routes plus rapides.
- Ponts.
- Tunnels.
- Stations de recharge.
- Rails.

#### Programmation

- Nouvelles fonctions.
- Events.
- Queues spécialisées.
- Debugging avancé.
- Profiler de performance.

#### Monde

- Cartographie avancée.
- Détection de ressources rares.
- Prévision météo.
- Analyse de danger.

---

## 15. Dangers et contraintes

Le jeu n’a pas besoin d’être un jeu de combat, mais des contraintes peuvent rendre l’automatisation intéressante.

### Exemples

- Tempêtes.
- Terrain instable.
- Zones toxiques.
- Robots qui se bloquent.
- Routes qui s’usent.
- Batteries qui se vident.
- Faune mécanique hostile.
- Ruines dangereuses.
- Brouillard magnétique qui perturbe les communications.

### Exemple de tâche d’urgence

```python
if robot.in_danger():
    queue.add("rescue_robot", target=robot.position, priority=100)
```

---

## 16. Personnalisation des robots

Le joueur peut construire des robots à partir de modules.

### Modules possibles

- Roues.
- Jambes.
- Propulseurs.
- Bras simples.
- Bras multiples.
- Foreuse.
- Grand coffre.
- Scanner.
- Batterie avancée.
- Blindage.
- Module amphibie.
- Module de communication.

### Exemple de robot custom

```text
Name: Heavy Builder
Movement: Tracks
Arms: 4
Tool: Construction Kit
Battery: Large
Storage: Medium
Role: Build roads and outposts
```

---

## 17. Économie et chaînes de production

À long terme, le jeu peut évoluer vers des chaînes de production plus complexes.

### Exemple

```text
Iron ore → Iron plates → Mechanical parts → Robot arms → Multi‑Arm Bot
Copper → Wires → Circuits → Sensors → Explorer Mk2
Crystal → Energy cells → Advanced batteries → Flying Bot Mk2
```

Le système de queue permet de gérer automatiquement les besoins.

```python
if factory.needs("circuits"):
    queue.add("produce_circuits", priority=70)

if storage["copper"] < 500:
    queue.add("mine_copper", priority=80)
```

---

## 18. MVP recommandé

Pour une première version jouable, il faut rester très simple.

## 18.1 Robots MVP

- Worker : récolte et transporte.
- Explorer : découvre la carte.
- Builder : construit des routes.
- Chief : assigne les tâches.

## 18.2 Ressources MVP

- Bois.
- Pierre.
- Fer.
- Énergie.

## 18.3 Tâches MVP

- Explore.
- Harvest.
- Deliver.
- BuildRoad.
- Recharge.

## 18.4 Systèmes MVP

- Monde ouvert procédural simple.
- Brouillard de guerre.
- Queue globale.
- Priorités simples.
- Tâches bloquées.
- Routes.
- Scripts de robot basiques.
- Script du chef basique.
- Rapport idle.

## 18.5 Boucle MVP

```text
1. Le joueur programme un Explorer.
2. L’Explorer découvre du bois, de la pierre et du fer.
3. Les découvertes ajoutent des tâches à la queue.
4. Le Worker récolte.
5. Le Builder construit une route vers le fer.
6. La route améliore la production.
7. Le joueur débloque un nouveau robot ou une nouvelle fonction.
```

---

## 19. Idées avancées

## 19.1 Blueprints

Le joueur peut sauvegarder des plans :

- Route vers ressource.
- Avant-poste minier.
- Station de recharge.
- Dépôt logistique.
- Réseau de transport.

```python
blueprint.place("mining_outpost", target=iron_deposit.position)
```

## 19.2 Système de zones

Le joueur peut créer des zones nommées.

```python
chief.create_zone("forest_alpha", center=(120, 80), radius=50)
chief.assign_zone_role("forest_alpha", "wood_harvesting")
```

## 19.3 Robots managers secondaires

Plus tard, un seul chef peut ne plus suffire. Le joueur peut créer des sous-chefs.

```text
Chief Bot
├── Exploration Manager
├── Logistics Manager
├── Construction Manager
└── Mining Manager
```

## 19.4 Communication limitée

Les robots peuvent avoir besoin de relais pour communiquer loin de la base.

Cela crée une raison de construire des tours de communication.

## 19.5 Météo

La météo peut influencer le monde :

- Pluie : ralentit les robots terrestres.
- Tempête : danger pour robots volants.
- Brouillard : réduit le scan.
- Canicule : augmente la consommation d’énergie.

## 19.6 Optimisation avancée

Le joueur peut voir des métriques :

- Ressources par minute.
- Temps moyen de trajet.
- Robots idle.
- Tâches bloquées par type.
- Routes les plus utilisées.
- Goulots d’étranglement.

---

## 20. Direction artistique

Le style peut être lisible, mignon et technique.

### Options possibles

- Low poly coloré.
- Pixel art moderne.
- 2D top-down propre.
- 3D isométrique stylisée.
- Monde calme avec petits robots animés.

L’important est de rendre l’automatisation agréable à regarder.

Le joueur doit aimer observer ses robots se déplacer, construire et résoudre des tâches.

---

## 21. Ton et ambiance

Le jeu peut avoir une ambiance :

- Calme.
- Satisfaisante.
- Curieuse.
- Technique mais accessible.
- Légèrement mystérieuse.

Le monde peut raconter une histoire par l’exploration : ruines, anciennes machines, signaux étranges, technologies perdues.

---

## 22. Objectifs long terme

Le joueur pourrait chercher à :

- Cartographier toute la planète.
- Construire une méga‑colonie automatisée.
- Réactiver une ancienne structure.
- Construire une fusée.
- Créer une IA centrale.
- Atteindre une autosuffisance totale.
- Optimiser la colonie à un niveau extrême.

---

## 23. Ce qui rend le jeu unique

Le jeu ne se limite pas à programmer un robot.

Il propose de programmer une organisation complète :

- Robots spécialisés.
- Chef programmable.
- Queues de tâches.
- Découvertes automatiques.
- Construction d’infrastructure.
- Idle progress.
- Monde ouvert procédural.
- Optimisation logistique.

Le plaisir principal vient du moment où le joueur regarde sa colonie travailler toute seule et se dit :

> “Pourquoi cette tâche est bloquée ? Comment je peux rendre mon système plus intelligent ?”

C’est cette boucle d’observation, de diagnostic, d’amélioration et d’automatisation qui doit devenir addictive.

---

## 24. Résumé final

Ce jeu est un **idle programming automation game** dans un monde ouvert procédural.

Le joueur commence avec un seul robot, puis construit une flotte spécialisée. Les explorateurs découvrent le monde, les découvertes créent des tâches, les queues organisent le travail, le chef assigne les robots, les builders construisent les routes, les workers récoltent, les carriers transportent et toute la colonie progresse même quand le joueur est absent.

Le cœur du jeu est :

```text
Explorer → Découvrir → Queue → Assigner → Construire → Produire → Optimiser
```

La grande promesse est :

> Créer un système autonome capable de comprendre le monde, de générer ses propres objectifs et de s’améliorer grâce au code du joueur.

