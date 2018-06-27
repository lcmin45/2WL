#include "stdafx.h"
#include "scenePart.h"

scenePart::scenePart() {}
scenePart::~scenePart() {}

HRESULT scenePart::init()
{
	SCENEMANAGER->addScene("intro", new intro);
	SCENEMANAGER->addScene("loading", new loading);
	SCENEMANAGER->addScene("ending", new ending);

	SCENEMANAGER->changeScene("intro");

	return S_OK;
}

void scenePart::release() {}

void scenePart::update()
{

}

void scenePart::render()
{

}