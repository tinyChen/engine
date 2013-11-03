#ifdef _WIN32

#pragma once

#include <Windows.h>
#include "jni/BaseGame.h"
#include "jni/Context.h"

namespace star
{
	class TimeManager;
	class TextureManager;

	class Window final
	{
	public:
		~Window(void);

		static Window * GetInstance();
		void Initialize(HINSTANCE instance, BaseGame * pBaseGame);

		void WindowInactiveUpdate(bool inactive);
		const HDC & GetHDC() const;
		const HWND & GetHandle() const;
		void SetClipRect(const RECT & rect);

		bool IsInitialized() const;
		bool IsCursorClipped() const;
		bool IsFullScreen() const;
		bool CanGoFullScreen() const;
		bool IsActive() const;
		bool UpdateGameWhenInactive() const;
		bool ChangeResolutionWhenGoingFullScreen() const;

		void ToggleFullScreen(HWND hWnd);
		void SetFullScreen(HWND hWnd, bool fullscreen);
		void UpdateClippingIfNeeded();
		void SetWindowMoved();
		void SetWindowActive(bool active);

		void SetResolution(int width, int height, bool reset = true);

		void ForceTimerCalculation();

		void GetWindowClipSize(RECT & rect);

	private:
		Window();

		HWND GetConsoleHWND();
		void SetWindowsTitle() const;

		static Window * m_pInstance;

		void ClientResize(int & width, int & height);
		void GetWindowDifferenceSize(int & difX, int & difY);

		bool m_IsInitialized;
		bool m_IsFullScreen;
		bool m_CanGoFullScreen;
		bool m_WindowMoved;
		bool m_IsActive;
		bool m_UpdateGameWhenInactive;
		bool m_ManipulateWindowResolution;

		struct WindowState
		{
			BOOL Maximized;
			long Style, ExStyle;
			RECT WinRect;
		};

		WindowState m_SavedWindowState;

		BaseGame* mGamePtr;
		TimeManager* mTimeManager;
		Context mContext;

		HWND mHandle;
		HGLRC mOGLContext;
		HDC mHDC;
		RECT mClipRect;

		HANDLE m_hKeybThread;
		DWORD m_dKeybThreadID;

		static LRESULT CALLBACK wEventsProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam);

		static const uint32 CLASS_STYLES_COUNT = 5;
		static const uint32 WINDOW_STYLES_COUNT = 28;

		typedef std::pair<tstring, uint32> psip;
		static const psip CLASS_STYLES[];
		static const psip WINDOW_STYLES[];

		int CastStringToClassStyle(const tstring & style);
		int CastStringToWinStyle(const tstring & style);

		Window & operator=(const Window&);
		Window & operator=(Window&&);
		Window(const Window&);
		Window(Window&&);
	};

	void UpdateWindowClipping(HWND hWnd);
}

DWORD WINAPI KeybThreadProc ();
#endif
