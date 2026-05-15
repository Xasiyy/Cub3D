# Cub3D — Moteur de Raycasting en C

> *"What I cannot create, I do not understand."* — Richard Feynman

Cub3D est un projet graphique réalisé dans le cadre du cursus **42**. L'objectif : recréer une vue pseudo-3D à la première personne, inspirée de *Wolfenstein 3D*, en partant d'une carte 2D décrite dans un fichier `.cub`. Aucun moteur 3D, aucune bibliothèque de rendu — uniquement des mathématiques, des vecteurs et de la logique spatiale.

---

## Aperçu

```
+--------------------------------------------------+
|  Vue FPS (raycasting)     |  Minimap 2D          |
|                           |                      |
|   ██████        ██████   |   □ □ □ □ □          |
|   ██████        ██████   |   □ P → □ □          |
|   ██████        ██████   |   □ □ □ □ □          |
|___________________________|______________________|
|  Floor ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░  |
+--------------------------------------------------+
```

---

## Concepts clés

### Qu'est-ce que le Raycasting ?

Le raycasting est un algorithme de rendu qui simule une vue 3D en projetant des **rayons** depuis la position du joueur pour chaque colonne de pixels de l'écran. Là où un rayon touche un mur, on calcule la distance et on dessine une tranche verticale de hauteur proportionnelle à cette distance.

> Plus le mur est loin → tranche petite → illusion de profondeur.

### Pourquoi c'est efficace ?

Contrairement au ray*tracing* (un rayon par pixel, très coûteux), le raycasting ne lance qu'**un rayon par colonne de l'écran** — soit `SCREEN_WIDTH` rayons par frame. C'est suffisant pour une vue 3D convaincante et assez rapide pour tourner en temps réel.

---

## Architecture du projet

```
cub3D/
├── inc/
│   └── cub3D.h                          # Structures & prototypes globaux
├── src/
│   ├── main/
│   │   ├── cb_main.c                    # Point d'entrée, boucle MLX
│   │   ├── cb_initialization.c          # Init de la structure principale
│   │   ├── cb_initialization_player.c   # Init position/direction joueur
│   │   ├── cb_free.c                    # Libération mémoire & nettoyage
│   │   ├── cb_libutils.c                # Utilitaires divers
│   │   └── cb_utils.c                   # Fonctions helpers
│   ├── parser/
│   │   ├── cb_parser.c                  # Entrée du parsing, dispatch
│   │   ├── cb_pars_sfile.c              # Lecture du fichier .cub
│   │   ├── cb_pars_map.c                # Extraction & validation de la carte
│   │   ├── cb_pars_pc_extractors.c      # Parsing textures & couleurs
│   │   └── cb_pars_pc_checkduplicate.c  # Détection des duplicats
│   ├── graphics/
│   │   ├── init_graphics.c              # Init fenêtre MLX & image buffer
│   │   ├── render_map.c                 # Rendu de la frame complète
│   │   ├── control.c                    # Gestion des inputs clavier
│   │   ├── collisions.c                 # Détection de collisions murs
│   │   ├── player.c                     # Déplacements & rotations joueur
│   │   ├── minimap.c                    # Minimap 2D (fond & cases)
│   │   ├── draw_minimap_mm.c            # Dessin du joueur sur la minimap
│   │   └── raycasting/
│   │       ├── raycasting.c             # Boucle principale par colonne
│   │       ├── intersections.c          # Algorithme DDA
│   │       ├── rendu_3D.c               # Calcul hauteur & dessin tranche
│   │       ├── draw_view.c              # Mapping texture sur la tranche
│   │       ├── init_textures.c          # Chargement des XPM
│   │       └── utils_raycasting.c       # Helpers vecteurs & angles
│   └── gc/
│       ├── gc.c                         # Garbage collector maison
│       └── gc_utils.c                   # Utilitaires du GC
├── maps/
│   ├── valid_subject.cub                # Carte de référence du sujet
│   ├── test.cub / test_big.cub          # Cartes de test
│   └── invalid_*.cub                    # Cas d'erreurs (tests de robustesse)
├── tex/
│   ├── 42_north.xpm / 42_south.xpm     # Textures thème 42
│   ├── 42_east.xpm  / 42_west.xpm
│   ├── crash_*.xpm                      # Textures thème crash
│   └── *.xpm                            # Textures portrait (easter eggs)
├── libft/                               # Bibliothèque C personnelle
├── minilibx-linux/                      # Bibliothèque graphique MLX
└── Makefile
```

---

## 🗺️ Format du fichier `.cub`

Un fichier `.cub` valide contient :

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 135,206,235

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
        111111111011000001110000000000001
        100000000011000001110111111111111
        11110111111111011100000010001
        11110111111111011101010010001
        11000000110101011100000010001
        10000000000000001100000010001
        10000000000000001101010010001
        11000001110101011111011110N0111
        11110111 1110101 101111010001
        11111111 1111111 111111111111
```

### Règles de validation

| Élément | Règle |
|---|---|
| Textures | 4 faces obligatoires : `NO`, `SO`, `WE`, `EA` |
| Couleurs | Format `R,G,B` — valeurs entre 0 et 255 |
| Carte | Entourée de `1` (murs), aucun bord ouvert |
| Caractères valides | `0` (vide), `1` (mur), `N/S/E/W` (joueur) |
| Position joueur | Une et une seule position de départ |

---

## Fonctionnement du Raycasting

### 1. Initialisation du rayon

Pour chaque colonne `x` de l'écran, on calcule un **vecteur directeur** à partir de la position et de la direction du joueur :

```c
// camera_x est dans [-1, 1] selon la position dans l'écran
double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;

// ray_dir = direction + plan_camera * camera_x
ray->dir_x = player->dir_x + player->plane_x * camera_x;
ray->dir_y = player->dir_y + player->plane_y * camera_x;
```

Le **plan de caméra** est un vecteur perpendiculaire à la direction du joueur qui détermine le champ de vision (FOV ≈ 66°).

```
      Plan de caméra
      ←──────────────→
           │  FOV
     dir ↑ │
           │
        [joueur]
```

### 2. Algorithme DDA (Digital Differential Analyzer)

Le DDA permet de trouver la première intersection du rayon avec une case de la grille, sans tester chaque pixel.

On calcule les **distances entre deux intersections de grille** selon X et Y :

```c
// Distance à parcourir pour traverser une case entière
ray->delta_dist_x = fabs(1 / ray->dir_x);
ray->delta_dist_y = fabs(1 / ray->dir_y);
```

On avance ensuite case par case dans la direction du rayon jusqu'à toucher un mur (`map[y][x] == '1'`).

```
    ┌───┬───┬───┬───┐
    │   │   │   │   │
    ├───┼───┼───┼───┤
    │   │ P →───►HIT│  ← rayon
    ├───┼───┼───┼───┤
    │   │   │   │   │
    └───┴───┴───┴───┘
         ↑ grille de la carte
```

### 3. Correction Fish-Eye

Sans correction, les rayons aux bords de l'écran paraissent plus longs → les murs semblent courbés. On corrige en calculant la **distance perpendiculaire** au plan de caméra (et non la distance euclidienne) :

```c
if (ray->side == SIDE_X)
    perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
else
    perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
```

### 4. Calcul de la hauteur du mur

```c
int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);

int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
int draw_end   =  line_height / 2 + SCREEN_HEIGHT / 2;
```

Plus `perp_wall_dist` est petit (mur proche), plus `line_height` est grand → tranche haute → mur qui semble proche.

### 5. Sélection et mapping de la texture

On détermine la face touchée (Nord/Sud/Est/Ouest) selon le côté d'intersection (`side`) et la direction du rayon :

```c
if (ray->side == SIDE_X && ray->dir_x > 0)  face = WEST;
if (ray->side == SIDE_X && ray->dir_x < 0)  face = EAST;
if (ray->side == SIDE_Y && ray->dir_y > 0)  face = NORTH;
if (ray->side == SIDE_Y && ray->dir_y < 0)  face = SOUTH;
```

La position exacte d'impact sur le mur (`wall_x`) permet de sélectionner la colonne de pixels correspondante dans la texture XPM.

---

## Contrôles

| Touche | Action |
|---|---|
| `W` | Avancer |
| `S` | Reculer |
| `A` | Déplacement latéral gauche (strafe) |
| `D` | Déplacement latéral droit (strafe) |
| `←` | Rotation gauche |
| `→` | Rotation droit |
| `ESC` | Quitter |
| Croix fenêtre | Quitter proprement |

---

## Compilation & lancement

### Prérequis

- GCC / Clang
- **MinilibX** (MLX) — fournie avec le projet
- Make

### Compilation

```bash
make
```

### Lancement

```bash
./cub3D maps/default.cub
```

### Nettoyer

```bash
make clean   # supprime les .o
make fclean  # supprime les .o et l'exécutable
make re      # recompile entièrement
```

---

## Gestion des erreurs

Le programme affiche `Error\n` suivi d'un message explicite dans les cas suivants :

- Fichier `.cub` introuvable ou non lisible
- Extension incorrecte (pas `.cub`)
- Texture manquante ou chemin invalide
- Couleur mal formatée ou valeur hors range
- Carte non fermée (bord ouvert)
- Caractère invalide dans la carte
- Aucune ou plusieurs positions de départ
- Allocation mémoire échouée

---

## Ressources & références

- [minilibx-linux](https://github.com/42Paris/minilibx-linux) — documentation MLX
- https://www.youtube.com/watch?v=gYRrGTC7GtA -- inspiration pour la mise en place des calculs du raycasting (episode 1 a 3)


---

## Auteur

Projet réalisé dans le cadre du cursus **42** — School of Computer Science.

Projet réalisé en binôme, ce qui m'a permis d'améliorer mon travail d'équipe et mon organisation.

---

*Ce projet m'a permis de comprendre concrètement comment des moteurs de jeu comme Wolfenstein 3D rendaient une vue 3D en temps réel sur du matériel des années 90 — entièrement à base de trigonométrie et d'arithmétique entière.*
