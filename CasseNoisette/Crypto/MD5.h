/* MD5 : un algorithme de chiffrement par bloc

Basé sur l'implémentation de référence
RFC 1321 (https://www.ietf.org/rfc/rfc1321.txt)

@author Raphaël Doré
*/

#pragma once
#include "stdafx.h"
#define BLOCKSIZE 64

namespace CustomCrypto
{
	// Utilisation:
	//    1)
	//    2)
	//    3)
	class MD5 : public IHash
	{
	public:
		MD5();
		~MD5() override;
		string hash(const string _stringToHash) override;

	private:
		/* UINT1 définit un mot (word) d'un octet (8 bits) */
		typedef unsigned char uint1;

		/* UINT4 définit un mot (word) de 4 octets (32 bits) */
		typedef unsigned int uint4; 

		void MD5Init();

		/* ... */
		void MD5Update(const unsigned char * _input, unsigned int _length);

		/* */
		void MD5Finalization();

		string MD5HexDigest() const;

		void MD5Tansform(const uint1 block[BLOCKSIZE]);

		// Décodage de l'entrée (unsigned char) vers l'output (uint4).
		// On assume ici que 'len' est un multiple de 4
		static void Decode(uint4 _output[], const uint1 _input[], unsigned int _len);

		// Encodage de l'entrée (unint4) vers l'output (unsigned char) 
		static void Encode(uint1 _output[], const uint4 _input[], unsigned int _len);

		// Rotation de x de n bits
		static uint4 Rotate_left(uint4 x, uint4 n);

		// F, G, H, I sont les 4 fonctions de base
		// utilisées lors des transformations.
		static uint4 F(uint4 x, uint4 y, uint4 z);
		static uint4 G(uint4 x, uint4 y, uint4 z);
		static uint4 H(uint4 x, uint4 y, uint4 z);
		static uint4 I(uint4 x, uint4 y, uint4 z);

		// FF, GG, HH, II: transformations pour les rondes 1, 2, 3 et 4. 
		// Ce sont les 4 fonctions de base que l'algorithme utilise
		static void FF(uint4 & a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
		static void GG(uint4 & a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
		static void HH(uint4 & a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
		static void II(uint4 & a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);

		uint4 count[2];
		uint4 state[4];
		uint1 buffer[BLOCKSIZE]; // le tampon d'entré
		uint1 digest[16]; // Le résultat
	};
}