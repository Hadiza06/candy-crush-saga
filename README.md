# 🍬 CandyECE — Candy Crush Saga (Terminal)

Un clone en console du célèbre jeu **Candy Crush Saga**, développé en **C** dans le cadre d'un projet étudiant. Le jeu se joue entièrement dans le terminal avec une grille colorée et un système de score.

---

## 📸 Aperçu

### Menu principal
<img width="400" height="270" alt="Capture d&#39;écran 2024-12-11 182021" src="https://github.com/user-attachments/assets/2284a7a8-3177-4d34-977f-7d1918625a28" />


### Menu des niveaux
<img width="400" height="270" alt="Capture d&#39;écran 2024-12-11 182038" src="https://github.com/user-attachments/assets/d7459452-cdc6-4647-b17a-5e52d75fcf8d" />


### Grille de jeu (Niveau 3 — avec Jokers)
<img width="970" height="1119" alt="Capture d&#39;écran 2024-12-13 152318" src="https://github.com/user-attachments/assets/fe5a6543-d104-43fa-90f1-d96b7c5da0d6" />


---

## 👥 Auteurs

- Minh Tri
- Djeneba Coulibaly
- Hadiza Hamidou Ba

---

## 🎮 Fonctionnalités

- Grille de jeu **15×15** avec 5 types de bonbons
- **4 niveaux** de difficulté progressifs
- Obstacles (`X`) introduits dès le niveau 2
- **Jokers** (`J`) disponibles aux niveaux 3 et 4 (valent 10 points chacun)
- Détection et suppression des alignements **horizontaux et verticaux** (minimum 3 bonbons)
- Système de **cascade** : les bonbons tombent pour remplir les espaces vides
- **Limite de temps** de 120 secondes par partie
- Sauvegarde du score dans le fichier `scoreJoueur.txt`
- Affichage **coloré** dans le terminal (codes ANSI)

---

## 🍭 Types de bonbons

| Symbole | Couleur         | Points |
|---------|-----------------|--------|
| `C`     | Rouge           | 1      |
| `F`     | Vert            | 2      |
| `R`     | Jaune           | 3      |
| `S`     | Bleu            | 4      |
| `T`     | Violet          | 5      |
| `J`     | Cyan (Joker)    | 10     |
| `X`     | Gris (Obstacle) | —      |

---

## 📁 Structure du projet

```
candy-crush-saga/
├── main.c          # Point d'entrée — saisie du nom du joueur, lancement du menu
├── candy.c         # Logique du jeu (grille, score, cascade, affichage)
├── crush.h         # Déclarations des fonctions et constantes
├── scoreJoueur.txt # Fichier de sauvegarde des scores
└── Projetcandy.cbp # Fichier de projet Code::Blocks
```

---

## ⚙️ Prérequis

- **Compilateur C** : GCC (MinGW sur Windows)
- **IDE recommandé** : [Code::Blocks](https://www.codeblocks.org/) (le fichier `.cbp` est fourni)
- **Système d'exploitation** : Windows (le code utilise `<windows.h>`)

> ⚠️ Le projet utilise `<windows.h>` pour certaines fonctionnalités. Une adaptation serait nécessaire pour Linux/macOS.

---

## 🚀 Compilation & Lancement

### Avec Code::Blocks
1. Ouvrir `Projetcandy.cbp` dans Code::Blocks
2. Cliquer sur **Build & Run** (`F9`)

### Avec GCC en ligne de commande
```bash
gcc main.c candy.c -o candy_crush
./candy_crush
```

---

## 🕹️ Comment jouer

1. Entrez votre **nom** au démarrage.
2. Depuis le **menu principal**, choisissez :
   - `1` → Jouer
   - `2` → Règles du jeu
   - `3` → Crédits
   - `4` → Quitter
3. Sélectionnez un **niveau** (1 à 4).
4. Appuyez sur `L` pour lancer la partie.
5. Entrez une **ligne** (1–15) et une **colonne** (A–O) pour sélectionner un bonbon.
6. Si au moins 3 bonbons identiques sont alignés, ils sont supprimés et vous gagnez des points.
7. La partie se termine quand le **temps est écoulé** (120 s) ou quand vous atteignez **50 points**.
8. Tapez `0` pour quitter la partie en cours.

---

## 📊 Système de score

- Le score dépend du **type de bonbon** et du **nombre** effacé en un coup.
- Formule : `score = valeur_bonbon × nombre_bonbons_effacés`
- Les scores sont cumulés entre les parties et sauvegardés dans `scoreJoueur.txt`.

---

## 📜 Licence

Projet académique — libre d'utilisation à des fins éducatives.
