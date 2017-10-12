// Windows Header Files:
#include <windows.h>
#include <CommCtrl.h>
// C RunTime Header Files
#include <math.h>
#include <objbase.h>
#include <tchar.h>
/******************************************************************
*                                                                 *
*  Macros                                                         *
*                                                                 *
******************************************************************/
template<class Interface>
inline void
SafeRelease(
	Interface **ppInterfaceToRelease
)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}
#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif
#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif
/******************************************************************
*                                                                 *
*  DemoApp                                                        *
*                                                                 *
******************************************************************/
class DemoApp
{
public:
	DemoApp();
	~DemoApp();
	HRESULT Initialize();
	void RunMessageLoop();
private:
	HRESULT CreateResources();
	void DiscardResources();
	static LRESULT CALLBACK WndProc(
		HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam
	);
	void static DrawComboBox(int, int, int, int, HWND, HDC);
	void static DrawEclipse(int, int, int, int, HWND, HDC);
	void static GamePaint(HDC, HWND);
	void static DrawPlayer(int, int, HWND, HDC);
private:
	HWND m_hwnd;
};
