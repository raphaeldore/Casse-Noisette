![Casse-Noisette Banner](https://github.com/440-H15/EQ16-TP3/blob/master/Documents/banner.png)

# Casse-Noisette

Casse-Noisette est une application qui permet le cassage de mots de passe (autrement connu sous le nom de "Password Cracking" dans le monde informatique Anglais).

Table des matières
=================

  * [Casse-Noisette](#casse-noisette)
    * [Comment compiler](#comment-compiler)
      * [OpenSSL](#openssl)
      * [QT](#qt)
    * [Comment distribuer l'application compilée](#comment-distribuer-lapplication-compil%C3%A9e)
      * [Où trouver ces fichiers .DLLs](#o%C3%B9-trouver-ces-fichiers-dlls)
    * [Méthodes de cassage](#m%C3%A9thodes-de-cassage)
      * [Attaque par force brute](#attaque-par-force-brute)
      * [Attaque par dictionnaire](#attaque-par-dictionnaire)
    * [Structure de l'application](#structure-de-lapplication)
      * [CasseNoisette](#cassenoisette)
      * [Crypto](#crypto)
      * [CrackingEngine](#crackingengine)
      * [DataLayer](#datalayer)
      * [Utilities](#utilities)
      * [UnitTests + IntegrationTests](#unittests--integrationtests)
    * [Annexes](#annexes)
      * [Ressources](#ressources)
      * [Où puis-je me procurer un dictionnaire de mots?](#o%C3%B9-puis-je-me-procurer-un-dictionnaire-de-mots)

## Comment compiler

Pour compiler, vous avez besoin de 3 choses:

* Une version récente de **Visual Studio** (de préférence 2013, mais 2012 devrait fonctionner aussi... Mais on ne garantit rien)
* **OpenSSL** : Nécessaire pour compiler le projet Crypto (On a implémenté la fonction de hachage MD5 nous-mêmes, mais pour les fonctions SHA-1, SHA-256 et SHA-512 ont a utilisé OpenSSL). De plus, OpenSSL est nécessaire pour faire des requêtes HTTPS avec QT.
* **QT 32bits 5.4.x msvc 2013** : Nécessaire pour l'interface utilisateur (GUI, ou UI).

### OpenSSL

Rendez-vous à la page [http://slproweb.com/products/Win32OpenSSL.html](http://slproweb.com/products/Win32OpenSSL.html), et téléchargez la version 32bits la plus récente de OpenSSL qu'il y a sur la page (**Pas la version light!**). Au moment de l'écriture de ces instructions, la version la plus récente était : `Win32 OpenSSL v1.0.2a`. Lancez l'installateur, et choisissez un emplacement approprié pour votre installation d'OpenSSL (Par exemple: `C:\lib\OpenSSL`). Lorsqu'on vous demandera où copier les fichiers .DLL, choisissez l'option « Copy OpenSSL Files to **The Windows system directory** » (très important).

Vous pouvez être informé lors de l'exécution de l'installateur que « Visual C ++ 2008 Redistributable » est introuvable. Dans ce cas vous devez d'abord installer le composant manquant. Suivez les instructions à l'adresse suivante [https://www.microsoft.com/en-us/download/details.aspx?id=29](https://www.microsoft.com/en-us/download/details.aspx?id=29), et puis relancez l'installateur.

![But wait, there's more!](http://i.imgur.com/CQHRVih.png)


Maintenant que OpenSSL est installé, vous avez quelques petites choses à faire pour utiliser la librairie avec Visual Studio. La première chose à faire (en supposant une installation dans le dossier `C:\lib\OpenSSL`) est d'aller dans le répertoire `C:\lib\OpenSSL\lib\VC` et de copier tous les fichiers qui s'y trouvent dans le répertoire « lib » de Visual Studio C++ (dans mon cas, le chemin était: `C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\lib`).

Ensuite, copiez tous les fichiers qui sont dans le répertoire `C:\OpenSSL\include` dans le dossier « Include » de Visual Studio (devrait être dans le même dossier où se trouve le répertoire « lib », donc `C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\include` dans le cas de Visual Studio 2013).

Voilà, vous devriez maintenant être en mesure d'utiliser la librairie OpenSSL avec notre projet!

*Truc de pro : Si jamais vous voulez utiliser OpenSSL dans un de vos projets, rendez-vous dans les `propriétés de votre projet -> Générateur de bibliothèque -> Dépendances supplémentaires` et d'ajouter dans le champ   « Dépendances supplémentaires » le fichier .lib libeay32MDd.lib pour la compilation en mode debug, ou sinon en mode release ajoutez à la place libeay32MD.lib (d'ailleurs il y a 4 versions des librairies disponibles, voici la définition des suffixes : MD pour dynamic-release, MDd pour dynamic-debug, MT pour static-release, MTd pour static-debug).*

### QT

Téléchargez la version **32bits** community de QT (version 5.4.x) **pour msvc2013** (vous pouvez vous rendre sur cette page [http://download.qt.io/archive/qt/5.4/5.4.1/qt-opensource-windows-x86-msvc2013-5.4.1.exe.mirrorlist](http://download.qt.io/archive/qt/5.4/5.4.1/qt-opensource-windows-x86-msvc2013-5.4.1.exe.mirrorlist), et appuyez sur le lien « Download file » ). Lancez l'installateur, et suivez les instructions à l'écran. Lorsqu'on vous demandera de choisir un dossier d'installation, choisissez un chemin qui n'a aucun espace et caractère spécial, tel que `C:\lib\Qt5.4.0`. 

C'est tout pour l'installation de QT, mais il reste encore quelques petits trucs à faire. Pour que QT fonctionne bien avec Visual Studio, il vous faut installer le plugin QT pour Visual Studio. Rendez-vous à la page suivante [https://www.qt.io/download-open-source/](https://www.qt.io/download-open-source/), dans le bas de la page (sous la section « Other downloads ») devrait se situer un lien pour télécharger le plugin QT pour Visual Studio. Installez le plugin, et ensuite ouvrez Visual Studio. Il devrait maintenant avoir y un nouveau menu `QT5` (haut de la fenêtre, près du menu « Affichage » ). Sélectionnez `QT5 -> QT Options`, ensuite l'onglet Qt Versions et cliquez sur le bouton « Add » pour faire afficher le dialogue « Add New QT Version ». Choisissez un nom significatif pour le nom de la version, tel que QT 5.4 32bits MSVC 2013. Rendez-vous ensuite jusqu'au chemin où vous avez installé QT. Une fois la version de QT ajoutée, toujours dans QT Options, sélectionnez comme version de QT par défaut la version que vous venez d'ajouter.

Voilà, ça devrait suffire! Tope là!

![High Five](http://www.petitpetitgamin.com/wp-content/uploads/2011/02/high-fivepicture.png)

## Comment distribuer l'application compilée

Une fois que vous avez compilé l'application, vous allez sûrement vouloir la partager, ou bien l'utiliser sur un autre ordinateur. Le problème ici est que ce nouvel ordinateur n'a probablement pas tous les .DLLs requis pour exécuter l'application. Voici donc une liste des fichier .DLLs que vous devez inclure dans le même dossier que l’exécutable de l'application CasseNoisette.exe :

	¦   CasseNoisette.exe
	¦   icudt53.dll
	¦   icuin53.dll
	¦   icuuc53.dll
	¦   libeay32.dll
	¦   libEGL.dll
	¦   libGLESv2.dll
	¦   msvcp120.dll
	¦   msvcr120.dll
	¦   Qt5Core.dll
	¦   Qt5Gui.dll
	¦   Qt5Network.dll
	¦   Qt5Widgets.dll
	¦   ssleay32.dll
	¦   vccorlib120.dll
	¦
	+---platforms
    	    qminimal.dll
        	qoffscreen.dll
        	qwindows.dll

La structure du dossier doit être exactement la même (n'oubliez surtout pas de créer le dossier platforms et d'y mettre les .DLLs requis).

### Où trouver ces fichiers .DLLs?

Les fichiers `icudt53.dll`, `icuin53.dll`, `icuuc53.dll`, `libEGL.dll`, `libGLESv2.dll`, `Qt5Core.dll`, `Qt5Gui.dll`, `Qt5Network.dll`, `Qt5Widgets.dll` : vous les trouverez dans le dossier `bin/` situé à l'endroit où vous avez installé QT (Ex: `C:\Qt\Qt5.4.0_x86\5.4\msvc2013\bin\`).

Les fichiers `qminimal.dll`, `qoffscreen.dll` et `qwindows.dll` : sont disponibles dans le dossier `plugins/platforms/` de votre installation QT (Ex: `C:\Qt\Qt5.4.0_x86\5.4\msvc2013\plugins\platforms\`).

Les fichiers `msvcp120.dll`, `msvcr120.dll` et `vccorlib120.dll` : sont fournis avec Visual Studio. Sur mon ordinateur ces .DLLs se situent dans le dossier `C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\redist\x86\Microsoft.VC120.CRT\`. Le chemin peut varier légèrement pour vous, mais ça devrait être dans ces environs.

Finalement, les fichiers `ssleay32.dll` et `libeay32.dll` : sont fournis avec OpenSSL. Si vous ne l'avez pas déjà fait, suivez les instructions pour [installer OpenSSL](#openssl). Les fichiers .DLLs se situent dans la racine de votre dossier d'installation d'OpenSSL (Par exemple, `C:\lib\OpenSSL\`).

## Méthodes de cassage

Casse-Noisette permet de casser des mots de passe de deux manières différentes.

Pour les deux méthodes de cassage, il faut fournir un fichier `.txt` contenant la liste des mots de passe hachés à casser. Le fichier doit contenir **1 seul** mot de passe haché **en hexadécimal** par ligne. Le formatage d'une ligne doit être :

`([NomUtilisateur][separateur])mot de passe haché`

Où tout ce qui est entre parenthèses est optionnel (Cependant, le séparateur est obligatoire lorsqu'un nom d'utilisateur est fournis. Voici des exemples:

Ceci est valide : `user1!!6d4db5ff0c117864a02827bad3c361b9`

Ceci n'est pas valide : `<use:r1:f71dbe52628a3f83a77ab494817525c6>`

Ceci est valide :

    bob:106a6c241b8797f52e1e77317b96a201
    06d80eb0c50b49a509b49f2424e8c805
    2a1585a864d9e67627c6ae04c807a2c5
    john:0a16bc32f55683128983f223de242942

Ceci n'est pas valide : `claude:za1585a864d9e67627c6ae04c807a2c5` car le hash contient au moins un caractère qui n'est pas en hexadécimal (le **z**). Petit rappel sur l'hexadécimal : Chiffres de 0 à 9, et lettres de A à F. Touts les autres lettres n'existent pas en hexadécimal. Ça peut sembler bizarre comme format, mais c'est la manière la plus simple de représenter un hash. Tous les algorithmes de hachage affichent le hash en hexadécimal (et Casse-Noisette n'en est pas l'exception).

### Attaque par force brute

L'attaque par force brute est typiquement la dernière méthode qu'on utilise quand on a épuisé toutes les autres méthodes, puisque c'est peu optimisé. Essentiellement, cette méthode de cassage essaye toutes les combinaisons possibles d'un groupe de caractères (ex: a, aa, ab, ac, abc..) jusqu'à ce qu'on trouve le mot de passe. Si le mot de passe est moins de 6 caractères, Casse-Noisette le trouvera en moins d'une seconde, cependant à partir de 6 caractères, le temps nécessaire pour casser un mot de passe augmente exponentiellement.

Pour casser des mots de passe par force brute avec Casse-Noisette, vous devez donc fournir un fichier de mots de passe, et choisir un charset. Qu'est-ce qu'un charset? C'est tout simplement les caractères qui seront utilisés pour faire les combinaisons pendant le cassage. Si jamais ce que le programme offre est trop limité, vous pouvez fournir votre charset personnalisé dans le textbox sous le label "Aussi inclure les caractères suivant : "

![Cassage par force brute](http://i.imgur.com/UIvDvxx.png)


### Attaque par dictionnaire

L'attaque par dictionnaire est une méthode très simple et très efficace pour casser des mots de passe. Au lieu de générer toutes les combinaisons possibles (ce qui peut être très long), on utilise une liste de mots préétablie et on cherche au travers de la liste de mots jusqu'à ce qu'on trouve un mot qui a le même hash que le (ou les) mot de passe qu'on tente de casser. C'est une méthode très efficace, puisque beaucoup d'utilisateurs sur le web utilisent des mots de passe simples, qui sont faciles à casser avec un dictionnaire (ex: 123password), mais qui prendrait des semaines (voir des années) par force brute.

Vous devez évidemment fournir un dictionnaire de mots. C'est tout simplement un fichier texte avec 1 mot par ligne. Il y a plein de dictionnaires disponibles en ligne. Plus d'informations dans l'annexe [Où puis-je me procurer un dictionnaire de mots?](#o%C3%B9-puis-je-me-procurer-un-dictionnaire-de-mots)

![Cassage par dictionnaire](http://i.imgur.com/fNfURwF.png)


## Structure de l'application

Le projet est séparé en 7 sous-projets :

### CasseNoisette

Tout le code qui gère l'interface est ici. La classe principale est la classe CasseNoisette (cassenoisette.h et cassenoisette.cpp). À partir de cette classe, toutes les autres classes du projets sont appelées.

Fonctionnalités notables de l'interface :

* Vous pouvez démarrer et annuler une séance de cassage
* Vous pouvez générer un dictionnaire de mots
* Vous pouvez générer des mots de passe aléatoires et sécuritaires
* Vous pouvez vérifier si un de vos comptes sur le web a été victime d'une fuite de données.
* et encore plus!

### Crypto

Le projet Crypto s'occupe de gérer tout ce qui touche aux fonctions de hachage. Les fonctions de hachage que nous supportons sont :

* MD5
* SHA-1
* SHA-256
* SHA-512

Chaque classe a une méthode publique, `hash` qui prend en paramètre la string que vous voulez hacher, et retourne une string représentant le mot de passe haché avec une des 4 fonctions sous forme hexadécimal.

Si vous avez une liste de mots de passe hachés avec une autre fonction de hachage, vous ne pourrez malheureusement pas utiliser notre application (pour le moment en tout cas). 

### CrackingEngine

Le projet CrackEngine regroupe les différents engins de cassage : `BruteForce` et `Dictionary`. Pour instancier un engin facilement on utilise le pattern [Factory](https://fr.wikipedia.org/wiki/Fabrique_%28patron_de_conception%29) dans notre classe `CrackFactory`.

### DataLayer

Projet qui contient 1 seul classe (pour l'instant) : FileRepository. Cette classe est utilisée pour charger à partir d'un fichier une liste des mots de passes hachés (avec la méthode `loadPasswordFile`), ou un dictionnaire de mots (avec la méthode `loadDictionaryFile`).

### Utilities

Projet assez général qui regroupe sous le namespace `Utilities` des classes pratiques qui n'ont pas vraiment leur place dans les autres projets. Pour l'instant, le projet contient 4 classes :

* PasswordGenerator : Pour générer des mots de passe aléatoires à partir d'un charset
* DictionaryGenerator : Pour générer une liste de mots
* GuessHash : Pour déterminer la fonction de hachage qui a été utilisée pour hacher un certain mot de passe.
* FileUtilities :  Petite classe avec une couple de méthodes statiques bien pratique pour faciliter les interactions avec les fichiers, dans le but ultime de réduire la répétition de code.

### UnitTests + IntegrationTests

Regroupe tous les tests unitaires et les tests d'intégrations de notre application (sauf l'interface).

## Annexes

### Ressources

* [Page Wikipedia sur l'Attaque par force brute](http://fr.wikipedia.org/wiki/Attaque_par_force_brute)
* [Page Wikipedia sur l'Attaque par dictionnaire](http://fr.wikipedia.org/wiki/Attaque_par_dictionnaire)

### Où puis-je me procurer un dictionnaire de mots?

Voici quelques bonnes ressources :

* [https://wiki.skullsecurity.org/Passwords#Password_dictionaries](https://wiki.skullsecurity.org/Passwords#Password_dictionaries)
* [http://www.openwall.com/passwords/wordlists/](http://www.openwall.com/passwords/wordlists/)
* L'ultime des dictionnaires (15 Go!) : [https://crackstation.net/buy-crackstation-wordlist-password-cracking-dictionary.htm](https://crackstation.net/buy-crackstation-wordlist-password-cracking-dictionary.htm) *


\* Cependant ne fonctionnera pas avec Casse-Noisette. Le fichier est beaucoup trop gros. 
