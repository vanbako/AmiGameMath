#include "DtxWindow.h"

DtxWindow::DtxWindow(const std::string& title, const DtxRect& dtxRect, const DtxSize& dtxMinSize, const DtxSize& dtxMaxSize)
    : mpWindow{ nullptr }
    , mTitle{ title }
    , mDtxRect{ dtxRect }
    , mMinDtxSize{ dtxMinSize }
    , mMaxDtxSize{ dtxMaxSize }
    , mpScreen{ nullptr }
    , mpVisualInfo{ nullptr }
    , mFontName{ "topaz.font" }
    , mTextAttr{}
    , mpGadgetList{ nullptr }
    , mpGadget{ nullptr }
    , mNewGadget{}
    , mDtxCamera{ WORD(dtxRect.mWidth), WORD(dtxRect.mHeight) }
{
    mTextAttr = TextAttr{ mFontName, 11, 0, 0 };
    Screen *mpScreen{ LockPubScreen(nullptr) };
    mpVisualInfo = GetVisualInfo(mpScreen, TAG_END);
    mpGadget = CreateContext(&mpGadgetList);
    mNewGadget.ng_TextAttr = &mTextAttr;
    mNewGadget.ng_VisualInfo = mpVisualInfo;
}

DtxWindow::~DtxWindow()
{
    if (mpWindow != nullptr)
        CloseWindow(mpWindow);
    FreeGadgets(mpGadgetList);
    FreeVisualInfo(mpVisualInfo);
    UnlockPubScreen(nullptr, mpScreen);
}

Window *DtxWindow::OpenWindow(bool getMouseMoveEvents)
{
    ULONG idcmpFlags{ IDCMP_CLOSEWINDOW | IDCMP_NEWSIZE | IDCMP_GADGETUP | IDCMP_GADGETDOWN };
    if (getMouseMoveEvents)
    {
        idcmpFlags |= IDCMP_MOUSEBUTTONS | IDCMP_MOUSEMOVE;
    	mpWindow = OpenWindowTags(NULL,
            WA_Left, mDtxRect.mLeft, WA_Top, mDtxRect.mTop,
            WA_Width, mDtxRect.mWidth, WA_Height, mDtxRect.mHeight,
            WA_MinWidth, mMinDtxSize.mWidth, WA_MinHeight, mMinDtxSize.mHeight,
            WA_MaxWidth, mMaxDtxSize.mWidth, WA_MaxHeight, mMaxDtxSize.mHeight,
            WA_Title, mTitle.c_str(),
            WA_Gadgets, mpGadgetList,
            WA_PubScreen, mpScreen,
            WA_CloseGadget, TRUE, WA_DepthGadget, TRUE,
            WA_SizeGadget, TRUE, WA_DragBar, TRUE,
            WA_Activate, TRUE, WA_RMBTrap, TRUE,
            WA_ReportMouse, TRUE,
            WA_IDCMP, idcmpFlags,
            TAG_DONE
        );
    }
    else
    	mpWindow = OpenWindowTags(NULL,
            WA_Left, mDtxRect.mLeft, WA_Top, mDtxRect.mTop,
            WA_Width, mDtxRect.mWidth, WA_Height, mDtxRect.mHeight,
            WA_MinWidth, mMinDtxSize.mWidth, WA_MinHeight, mMinDtxSize.mHeight,
            WA_MaxWidth, mMaxDtxSize.mWidth, WA_MaxHeight, mMaxDtxSize.mHeight,
            WA_Title, mTitle.c_str(),
            WA_Gadgets, mpGadgetList,
            WA_PubScreen, mpScreen,
            WA_CloseGadget, TRUE, WA_DepthGadget, TRUE,
            WA_SizeGadget, TRUE, WA_DragBar, TRUE,
            WA_Activate, TRUE, WA_RMBTrap, TRUE,
            WA_IDCMP, idcmpFlags,
            TAG_DONE
        );
    return mpWindow;
}

ULONG DtxWindow::GetSignalMask()
{
    if (mpWindow == nullptr)
        return 0;
    return (1L << mpWindow->UserPort->mp_SigBit);
}

Window *DtxWindow::GetWindow()
{
    return mpWindow;
}

void DtxWindow::Clear()
{
    if (mpWindow != nullptr)
        EraseRect(
            mpWindow->RPort,
            mpWindow->BorderLeft, mpWindow->BorderTop,
            mpWindow->Width - mpWindow->BorderRight, mpWindow->Height - mpWindow->BorderBottom
        );
}

void DtxWindow::DtxAddGadget(const DtxRect& rect, const std::string& text)
{
    mNewGadget.ng_LeftEdge = rect.mLeft;
    mNewGadget.ng_TopEdge = rect.mTop;
    mNewGadget.ng_Width = rect.mWidth;
    mNewGadget.ng_Height = rect.mHeight;
    mNewGadget.ng_GadgetText = text.c_str();
}

Gadget *DtxWindow::AddButtonGadget(const DtxRect& rect, const std::string& text, bool disabled)
{
    DtxAddGadget(rect, text);
    if (mpWindow != nullptr)
        RemoveGList(mpWindow, mpGadgetList, -1);
    if (disabled)
        mpGadget = CreateGadget(BUTTON_KIND, mpGadget, &mNewGadget, GA_Disabled, TRUE, TAG_END);
    else
        mpGadget = CreateGadget(BUTTON_KIND, mpGadget, &mNewGadget, TAG_END);
    if (mpWindow != nullptr)
    {
        AddGList(mpWindow, mpGadgetList, 0, -1, nullptr);
        RefreshGList(mpGadgetList, mpWindow, nullptr, -1);
    }
    return mpGadget;
}

void DtxWindow::DrawPolyLine(const std::vector<DtxPoint>& dtxTriangle)
{
    if (mpWindow == nullptr)
        return;
    SetAPen(mpWindow->RPort, 1);
    Move(mpWindow->RPort, dtxTriangle[0].mX, dtxTriangle[0].mY);
    PolyDraw(mpWindow->RPort, dtxTriangle.size() - 1, (WORD*)&dtxTriangle[1]);
    Draw(mpWindow->RPort, dtxTriangle[0].mX, dtxTriangle[0].mY);
}

DtxCamera* DtxWindow::GetCamera()
{
    return &mDtxCamera;
}
