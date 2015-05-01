/* MD5 : un algorithme de chiffrement par bloc

Basé sur l'implémentation de référence
RFC 1321 (https://tools.ietf.org/html/rfc1321)

@author Raphaël Doré
*/

#pragma once
#include "stdafx.h"
#define BLOCKSIZE 64

namespace CustomCrypto
{
	class MD5 : public IHash
	{
	public:
		MD5();
		~MD5() override;
		string hash(const string & _stringToHash) override;

	private:
		/* UINT1 définit un mot (word) d'un octet (8 bits) */
		typedef unsigned char uint1;

		/* UINT4 définit un mot (word) de 4 octets (32 bits) */
		typedef unsigned int uint4; 

		// Appellé avant MD5Transform.
		// Pour générer/réinitialiser un digest (qui va contenir le résultat du hachage).
		void MD5Init();

		/* ... */
		void MD5Update(const unsigned char * _input, const unsigned int _length);

		/* */
		void MD5Finalization();

		// Retourne la hash MD5 sous forme de string hexadecimale
		string MD5HexDigest() const;

		// C'est la viande de l'algorithme MD5.
		// Applique l'algorithme MD5 sur un bloque
		// de 16 octets (64 bits).
		void MD5Tansform(const uint1 block[BLOCKSIZE]);

		// Décodage de l'entrée (unsigned char) vers l'output (uint4).
		// On assume ici que 'len' est un multiple de 4
		static void Decode(uint4 _output[], const uint1 _input[], const unsigned int _len);

		// Encodage de l'entrée (unint4) vers l'output (unsigned char) 
		static void Encode(uint1 _output[], const uint4 _input[], const unsigned int _len);

		// Rotation de x de n bits
		static uint4 Rotate_left(const uint4 x, const uint4 n);

		// F, G, H, I sont les 4 fonctions de base
		// utilisées lors des transformations.
		static uint4 F(const uint4 x, const uint4 y, const uint4 z);
		static uint4 G(const uint4 x, const uint4 y, const uint4 z);
		static uint4 H(const uint4 x, const uint4 y, const uint4 z);
		static uint4 I(const uint4 x, const uint4 y, const uint4 z);

		// FF, GG, HH, II: transformations pour les rondes 1, 2, 3 et 4. 
		// Ce sont les 4 fonctions de base que l'algorithme utilise.
		static void FF(uint4 & a, const uint4 b, const uint4 c, const uint4 d, const uint4 x, const uint4 s, const uint4 ac);
		static void GG(uint4 & a, const uint4 b, const uint4 c, const uint4 d, const uint4 x, const uint4 s, const uint4 ac);
		static void HH(uint4 & a, const uint4 b, const uint4 c, const uint4 d, const uint4 x, const uint4 s, const uint4 ac);
		static void II(uint4 & a, const uint4 b, const uint4 c, const uint4 d, const uint4 x, const uint4 s, const uint4 ac);

		uint4 count[2];
		uint4 state[4];
		uint1 buffer[BLOCKSIZE]; // le tampon d'entré. Va contenir le morceau 
								 // de 16 octets qu'on est en train de travailler
								 // dessus à une instance dans le temps.

		uint1 digest[16]; // Le résultat
	};
}