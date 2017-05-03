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
 * Contributor(s): mrimer
 *
 * ***** END LICENSE BLOCK ***** */

#include "TarStabEffect.h"
#include "TileImageConstants.h"
#include "DrodBitmapManager.h"
#include "../DRODLib/GameConstants.h"
#include <BackEndLib/Assert.h>

const UINT FLUFF_PARTICLES = 15;

//********************************************************************************
CTarStabEffect::CTarStabEffect(
//Constructor.
//
//Params:
	CWidget *pSetWidget,       //(in)   Should be a room widget.
	const CMoveCoord &MoveCoord,  //(in)   Location of debris and direction of its movement.
	const UINT wParticleMinDuration,
	const UINT baseSpeed)
	: CParticleExplosionEffect(pSetWidget, MoveCoord, 8, 8, 2, PARTICLES_PER_EXPLOSION,
			wParticleMinDuration, baseSpeed)
{
	this->bRotatingParticles = false;

	this->tileNums[0] = TI_TARBLOOD_1;
	this->tileNums[1] = TI_TARBLOOD_2;
	this->xDims[0] = this->yDims[0] = 6;
	this->xDims[1] = this->yDims[1] = 8;
	InitParticles();
}

//********************************************************************************
CMudStabEffect::CMudStabEffect(
//Constructor.
//
//Params:
	CWidget *pSetWidget,       //(in)   Should be a room widget.
	const CMoveCoord &MoveCoord,  //(in)   Location of debris and direction of its movement.
	const UINT wParticleMinDuration,
	const UINT baseSpeed)
	: CParticleExplosionEffect(pSetWidget, MoveCoord, 8, 8, 2, PARTICLES_PER_EXPLOSION,
			wParticleMinDuration, baseSpeed)
{
	this->bRotatingParticles = false;

	this->tileNums[0] = TI_MUDBLOOD_1;
	this->tileNums[1] = TI_MUDBLOOD_2;
	this->xDims[0] = this->yDims[0] = 6;
	this->xDims[1] = this->yDims[1] = 8;
	InitParticles();
}

//********************************************************************************
CGelStabEffect::CGelStabEffect(
//Constructor.
//
//Params:
	CWidget *pSetWidget,       //(in)   Should be a room widget.
	const CMoveCoord &MoveCoord,  //(in)   Location of debris and direction of its movement.
	const UINT wParticleMinDuration,
	const UINT baseSpeed)
	: CParticleExplosionEffect(pSetWidget, MoveCoord, 8, 8, 2, PARTICLES_PER_EXPLOSION,
			wParticleMinDuration, baseSpeed)
{
	this->bRotatingParticles = false;

	this->tileNums[0] = TI_GELBLOOD_1;
	this->tileNums[1] = TI_GELBLOOD_2;
	this->xDims[0] = this->yDims[0] = 6;
	this->xDims[1] = this->yDims[1] = 8;
	InitParticles();
}

//********************************************************************************
CFluffStabEffect::CFluffStabEffect(
//Constructor.
//
//Params:
	CWidget *pSetWidget,       //(in)   Should be a room widget.
	const CMoveCoord &MoveCoord,  //(in)   Location of debris and direction of its movement.
	const UINT wParticleMinDuration,
	const UINT baseSpeed)
	: CParticleExplosionEffect(pSetWidget, MoveCoord, 4, 4, 2, FLUFF_PARTICLES,
			wParticleMinDuration, baseSpeed)
{
	this->bRotatingParticles = false;

	this->tileNums[0] = TI_FLUFFBLOOD_1;
	this->tileNums[1] = TI_FLUFFBLOOD_2;
	this->xDims[0] = this->yDims[0] = 4;
	this->xDims[1] = this->yDims[1] = 3;
	InitParticles();
}

//********************************************************************************
CFluffInWallEffect::CFluffInWallEffect(
//Particles move more slowly than for the normal effect.
//
//Params:
	CWidget *pSetWidget,       //(in)   Should be a room widget.
	const CMoveCoord &MoveCoord)  //(in)   Location of debris and direction of its movement.
	: CParticleExplosionEffect(pSetWidget, MoveCoord, 4, 4, 2, FLUFF_PARTICLES, 12, 1)
{
	this->bRotatingParticles = false;

	this->tileNums[0] = TI_FLUFFBLOOD_1;
	this->tileNums[1] = TI_FLUFFBLOOD_2;
	this->xDims[0] = this->yDims[0] = 4;
	this->xDims[1] = this->yDims[1] = 3;
	InitParticles();
}

//*****************************************************************************
bool CFluffInWallEffect::HitsObstacle(const CDbRoom *pRoom, const PARTICLE &/*particle*/) const
//Nothing is an obstacle to this effect.
{
	ASSERT(pRoom);
	return false;
}
