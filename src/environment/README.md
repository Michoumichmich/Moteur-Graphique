On va essayer que cette partie du programme ne dépende pas du moteur de rendu choisi (raytracer, shaders, etc).

L'environnement contient une collection d'objets. Au moment du rendu on va déclencher la tesselation et

Il faut encore créer des structures de base genre Sphère, Cube, etc qui héritent de Object et qui ont les mêmes
fonctions.

Idéalement les objets seraient définis dans un référentiel cartésien local. Puis pour passer au global de
l'environnement on va translater l'objet et lui appliquer les rotations