Fonctions de base.

Le pictureManager sert à récupérer les couleurs des pixels générés par la méthode de rendu et les placer sur une image. L'intérêt est nottament pour le calcul parallèle. Si on fait une procédure on
pourra l'utiliser comme callback par les threads pour récupérer les sorties. Faudra rajouter un spinlock. 
