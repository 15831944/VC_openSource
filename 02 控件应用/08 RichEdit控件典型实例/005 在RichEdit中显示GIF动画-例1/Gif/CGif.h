// CGif.h : Declaration of the CCGif

#ifndef __CGIF_H_
#define __CGIF_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "afxcmn.h"
#include "Gdiplus//Gdiplus.h"
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus//gdiplus.lib")


#define MAX_IMGNUM 2000		//�����������ͼ������

#include "afxctl.h"
/////////////////////////////////////////////////////////////////////////////
// CCGif

enum ImageTypeEx{IT_UNKNOWN,IT_STATIC,IT_DYNAMIC};

class ATL_NO_VTABLE CCGif : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CCGif, ICGif, &IID_ICGif, &LIBID_GIFLib>,
	public CComControl<CCGif>,
	public IPersistStreamInitImpl<CCGif>,
	public IOleControlImpl<CCGif>,
	public IOleObjectImpl<CCGif>,
	public IOleInPlaceActiveObjectImpl<CCGif>,
	public IViewObjectExImpl<CCGif>,
	public IOleInPlaceObjectWindowlessImpl<CCGif>,
	public IPersistStorageImpl<CCGif>,
	public ISpecifyPropertyPagesImpl<CCGif>,
	public IQuickActivateImpl<CCGif>,
	public IDataObjectImpl<CCGif>,
	public IProvideClassInfo2Impl<&CLSID_CGif, NULL, &LIBID_GIFLib>,
	public CComCoClass<CCGif, &CLSID_CGif>,
	public IPropertyNotifySinkCP<CCGif>,
	public IConnectionPointContainerImpl<CCGif>

{
public:
	CContainedWindow	m_ctlStatic;
	GdiplusStartupInput m_Gdiplus;					//����GDI+��ʼ������
	ULONG_PTR			m_pGdiToken;				//����GID+��ʶ
	Bitmap				*m_pBmp;					//����λͼ����������Image��
	UINT				m_Count;					//��¼ά��
	UINT				m_FrameCount;				//֡��
	PropertyItem*		pItem ;						//����ͼ������
	int					fcount;						//����һ����ʱ���ͱ���
	UINT				delay;						//��һ֡����ʱ	
	RECT				m_RC;
	static BOOL			m_bChange;
	BOOL				m_bNewInsert;				//����Ƿ��ж��󱻲���

	static BOOL			m_bSetHook;					//����Ƿ�ҹ�
	static WNDPROC		RichProc;					//���崰�ں���ָ��
	int					m_Num;
	static int			m_ImageNum;					//��¼�����ͼ������
	static CCGif		*m_ImageInfo[MAX_IMGNUM];
	static HHOOK		m_hHook;
	static HANDLE		m_hThread;
	ATL_DRAWINFO		m_DrawInfo;
	BOOL				m_bLoaded;					//�Ƿ��Ѿ�������ͼ��
	ImageTypeEx			m_ImageType;
	int					m_InsertIndex;
	HWND				hTmp;						//��ʱ��������ATL�ؼ��ĸ�����
	WCHAR				m_wchFileName[MAX_PATH];	//��¼�ļ�����
	HGLOBAL				m_hMem;						//��ʾ����ͼ��ʹ�õ����ݿռ�
	GUID				ImageID;
	BOOL				m_bDraw;					//ͼ���Ƿ���ʾ
	SYSTEMTIME			m_DrawTime;					//�滭ʱ��
	CCGif() //:	
		//m_ctlStatic(_T("Static"), this, 1)
	{
		m_bLoaded		= FALSE;
		m_bChange		= FALSE;
		m_ImageType		= IT_UNKNOWN;
		m_bNewInsert	= TRUE;
		m_InsertIndex	= 0;
		hTmp			= NULL;
		m_hMem			= NULL;
		m_bDraw			= FALSE;
		m_Num			= 0;

	}
	virtual ~CCGif() //:	
		//m_ctlStatic(_T("Static"), this, 1)
	{
		m_ImageNum--;
		if (m_hMem != NULL)
		{
			GlobalFree(m_hMem);
			m_hMem = NULL;
		}
		if (m_ImageNum == 0)
		{
			::TerminateThread(m_hThread,0);
			UnhookWindowsHookEx(m_hHook);
			GdiplusShutdown(m_pGdiToken);
		}
	}


static DWORD __stdcall ThreadProc( LPVOID lpParameter)
{
	while (true)
	{ 	
		Sleep(250);
		for (int i=0; i< m_ImageNum; i++)
		{
			if (m_ImageInfo[i] != NULL)
			{
				if (m_ImageInfo[i]->m_ImageType == IT_DYNAMIC)
				{
					::InvalidateRect(m_ImageInfo[i]->hTmp, &m_ImageInfo[i]->m_RC, FALSE);
					m_ImageInfo[i]->m_Num = 0;
				}
			}
		}
		m_bChange = FALSE; 
	}
	return 0;
}

static LRESULT __stdcall GetMsgProc(int code,WPARAM wParam,LPARAM lParam)
{
	MSG *pMsg = (MSG*)lParam;
	if (pMsg != NULL)
	{	
		char clName[MAX_PATH] = {0};
		GetClassName(pMsg->hwnd,clName,MAX_PATH);
		if (pMsg->message == WM_KEYDOWN || pMsg->message == WM_MOUSEMOVE)
		{
			for (int i=0; i< m_ImageNum; i++)
			{
				if (m_ImageInfo[i] != NULL)
				{
					if (m_ImageInfo[i]->hTmp == pMsg->hwnd)
					{
						m_ImageInfo[i]->m_Num = 1;
						break;
					}
				}
			}			
			return S_OK;
		}
		else if (pMsg->message == WM_PAINT )
		{
			for (int i=0; i< m_ImageNum; i++)
			{
				if (m_ImageInfo[i] != NULL && m_ImageInfo[i]->m_Num ==1)
				{
					if (m_ImageInfo[i]->hTmp == pMsg->hwnd)
					{
						m_ImageInfo[i]->m_Num = 2;

						break;
					}
				}
			}
			return S_OK;
		}
	}
	return CallNextHookEx(0,code,wParam,lParam);
}

DECLARE_REGISTRY_RESOURCEID(IDR_CGIF)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCGif)
	COM_INTERFACE_ENTRY(ICGif)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceSite)//IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)


END_COM_MAP()

BEGIN_PROP_MAP(CCGif)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("Appearance", DISPID_APPEARANCE, CLSID_NULL)
	PROP_ENTRY("AutoSize", DISPID_AUTOSIZE, CLSID_NULL)
	PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage)
	PROP_ENTRY("BackStyle", DISPID_BACKSTYLE, CLSID_NULL)
	PROP_ENTRY("BorderColor", DISPID_BORDERCOLOR, CLSID_StockColorPage)
	PROP_ENTRY("BorderStyle", DISPID_BORDERSTYLE, CLSID_NULL)
	PROP_ENTRY("BorderVisible", DISPID_BORDERVISIBLE, CLSID_NULL)
	PROP_ENTRY("BorderWidth", DISPID_BORDERWIDTH, CLSID_NULL)
	PROP_ENTRY("Caption", DISPID_CAPTION, CLSID_NULL)
	PROP_ENTRY("DrawMode", DISPID_DRAWMODE, CLSID_NULL)
	PROP_ENTRY("DrawStyle", DISPID_DRAWSTYLE, CLSID_NULL)
	PROP_ENTRY("DrawWidth", DISPID_DRAWWIDTH, CLSID_NULL)
	PROP_ENTRY("Enabled", DISPID_ENABLED, CLSID_NULL)
	PROP_ENTRY("FillColor", DISPID_FILLCOLOR, CLSID_StockColorPage)
	PROP_ENTRY("FillStyle", DISPID_FILLSTYLE, CLSID_NULL)
	PROP_ENTRY("Font", DISPID_FONT, CLSID_StockFontPage)
	PROP_ENTRY("ForeColor", DISPID_FORECOLOR, CLSID_StockColorPage)
	PROP_ENTRY("HWND", DISPID_HWND, CLSID_NULL)
	PROP_ENTRY("MouseIcon", DISPID_MOUSEICON, CLSID_StockPicturePage)
	PROP_ENTRY("MousePointer", DISPID_MOUSEPOINTER, CLSID_NULL)
	PROP_ENTRY("Picture", DISPID_PICTURE, CLSID_StockPicturePage)
	PROP_ENTRY("TabStop", DISPID_TABSTOP, CLSID_NULL)
	PROP_ENTRY("Text", DISPID_TEXT, CLSID_NULL)
	PROP_ENTRY("Valid", DISPID_VALID, CLSID_NULL)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CCGif)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CCGif)
	CHAIN_MSG_MAP(CComControl<CCGif>)
ALT_MSG_MAP(1)
	// Replace this with message map entries for superclassed Static



END_MSG_MAP()
	//��д�����IOleObject_SetClientSite����������m_bNewInsert��Ա
	inline HRESULT IOleObject_SetClientSite(IOleClientSite *pClientSite)
	{
		//ATLASSERT(pClientSite == NULL || m_spClientSite == NULL);
		m_bNewInsert = TRUE;
		if (pClientSite==NULL)
			return S_OK;
		m_spClientSite = pClientSite;
		m_spAmbientDispatch.Release();
		if (m_spClientSite != NULL)
		{
			m_spClientSite->QueryInterface(IID_IDispatch,
				(void**) &m_spAmbientDispatch.p);
		}
		return S_OK;
	}

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{	
		if (m_bLoaded)
		{
			memcpy(&m_DrawInfo, &di, sizeof(ATL_DRAWINFO));
			//��ȡͼ�����ʾ����
			RECT& rc = *(RECT*)di.prcBounds;
			GUID Guid = FrameDimensionTime;
			//���ͼ���Ѿ����뵽�ؼ��У���ȡ�������ĸ����ھ��
			if (m_bNewInsert == TRUE)
			{
				IOleInPlaceSite* pSite = NULL;
				if (m_spClientSite != NULL)
				{
					m_spClientSite->QueryInterface(__uuidof(IOleInPlaceSite), (void**)&pSite);
					if (pSite != NULL)
					{
						pSite->GetWindow(&hTmp);
						
					}

					m_bNewInsert = FALSE;
				}
			}
			//�Ƿ�ΪGif����
			if(m_ImageType == IT_DYNAMIC)
			{
				if (m_bSetHook == FALSE)
				{
					m_bSetHook = TRUE;
					//����һ���̣߳�������ʾ����
					m_hThread = CreateThread(NULL, 0, ThreadProc, (void*)this, 0, 0);
					//����һ����Ϣ���ӣ��ػ񸸴��ڵ���Ϣ�����ڸ��¶���
					m_hHook = ::SetWindowsHookEx(WH_GETMESSAGE, GetMsgProc, 0, ::GetCurrentThreadId());
				}
			}
			//��ʾͼ��
			Graphics gh(di.hdcDraw);
			gh.DrawImage(m_pBmp,rc.left+1,rc.top+1,m_pBmp->GetWidth(),m_pBmp->GetHeight());
			//��¼��ǰͼ�������
			m_RC.left =rc.left+1;
			m_RC.top = rc.top+1;
			m_RC.right = m_RC.left+m_pBmp->GetWidth();
			m_RC.bottom =m_RC.top +m_pBmp->GetHeight();
			//�����Gif��������ʾ��һ֡ͼ��
			if (m_ImageType==IT_DYNAMIC)
			{
				if (m_Num == 0)
				{
					m_pBmp->SelectActiveFrame(&Guid,fcount++);
				}
				if(fcount >= m_FrameCount) 
				{
					fcount = 0;
				}
			}
		}
		return S_OK;
	}


// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)
// ICGif
public:
	STDMETHOD(SaveToFile)(BSTR FileName);
	STDMETHOD(put_FName)(long hParent, /*[in]*/ BSTR newVal);
	BSTR m_FileName;
	STDMETHOD(get_FileName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FileName)(/*[in]*/ BSTR newVal);
	STDMETHOD(LoadFromFile)(LPCTSTR FileName);
	short m_nAppearance;
	OLE_COLOR m_clrBackColor;
	LONG m_nBackStyle;
	OLE_COLOR m_clrBorderColor;
	LONG m_nBorderStyle;
	BOOL m_bBorderVisible;
	LONG m_nBorderWidth;
	CComBSTR m_bstrCaption;
	LONG m_nDrawMode;
	LONG m_nDrawStyle;
	LONG m_nDrawWidth;
	BOOL m_bEnabled;
	OLE_COLOR m_clrFillColor;
	LONG m_nFillStyle;
	CComPtr<IFontDisp> m_pFont;
	OLE_COLOR m_clrForeColor;
	CComPtr<IPictureDisp> m_pMouseIcon;
	LONG m_nMousePointer;
	CComPtr<IPictureDisp> m_pPicture;
	BOOL m_bTabStop;
	CComBSTR m_bstrText;
	BOOL m_bValid;

};

#endif //__CGIF_H_


