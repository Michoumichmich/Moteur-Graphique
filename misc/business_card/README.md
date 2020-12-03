J'ai modifié le code de Mayo avec le raytracer pour que ça tourne en parallèle sur tous les coeurs de l'ordi.

On le lance avec `make run`

J'ai aussi rajotué le paramètre `STOCH_SAMPLING` pour modifier le nombre de rayons lancés par rayon (c'est aussi utilisé pour la profondeur de champ). Il faut en mettre au moins 1. Initialement il y
en avait 64.

Bon, puis d'autres trucs aussi.

Pour installer openMPI : `sudo apt-get install libopenmpi-dev openmpi-bin libhdf5-openmpi-dev`

Sources:
https://fabiensanglard.net/rayTracing_back_of_business_card/
https://news.ycombinator.com/item?id=6425965
