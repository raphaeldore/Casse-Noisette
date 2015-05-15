#pragma once

using namespace std;

namespace CrackEngine
{
	enum PARAM_TYPE
	{
		PWD_FILE_PATH,
		MAX_PWD_LENGTH,
		CHARSET,
		SEPERATOR,
		HASH_TYPE,
		DICTIONARY_PATH,
		RAINBOW_TABLE_PATH
	};

	class Parameter
	{
		friend class CrackFactoryParams;
	public:
		Parameter(const PARAM_TYPE& _paramType, const string& _value);
		~Parameter();

		// Pour rendre la classe capatible avec le conteneur 'set'
		bool operator<(const Parameter& rhs) const;

	private:
		PARAM_TYPE paramType;
		string value;
	};
}