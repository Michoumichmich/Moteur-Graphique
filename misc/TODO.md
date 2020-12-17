* Importer des objets .obj
* Profondeur de champ
* Optimiser les calculs avec SYCL
* Séparer les tessels en plusieurs zones pour réduire le temps de calcul
* Animations + keyframes (keyframe = position + timestamp). On lance le rendu avec FPS + Durée et il y a une interpolation
* GUI ?
* Super-sampling pour la réduire l'aliasing
* Effets volumétriques (style povray où on intègre les densités sur la longuer du rayon)
* Gestion plus intelligente des couleurs (pas de RGB donc)
* Réduire l'utilisation de la mémoire en ne précalculant pas tous les rayons
* Passer le rendu en itératif ie. pouvoir lancer plusieurs rayons pour chaque pixel, chacun légèrement décalé aléatoirement et ce jusqu'à ce que le bruit de
  l'image passe sous un seuil, par exmeple. Ou pendant une certaine durée, ou un certain nombre d'itérations. (comme les vrais raytracers).
