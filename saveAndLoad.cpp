#include "stdafx.h"
#include "saveAndLoad.h"

saveAndLoad::saveAndLoad() {}
saveAndLoad::~saveAndLoad() {}

HRESULT saveAndLoad::init()
{
	_saveInfo = new tagSaveInfo;

	return S_OK;
}

void saveAndLoad::release() {}

void saveAndLoad::update() {}

void saveAndLoad::render() {}

void saveAndLoad::save(tagSaveInfo* saveInfo)
{
	_saveInfo = saveInfo;

	HANDLE file;
	DWORD save;

	file = CreateFile("saveInfo.save", GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, _saveInfo, sizeof(tagSaveInfo), &save, NULL);

	CloseHandle(file);
}

tagSaveInfo* saveAndLoad::load()
{
	HANDLE file;
	DWORD load;

	file = CreateFile("saveInfo.save", GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, _saveInfo, sizeof(tagSaveInfo), &load, NULL);

	CloseHandle(file);

	return _saveInfo;
}