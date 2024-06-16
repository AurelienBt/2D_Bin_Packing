import json
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from math import sqrt, ceil

with open('out/bins.json', 'r') as f:
    data = json.load(f)

# Détermine le nombre de bins
num_bins = len(data['bins'])
cols = int(ceil(sqrt(num_bins)))+1
rows = int(ceil(num_bins / cols))

figX = (4 if(rows < 3) else 2)*cols
figY = (4 if(rows < 3) else 2)*rows

fig, axes = plt.subplots(rows, cols, figsize=(figX, figY))
axes = axes.flatten()  # Pour accéder aux axes comme une liste

for i, bin in enumerate(data['bins']):
    bin_id = bin['id']
    bin_width = bin['width']
    bin_height = bin['height']
    rectangles = bin['rectangles']

    ax = axes[i]
    ax.set_xlim(0, bin_width)
    ax.set_ylim(0, bin_height)

    # Je dessine ma bin sur le graphique
    bin_rect = patches.Rectangle((0, 0), bin_width, bin_height, linewidth=1, edgecolor='black', facecolor='yellow')
    ax.add_patch(bin_rect)
    
    num_rectangles = len(rectangles)

    # Pour chacun de mes rectangles présents dans ma bin, je vais récupérer les infos qui m'intéressent (x, y, rotation, height, width)
    # Afin de pouvoir les dessiner
    for j, rect in enumerate(rectangles):
        rectId = rect['id']
        x = rect['x']
        y = rect['y']
        if rect['rotation'] == 1:  # Si rotation est à 1, il faut inverser height et width
            width = rect['height']
            height = rect['width']
        else:
            width = rect['width']
            height = rect['height']

        # # Création du patch pour le rectangle
        rectangle_patch = patches.Rectangle((x, y), width, height, linewidth=1, edgecolor='blue', facecolor='blue', alpha=0.5)
        ax.add_patch(rectangle_patch)
        
        # Ajout du numéro dans le rectangle
        ax.text(x + width / 2, y + height / 2, "ID "+str(rectId), color='black', ha='center', va='center', fontsize=12)


    ax.set_title(f'Bin {bin_id}')  # Pour que chaque figure ait en titre le numéro de la bin qu'elle concerne

# Supprime les axes inutilisés
for j in range(i + 1, len(axes)):
    fig.delaxes(axes[j])

plt.tight_layout()  # Ajuste l'espacement entre les sous-parcelles
plt.show()  # J'affiche tout