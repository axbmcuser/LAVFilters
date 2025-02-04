/*
 *      Copyright (C) 2010-2019 Hendrik Leppkes
 *      http://www.1f0.de
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#pragma once

#include <ShellAPI.h>

class CBaseTrayIcon
{
public:
  CBaseTrayIcon(IBaseFilter *pFilter, const WCHAR *wszName, int resIcon);
  virtual ~CBaseTrayIcon(void);

  static BOOL ProcessBlackList();
  HRESULT SetCustomOpenPropPage(HRESULT (*fpCustomOpenPropPage)(IUnknown* pFilter));

protected:
  virtual HRESULT CreateTrayIconData();

  virtual HMENU GetPopupMenu() { return nullptr; }
  virtual HRESULT ProcessMenuCommand(HMENU hMenu, int cmd) { return E_NOTIMPL; }

  HRESULT OpenPropPage();

private:
  HRESULT StartMessageThread();
  HRESULT RegisterWindowClass();
  HRESULT CreateMessageWindow();

  DWORD TrayMessageThread();
  static unsigned int WINAPI InitialThreadProc(LPVOID pv);

  static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
  IBaseFilter *m_pFilter;

private:
  CAMEvent m_evSetupFinished{TRUE};

  HANDLE m_hThread       = 0;
  HWND   m_hWnd          = 0;
  BOOL   m_bPropPageOpen = FALSE;
  HRESULT (*m_fpCustomOpenPropPage)(IUnknown* pFilter) = nullptr;

  WCHAR m_wszClassName[64];
  const WCHAR *m_wszName = nullptr;
  int m_resIcon          = 0;

  NOTIFYICONDATA m_NotifyIconData;
};
