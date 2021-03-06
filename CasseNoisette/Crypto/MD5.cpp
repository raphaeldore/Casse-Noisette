#include "stdafx.h"
#include "MD5.h"

// Nombre de bits dans un int
#define INT_BITS 32


using namespace CustomCrypto;
using namespace std;

namespace
{
	/* Constantes utilisées par la méthode MD5Transform */
	const unsigned int S11 = 7;
	const unsigned int S12 = 12;
	const unsigned int S13 = 17;
	const unsigned int S14 = 22;
	const unsigned int S21 = 5;
	const unsigned int S22 = 9;
	const unsigned int S23 = 14;
	const unsigned int S24 = 20;
	const unsigned int S31 = 4;
	const unsigned int S32 = 11;
	const unsigned int S33 = 16;
	const unsigned int S34 = 23;
	const unsigned int S41 = 6;
	const unsigned int S42 = 10;
	const unsigned int S43 = 15;
	const unsigned int S44 = 21;

	unsigned char padding[64] = {
		0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

};

MD5::MD5()
{
	MD5Init();
}

MD5::~MD5()
{
}

string MD5::hash(const string & _stringToHash)
{
	MD5Init();
	MD5Update(reinterpret_cast<const unsigned char *>(_stringToHash.c_str()), _stringToHash.length());
	MD5Finalization();

	return MD5HexDigest();
}

void MD5::MD5Init()
{
	/* Chargement/Réinitialisation des constantes aléatoires utilisées par
	l'algorithme (tel que spécifié dans l'implémentation).
	*/

	state[0] = 0x67452301;
	state[1] = 0xefcdab89;
	state[2] = 0x98badcfe;
	state[3] = 0x10325476;

	count[0] = 0;
	count[1] = 0;
}

void MD5::MD5Update(const unsigned char* _input, const unsigned int _length)
{
	// Découpage de _input en blocs de 512 bits.
	// ... chaque bloc est ensuite divisé en 16 mots de 32 bits (avec MD5Transform).

	// Calcul du nombre d'octets modulo 64
	unsigned int index = count[0] / 8 % BLOCKSIZE;

	// Mise à jour du nombre d'octets
	if ((count[0] += (_length << 3)) < (_length << 3))
	{
		count[1]++;
	}

	count[1] += (_length >> 29);

	// Nombre d'octets qu'on doit mettre dans le tampon
	unsigned int partLength = BLOCKSIZE - index;

	unsigned int i;

	// On transforme autant fois qu'on le peut chaque block d'octets
	if (_length >= partLength)
	{
		// On remplis le tampon, ensuite on le transforme.
		memcpy(&buffer[index], _input, partLength);
		MD5Tansform(buffer);

		// On transforme chaque morceaux du block (64 octets)
		for (i = partLength; i + BLOCKSIZE <= _length; i += BLOCKSIZE)
		{
			MD5Tansform(&_input[i]);
		}

		index = 0;
	}
	else
	{
		i = 0;
	}

	// On met dans le tampon ce qui reste
	memcpy(&buffer[index], &_input[i], _length - i);
}

void MD5::MD5Finalization()
{
	unsigned char bits[8];
	unsigned int index, paddingLenght;

	// Sauvegarde du nombre d'octets
	Encode(bits, count, 8);

	// On ajoute du padding jusqu'à 56 mod 64
	index = count[0] / 8 % 64;
	paddingLenght = (index < 56) ? (56 - index) : (120 - index);
	MD5Update(padding, paddingLenght);

	// Ajout de la longeur (avant le padding) 
	MD5Update(bits, 8);


	// Stocker le state (état) dans le digest
	Encode(digest, state, 16);

	// Normalement on viderait les buffers afin d'être sécuritaire...Mais dans notre cas
	// la sécurité est +/- importante. memset ajoute un 5 milisecondes de délais par hash
	
	//// On reset les arrays (on les vide)
	//memset(buffer, 0, sizeof buffer);
	//memset(count, 0, sizeof count);
}

string MD5::MD5HexDigest() const
{
	// Tableau qui va contenir les caractères du hash
	char charBuffer[33];

	// On convertit les charactères en hexadecimal 
	for (unsigned int i = 0; i < 16; i++)
	{
		sprintf(charBuffer + i * 2, "%02x", digest[i]);
	}

	charBuffer[32] = 0;

	return string(charBuffer);
}

void MD5::MD5Tansform(const uint1 block[BLOCKSIZE])
{
	uint4 a = state[0], b = state[1], c = state[2], d = state[3], words[16];

	Decode(words, block, BLOCKSIZE);

	/* 1ère ronde */
	FF(a, b, c, d, words[ 0], S11, 0xd76aa478); /* 1 */
	FF(d, a, b, c, words[ 1], S12, 0xe8c7b756); /* 2 */
	FF(c, d, a, b, words[ 2], S13, 0x242070db); /* 3 */
	FF(b, c, d, a, words[ 3], S14, 0xc1bdceee); /* 4 */
	FF(a, b, c, d, words[ 4], S11, 0xf57c0faf); /* 5 */
	FF(d, a, b, c, words[ 5], S12, 0x4787c62a); /* 6 */
	FF(c, d, a, b, words[ 6], S13, 0xa8304613); /* 7 */
	FF(b, c, d, a, words[ 7], S14, 0xfd469501); /* 8 */
	FF(a, b, c, d, words[ 8], S11, 0x698098d8); /* 9 */
	FF(d, a, b, c, words[ 9], S12, 0x8b44f7af); /* 10 */
	FF(c, d, a, b, words[10], S13, 0xffff5bb1); /* 11 */
	FF(b, c, d, a, words[11], S14, 0x895cd7be); /* 12 */
	FF(a, b, c, d, words[12], S11, 0x6b901122); /* 13 */
	FF(d, a, b, c, words[13], S12, 0xfd987193); /* 14 */
	FF(c, d, a, b, words[14], S13, 0xa679438e); /* 15 */
	FF(b, c, d, a, words[15], S14, 0x49b40821); /* 16 */

	/* 2ème Ronde */
	GG(a, b, c, d, words[ 1], S21, 0xf61e2562); /* 17 */
	GG(d, a, b, c, words[ 6], S22, 0xc040b340); /* 18 */
	GG(c, d, a, b, words[11], S23, 0x265e5a51); /* 19 */
	GG(b, c, d, a, words[ 0], S24, 0xe9b6c7aa); /* 20 */
	GG(a, b, c, d, words[ 5], S21, 0xd62f105d); /* 21 */
	GG(d, a, b, c, words[10], S22,  0x2441453); /* 22 */
	GG(c, d, a, b, words[15], S23, 0xd8a1e681); /* 23 */
	GG(b, c, d, a, words[ 4], S24, 0xe7d3fbc8); /* 24 */
	GG(a, b, c, d, words[ 9], S21, 0x21e1cde6); /* 25 */
	GG(d, a, b, c, words[14], S22, 0xc33707d6); /* 26 */
	GG(c, d, a, b, words[ 3], S23, 0xf4d50d87); /* 27 */
	GG(b, c, d, a, words[ 8], S24, 0x455a14ed); /* 28 */
	GG(a, b, c, d, words[13], S21, 0xa9e3e905); /* 29 */
	GG(d, a, b, c, words[ 2], S22, 0xfcefa3f8); /* 30 */
	GG(c, d, a, b, words[ 7], S23, 0x676f02d9); /* 31 */
	GG(b, c, d, a, words[12], S24, 0x8d2a4c8a); /* 32 */

	/* 3ème Ronde */
	HH(a, b, c, d, words[ 5], S31, 0xfffa3942); /* 33 */
	HH(d, a, b, c, words[ 8], S32, 0x8771f681); /* 34 */
	HH(c, d, a, b, words[11], S33, 0x6d9d6122); /* 35 */
	HH(b, c, d, a, words[14], S34, 0xfde5380c); /* 36 */
	HH(a, b, c, d, words[ 1], S31, 0xa4beea44); /* 37 */
	HH(d, a, b, c, words[ 4], S32, 0x4bdecfa9); /* 38 */
	HH(c, d, a, b, words[ 7], S33, 0xf6bb4b60); /* 39 */
	HH(b, c, d, a, words[10], S34, 0xbebfbc70); /* 40 */
	HH(a, b, c, d, words[13], S31, 0x289b7ec6); /* 41 */
	HH(d, a, b, c, words[ 0], S32, 0xeaa127fa); /* 42 */
	HH(c, d, a, b, words[ 3], S33, 0xd4ef3085); /* 43 */
	HH(b, c, d, a, words[ 6], S34,  0x4881d05); /* 44 */
	HH(a, b, c, d, words[ 9], S31, 0xd9d4d039); /* 45 */
	HH(d, a, b, c, words[12], S32, 0xe6db99e5); /* 46 */
	HH(c, d, a, b, words[15], S33, 0x1fa27cf8); /* 47 */
	HH(b, c, d, a, words[ 2], S34, 0xc4ac5665); /* 48 */

	/* 4ème et dernière ronde */
	II(a, b, c, d, words[ 0], S41, 0xf4292244); /* 49 */
	II(d, a, b, c, words[ 7], S42, 0x432aff97); /* 50 */
	II(c, d, a, b, words[14], S43, 0xab9423a7); /* 51 */
	II(b, c, d, a, words[ 5], S44, 0xfc93a039); /* 52 */
	II(a, b, c, d, words[12], S41, 0x655b59c3); /* 53 */
	II(d, a, b, c, words[ 3], S42, 0x8f0ccc92); /* 54 */
	II(c, d, a, b, words[10], S43, 0xffeff47d); /* 55 */
	II(b, c, d, a, words[ 1], S44, 0x85845dd1); /* 56 */
	II(a, b, c, d, words[ 8], S41, 0x6fa87e4f); /* 57 */
	II(d, a, b, c, words[15], S42, 0xfe2ce6e0); /* 58 */
	II(c, d, a, b, words[ 6], S43, 0xa3014314); /* 59 */
	II(b, c, d, a, words[13], S44, 0x4e0811a1); /* 60 */
	II(a, b, c, d, words[ 4], S41, 0xf7537e82); /* 61 */
	II(d, a, b, c, words[11], S42, 0xbd3af235); /* 62 */
	II(c, d, a, b, words[ 2], S43, 0x2ad7d2bb); /* 63 */
	II(b, c, d, a, words[ 9], S44, 0xeb86d391); /* 64 */

	// Mise à jour du hash
	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;
}

void MD5::Decode(uint4 output[], const uint1 _input[], const unsigned int _len)
{
	unsigned int i, j;

	for (i = 0 , j = 0; j < _len; i++ , j += 4)
		output[i] = uint4(_input[j]) | (uint4(_input[j + 1]) << 8) |
			(uint4(_input[j + 2]) << 16) | (uint4(_input[j + 3]) << 24);
}

void MD5::Encode(uint1 _output[], const uint4 _input[], const unsigned int _len)
{
	/*
	On convertit 1 octet en 4 octets. Pour faire ça on fait "& 0xff". Qu'est-ce
	ça veut dire?

	0xFF c'est 255 en hexadecimal.
	En binaire c'est 00000000000000000000000011111111 (32 Bits)

	Un unsigned char c'est 8 bits. Par exemple, 'a' = 01100001.
	Pour que a soit en 32 bits, on fait: int a1 = a & 0xff

	maintenant, a1 = 00000000000000000000000001100001

	Le ET (AND) logic (&) met 1 si 2 bits sont parreil,
	et met 0 si 2 bits sont différents.

	En faisant int a1 = a & 0xff, les 8 bits de 'a' sont
	comparés aux 8 premiers bits de 0xFF. Puisque les 8 derniers
	bits de 0xff sont tous des 1, "a & 0xFF" va retourner la valeur
	de a, mais en 32 bits.

	00000000000000000000000011111111 AND
	                        01100001
	--------------------------------
	00000000000000000000000001100001

	*/

	unsigned i, j;

	for (i = 0 , j = 0; j < _len; i++ , j += 4)
	{
		_output[j] = _input[i] & 0xff;
		_output[j + 1] = (_input[i] >> 8) & 0xff;
		_output[j + 2] = (_input[i] >> 16) & 0xff;
		_output[j + 3] = (_input[i] >> 24) & 0xff;
	}
}

MD5::uint4 MD5::Rotate_left(const uint4 x, const uint4 n)
{
	// Les n derniers bits sont mis à l'avant
	// ex: Si x = 00001101
	//     Rotate_left(x, 3) donnerait: 10100001;

	return (x << n) | (x >> (INT_BITS - n));
}

MD5::uint4 MD5::F(const uint4 x, const uint4 y, const uint4 z)
{
	return (x & y) | ((~x) & z);
}

MD5::uint4 MD5::G(const uint4 x, const uint4 y, const uint4 z)
{
	return (x & z) | (y & (~z));
}

MD5::uint4 MD5::H(uint4 const x, const uint4 y, const uint4 z)
{
	return (x ^ y ^ z);
}

MD5::uint4 MD5::I(const uint4 x, const uint4 y, const uint4 z)
{
	return (y ^ (x | (~z)));
}

void MD5::FF(uint4& a, const uint4 b, const uint4 c, const uint4 d, const uint4 x, const uint4 s, const uint4 ac)
{
	a += F(b, c, d) + x + ac;
	a = Rotate_left(a, s);
	a += b;
}

void MD5::GG(uint4& a, const uint4 b, const uint4 c, const uint4 d, const uint4 x, const uint4 s, const uint4 ac)
{
	a += G(b, c, d) + x + ac;
	a = Rotate_left(a, s);
	a += b;
}

void MD5::HH(uint4& a, const uint4 b, const uint4 c, const uint4 d, const uint4 x, const uint4 s, const uint4 ac)
{
	a += H(b, c, d) + x + ac;
	a = Rotate_left(a, s);
	a += b;
}

void MD5::II(uint4& a, const uint4 b, const uint4 c, const uint4 d, const uint4 x, const uint4 s, const uint4 ac)
{
	a += I(b, c, d) + x + ac;
	a = Rotate_left(a, s);
	a += b;
}