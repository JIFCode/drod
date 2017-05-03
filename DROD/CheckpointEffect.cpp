// $Id$

/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Deadly Rooms of Death.
 *
 * The Initial Developer of the Original Code is
 * Caravel Software.
 * Portions created by the Initial Developer are Copyright (C) 2002, 2005
 * Caravel Software. All Rights Reserved.
 *
 * Contributor(s): Mike Rimer (mrimer)
 *
 * ***** END LICENSE BLOCK ***** */

#include "CheckpointEffect.h"
#include "TileImageConstants.h"

//********************************************************************************
CCheckpointEffect::CCheckpointEffect(
//Constructor.
//
//Params:
	CWidget *pSetWidget,    //(in)   Should be a room widget.
	const CCoord &SetCoord)    //(in)   Location of checkpoint.
	: CAnimatedTileEffect(pSetWidget,SetCoord,2000,TI_CHECKPOINT_L,false)
{
}

//********************************************************************************
bool CCheckpointEffect::Draw(SDL_Surface* pDestSurface)
//Draw the effect.
//
//Returns:
//True if effect should continue, or false if effect is done.
{
	const Uint32 dwElapsed = TimeElapsed();
	if (dwElapsed >= this->dwDuration) return false; //Effect is done.

	if (!pDestSurface) pDestSurface = GetDestSurface();

	//Draw lit up checkpoint.
	static const Uint32 dwFullOpacityTime = 500;
	static const Uint32 dwFadeTime = this->dwDuration - dwFullOpacityTime;
	static const float fMultiplier = 255.0f / (float)dwFadeTime;
	Uint8 opacity = dwElapsed > dwFullOpacityTime ?
			static_cast<Uint8>((dwFadeTime-(dwElapsed-dwFullOpacityTime)) * fMultiplier) :
			255;
	DrawTile(this->wTileNo, pDestSurface, opacity);

	//Continue effect.
	return true;
}
