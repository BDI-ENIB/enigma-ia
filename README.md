# enigma-ia

Une librairie réutilisable d'IA, conçue pour tourner sur Arduino, Teensy ou Raspberry.

## __Contenu de la lib__:
### __protocol.hpp__
#### Présentation:
C'est une classe 'abstraite' qui est sensée servir de template aux protocoles de votre robot. Ce protocole sera communiqué à l'IA qui se chargera de l'executer
#### Fonctions membres abstraites:
**void update(IA *ia)** : Est exécutée tant que le protocole est en cours d'execution, et que les actionneurs ont terminés leurs actions.<br>
**bool isCompleted()** : Doit indiquer quand le protocole est terminé<br>
**unsigned short int getPriority(IA *ia)** : Doit indiquer le niveau de priorité du protocole. Cette priorité doit varier au fur et à mesure des actions de l'IA (par exemple priorité nulle d'un protocole *ChargerPince* quand il y a déja un cube de chargé)
### __ia.hpp__
#### Présentation:
#### Fonctions membres:
