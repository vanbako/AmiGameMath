#pragma once

#include <string>
#include <vector>
#include "DtxRect.h"
#include "DtxSize.h"
#include "DtxPoint.h"
#include "DtxCamera.h"
#include <clib/intuition_protos.h>
#include <clib/gadtools_protos.h>
#include <clib/graphics_protos.h>

class DtxWindow final
{
public:
	DtxWindow(const std::string& title, const DtxRect& dtxRect, const DtxSize& dtxMinSize, const DtxSize& dtxMaxSize);
	~DtxWindow();
	Window *OpenWindow(bool getMouseMoveEvents = false);
	ULONG GetSignalMask();
	Window *GetWindow();
	void Clear();
	void DtxAddGadget(const DtxRect& rect, const std::string& text);
	Gadget *AddButtonGadget(const DtxRect& rect, const std::string& text, bool disabled = false);
	void DrawPolyLine(const std::vector<DtxPoint>& dtxTriangle);
	DtxCamera* GetCamera();
private:
	Window *mpWindow;
	const std::string mTitle;
	DtxRect mDtxRect;
	DtxSize mMinDtxSize;
	DtxSize mMaxDtxSize;
	Screen *mpScreen;
	APTR mpVisualInfo;
	char mFontName[100];
	TextAttr mTextAttr;
	Gadget *mpGadgetList;
	Gadget *mpGadget;
	NewGadget mNewGadget;
	DtxCamera mDtxCamera;
};
