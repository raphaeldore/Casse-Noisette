#include "stdafx.h"
#include "FakeFileRepository.h"

FakeFileRepository::FakeFileRepository() : loadPasswordFileHasBeenCalled(false), loadDictionaryFileHasBeenCalled(false)
{
}


FakeFileRepository::~FakeFileRepository()
{
}

multimap<string, string> FakeFileRepository::loadPasswordFile(const string & _pwdFilePath, const string & _separator)
{
	loadPasswordFileHasBeenCalled = true;
	multimap<string, string> fakeMultimap;
	fakeMultimap.insert(make_pair("f71dbe52628a3f83a77ab494817525c6", "fakeUser1"));

	return fakeMultimap;
}

unique_ptr<queue<string>> FakeFileRepository::loadDictionaryFile(const string & _dictFilePath)
{
	loadDictionaryFileHasBeenCalled = true;
	unique_ptr<queue<string>> fakeQueue = make_unique<queue<string>>();
	fakeQueue->push("patate");

	return move(fakeQueue);
}

bool FakeFileRepository::hasLoadPasswordFileBeenCalled()
{
	return loadPasswordFileHasBeenCalled;
}

bool FakeFileRepository::hasLoadDictionaryFileBeenCalled()
{
	return loadDictionaryFileHasBeenCalled;
}