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
      * [QT](#qt)
    * [Comment distribuer l'application compilée](comment-distribuer-lapplication-compil%C3%A9e) 
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

* Une version récente de Visual Studio (de préférence 2013, mais 2012 devrait fonctionner aussi... Mais on ne garantit rien)
* OpenSSL : Nécessaire pour compiler le projet Crypto (On a implémenté la fonction de hachage MD5 nous-mêmes, mais pour les fonctions SHA-1, SHA-256 et SHA-512 ont a utilisé OpenSSL). De plus, OpenSSL est nécessaire pour faire des requêtes HTTPS avec QT.
* QT 32bits 5.4.x msvc 2013 : Nécessaire pour l'interface utilisateur (GUI, ou UI).

### OpenSSL

Rendez-vous à la page [http://slproweb.com/products/Win32OpenSSL.html](http://slproweb.com/products/Win32OpenSSL.html), et téléchargez la version 32bits la plus récente de OpenSSL qu'il y a sur la page (**Pas la version light!**). Au moment de l'écriture de ces instructions, la version la plus récente était : `Win32 OpenSSL v1.0.2a`. Lancez l'installateur, et choisissez un emplacement approprié pour votre installation d'OpenSSL (Par exemple: `C:\lib\OpenSSL`). Lorsqu'on vous demandera où copier les fichiers .DLL, choisissez l'option « Copy OpenSSL Files to **The Windows system directory** » (très important).

Vous pouvez être informé lors de l'exécution de l'installateur que « Visual C ++ 2008 Redistributable » est introuvable. Dans ce cas vous devez d'abord installer le composant manquant. Suivez les instructions à l'adresse suivante [https://www.microsoft.com/en-us/download/details.aspx?id=29](https://www.microsoft.com/en-us/download/details.aspx?id=29), et puis relancez l'installateur.

![But wait, there's more!](http://i.imgur.com/CQHRVih.png)


Maintenant que OpenSSL est installé, vous avez quelques petites choses à faire pour utiliser la librairie avec Visual Studio. La première chose à faire (en supposant une installation dans le dossier `C:\lib\OpenSSL`) est d'aller dans le répertoire `C:\lib\OpenSSL\lib\VC` et de copier tous les fichiers qui s'y trouvent dans le répertoire « lib » de Visual Studio C++ (dans mon cas, le chemin était: `C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\lib`).

Ensuite, copiez tous les fichiers qui sont dans le répertoire `C:\OpenSSL\include` dans le dossier « Include » de Visual Studio (devrait être dans le même dossier où se trouve le répertoire « lib », donc `C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\include` dans le cas de Visual Studio 2013).

Voilà, vous devriez maintenant être en mesure d'utiliser la librairie OpenSSL avec notre projet!

*Truc de pro : Si jamais vous voulez utiliser OpenSSL dans un de vos projets, rendez-vous dans les `propriétés de votre projet -> Générateur de bibliothèque -> Dépendances supplémentaires` et d'ajouter dans le champ   « Dépendances supplémentaires » le fichier .lib libeay32MDd.lib pour la compilation en mode debug, ou sinon en mode release ajoutez à la place libeay32MD.lib (d'ailleurs il y a 4 versions des librairies disponibles, voici la définition des suffixes : MD pour dynamic-release, MDd pour dynamic-debug, MT pour static-release, MTd pour static-debug).*

### QT

Téléchargez la version 32bits community de QT (version 5.4.x) pour msvc2013 (vous pouvez vous rendre sur cette page [http://download.qt.io/archive/qt/5.4/5.4.1/qt-opensource-windows-x86-msvc2013-5.4.1.exe.mirrorlist](http://download.qt.io/archive/qt/5.4/5.4.1/qt-opensource-windows-x86-msvc2013-5.4.1.exe.mirrorlist), et appuyez sur le lien « Download file » ). Lancez l'installateur, et suivez les instructions. Lorsqu'on vous demandera de choisir un dossier d'installation, choisissez un chemin qui n'a aucun espace et caractère spécial, tel que C:\lib\Qt5.4.0. 

C'est tout pour l'installation de QT, mais il reste encore quelques petits trucs à faire. Pour que QT fonctionne bien avec Visual Studio, il vous faut installer le plugin QT pour Visual Studio. Pour faire ça, rendez-vous à la page suivante [https://www.qt.io/download-open-source/](https://www.qt.io/download-open-source/), dans le bas de la page (sous la section « Other downloads ») devrait se situer un lien pour télécharger le plugin QT pour Visual Studio. Installez le plugin, et ensuite ouvrez Visual Studio. Il devrait maintenant avoir y un nouveau menu QT5. Sélectionner QT5 -> QT Options, l'onglet Qt Versions et cliquez sur le bouton « Add » pour faire afficher le dialogue « Add New QT Version ». Choisissez un nom significatif pour le nom de la version, tel que QT 5.4 32bits MSVC 2013. Rendez-vous ensuite jusqu'au chemin où vous avez installé QT. Une fois la version de QT ajoutée, toujours dans QT Options, sélectionnez comme version de QT par défaut la version que vous venez d'ajouter.

Voilà, ça devrait suffire!

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

Où trouver ces fichiers .DLLs?

Les fichiers icudt53.dll, icuin53.dll, icuuc53.dll, libEGL.dll, libGLESv2.dll, Qt5Core.dll, Qt5Gui.dll, Qt5Network.dll, Qt5Widgets.dll : vous les trouverez dans le dossier bin/ situé à l'endroit où vous avez installé QT.

Les fichiers qminimal.dll, qoffscreen.dll et qwindows.dll : sont disponibles dans le dossier plugins/platforms/ de votre installation QT.

Les fichiers msvcp120.dll, msvcr120.dll et vccorlib120.dll : sont fournis avec Visual Studio. Sur mon ordinateur ces .DLLs se situent dans le dossier C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\redist\x86\Microsoft.VC120.CRT. Le chemin peut varier légèrement pour vous, mais ça devrait être dans ces environs.

Finalement, les fichiers ssleay32.dll et libeay32.dll : sont fournis avec OpenSSL. Si vous ne l'avez pas déjà fait, suivez les instructions pour [installer OpenSSL](#openssl). Les fichiers .DLLs se situent dans la racine de votre dossier d'installation d'OpenSSL (Par exemple, C:\lib\OpenSSL\\).

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

Fonctions de hachage (MD5, SHA-256, SHA-512 ...)

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
