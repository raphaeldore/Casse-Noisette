![Casse-Noisette Banner](https://github.com/440-H15/EQ16-TP3/blob/master/Documents/banner.png)

# Casse-Noisette

Casse-Noisette est une application qui permet le cassage de mots de passe (autrement connu sous le nom de "Password Cracking" dans le monde informatique). 

Casse-Noisette offre 2 manières de casser une liste de mots de passe :

* [Attaque par force brute](#attaque-par-force-brute) (brute force attack)
* [Attaque par dictionnaire](#attaque-par-dictionnaire) (dictionary attack)

Ressources :

* [Page Wikipedia sur l'Attaque par force brute](http://fr.wikipedia.org/wiki/Attaque_par_force_brute)
* [Page Wikipedia sur l'Attaque par dictionnaire](http://fr.wikipedia.org/wiki/Attaque_par_dictionnaire)

Table des matières
=================

  * [Casse-Noisette](#casse-noisette)
    * [Comment compiler](#comment-compiler)
      * [OpenSSL](#openssl) 
    * [Méthodes de cassage](#m%C3%A9thodes-de-cassage)
      * [Attaque par force brute](#attaque-par-force-brute)
      * [Attaque par dictionnaire](#attaque-par-dictionnaire)
    * [Structure de l'application](#structure-de-lapplication)
      * [Interface](#interface)
      * [Crypto](#crypto)
      * [CrackingEngine](#crackingengine)
      * [UnitTests + IntegrationTests](#unittests--integrationtests)
    * [Annexes](#annexes)
      * [Où puis-je me procurer un dictionnaire de mots?](#o%C3%B9-puis-je-me-procurer-un-dictionnaire-de-mots)

## Comment compiler

Pour compiler, vous avez besoin de 3 choses:

* Une version récente de Visual Studio (de préférence 2013, mais 2012 devrait fonctionner aussi)
* OpenSSL : Nécessaire pour faire des requêtes https
* QT : Nécessaire pour l'interface

### OpenSSL

Rendez-vous à la page [http://slproweb.com/products/Win32OpenSSL.html](http://slproweb.com/products/Win32OpenSSL.html), et téléchargez la version 32bits la plus récente de OpenSSL qu'il y a sur la page (Pas la version light). Au moment de l'écriture de ces instructions, la version la plus récente est : Win32 OpenSSL v1.0.2a. Lancez l'installateur, et choisissez un emplacement approprié pour votre installation d'OpenSSL (Par exemple: C:\lib\OpenSSL). Lorsqu'on vous demandera où copier les fichiers .DLL, choisissez l'option «Copy OpenSSL Files to **The Windows system directory**».

Vous pouvez être informé lors de l'exécution de l'installateur que «Visual C ++ 2008 Redistributable» est introuvable. Dans ce cas vous devez d'abords installer le composant manquant. Suivez les instructions à l'adresse suivante [https://www.microsoft.com/en-us/download/details.aspx?id=29](https://www.microsoft.com/en-us/download/details.aspx?id=29), et puis relancez l'installateur.

C'est tout!

## Méthodes de cassage

Casse-Noisette permet de casser des mots de passe de deux manières différentes.

### Attaque par force brute

TODO : Explication attaque par force brute

### Attaque par dictionnaire

TODO : Explication attaque par dictionnaire

## Structure de l'application

Le projet est séparé en 4 modules :

### Interface

TODO : Description de l'interface

### Crypto

Fonctions de hachage (MD5, SHA-256, SHA-512, ...)

TODO : Description Crypto

### CrackingEngine

TODO : Description CrackingEngine

### UnitTests + IntegrationTests

TODO : Description UnitTests + IntegrationTests 

## Annexes

### Où puis-je me procurer un dictionnaire de mots?

Voici quelques bonnes ressources :

* [https://wiki.skullsecurity.org/Passwords#Password_dictionaries](https://wiki.skullsecurity.org/Passwords#Password_dictionaries)
* [http://www.openwall.com/passwords/wordlists/](http://www.openwall.com/passwords/wordlists/)
* L'ultime des dictionnaires (15 Go!) : [https://crackstation.net/buy-crackstation-wordlist-password-cracking-dictionary.htm](https://crackstation.net/buy-crackstation-wordlist-password-cracking-dictionary.htm)
