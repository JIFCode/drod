// $Id: ExpandingTextEffect.cpp 9773 2011-11-10 16:19:01Z mrimer $

#include "ExpandingTextEffect.h"
#include "FontManager.h"
#include "BitmapManager.h"
#include "Widget.h"

#include <BackEndLib/Assert.h>

#include <math.h>

//********************************************************************************
CExpandingTextEffect::CExpandingTextEffect(
//Constructor.
//
//
//Params:
	CWidget *pSetWidget,    //(in)   Should be a room widget.
	const WCHAR *text,      //(in)  Text to display
	UINT eFont,             //(in) text font
	const int xOffset, const int yOffset, //(in)  Offset from top-left of parent, in pixels
	const float scaleIncrease, // multiplier, how much larger to make text over original size
	const Uint32 wDuration, //(in)  How long to display (in milliseconds) [default=1000]
	const Uint32 fadeTime)  //fade out time at end of duration [default=900]
	: CEffect(pSetWidget)
	, pTextSurface(NULL)
	, eFont(eFont)
	, xOffset(xOffset)
	, yOffset(yOffset)
	, scaleIncrease(scaleIncrease)
	, wDuration(wDuration)
	, fadeTime(fadeTime)
{
	ASSERT(pSetWidget->GetType() == WT_Room);
	ASSERT(text);
	ASSERT(wDuration);

	pSetWidget->GetRect(this->screenRect);
	this->dirtyRects.push_back(this->screenRect);

	this->wstrText = text;

	RenderText();
}

//********************************************************************************
CExpandingTextEffect::~CExpandingTextEffect()
{
	SDL_FreeSurface(this->pTextSurface);
}

//********************************************************************************
//Draws an expanding fading text message at the specified offset in the parent widget.
bool CExpandingTextEffect::Draw(SDL_Surface* pDestSurface)
{
	//End after duration has elapsed.
	const Uint32 elapsed = TimeElapsed();
	if (elapsed >= this->wDuration)
		return false;

	if (!pDestSurface) pDestSurface = GetDestSurface();

	//Expand text size, starting at 75% and growing to specified scale factor.
	const float size_delta = 0.75f + ((0.25f + this->scaleIncrease) * elapsed / (float)this->wDuration);
	const UINT scaled_w = ROUND(size_delta * this->base_size.w);
	const UINT scaled_h = ROUND(size_delta * this->base_size.h);

	//Scale.
	Uint8 *pSrcPixel = (Uint8*)this->pTextSurface->pixels;
	SDL_Surface *pScaledSurface = g_pTheBM->ScaleSurface(this->pTextSurface, pSrcPixel,
			this->base_size.w, this->base_size.h,
			scaled_w, scaled_h);
	if (!pScaledSurface)
		return false;

	//Specify area of effect.
	const UINT xDraw = this->screenRect.x + this->xOffset - scaled_w/2;
	const UINT yDraw = this->screenRect.y + this->yOffset - scaled_h/2;
	SDL_Rect rect = MAKE_SDL_RECT(xDraw, yDraw, scaled_w, scaled_h);
	ASSERT(this->dirtyRects.size() == 1);
	this->dirtyRects[0] = rect;

	if (g_pTheBM->bAlpha) {
		const Uint32 time_left = this->wDuration - elapsed;
		if (time_left < this->fadeTime) {
			static const Uint8 start_opacity = 255;
			const float fFadePerMS = start_opacity / float(this->fadeTime);
			const Uint8 opacity = (Uint8)(time_left * fFadePerMS);
			EnableSurfaceBlending(pScaledSurface, opacity);
		}
	}

	SDL_BlitSurface(pScaledSurface, NULL, pDestSurface, &rect);

	SDL_FreeSurface(pScaledSurface);

	return true;
}

//********************************************************************************
//Creates a surface with the text to display, so it doesn't have to be rerendered each frame.
void CExpandingTextEffect::RenderText()
{
	ASSERT(!this->pTextSurface);

	UINT w, h;
	g_pTheFM->GetTextWidthHeight(this->eFont, this->wstrText.c_str(), w, h);
	this->dirtyRects[0].w = w;
	this->dirtyRects[0].h = h;
	this->base_size = this->dirtyRects[0];

	ASSERT(this->dirtyRects.size() == 1);
	this->pTextSurface = CBitmapManager::ConvertSurface(SDL_CreateRGBSurface(
			SDL_SWSURFACE, w, h, g_pTheBM->BITS_PER_PIXEL, 0, 0, 0, 0));
	ASSERT(this->pTextSurface);

	SDL_Color BG = g_pTheFM->GetFontBackColor(this->eFont);
	const Uint32 TransparentColor = SDL_MapRGB(this->pTextSurface->format,
		BG.r, BG.g, BG.b);
	SDL_FillRect(this->pTextSurface, NULL, TransparentColor);   //make entire bg transparent
	g_pTheFM->DrawTextXY(this->eFont, this->wstrText.c_str(), this->pTextSurface, 0, 0);
	SetColorKey(this->pTextSurface, SDL_TRUE, TransparentColor);
}
