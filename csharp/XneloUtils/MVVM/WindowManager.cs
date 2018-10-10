#region © 2018 Spencer Hoffa
// <file>WindowManager.cs</file>
// <author> Spencer Hoffa </author>
//
// <copyright> 2018 Spencer Hoffa </copyright>
//
// <license>
// The zlib/libpng License
// Copyright(c) 2017 Spencer Hoffa
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the
// use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
//including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions :
//
//		1. The origin of this software must not be misrepresented; you must not
//		claim that you wrote the original software.If you use this software in
//		a product, an acknowledgment in the product documentation would be
//		appreciated but is not required.
//
//		2. Altered source versions must be plainly marked as such, and must not
//		be misrepresented as being the original software.
//
//		3. This notice may not be removed or altered from any source
//		distribution.
//
// This liscense can also be found at : http ://opensource.org/licenses/Zlib
//</license>
#endregion

using System.Collections.Concurrent;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows;

namespace XneloUtils.MVVM
{
	public static class WindowManager
	{
		#region Fields
		private static ConcurrentDictionary<string, Window> m_Windows;
		#endregion

		#region Constructor
		static WindowManager()
		{
			m_Windows = new ConcurrentDictionary<string, Window>();
		}
		#endregion

		#region Methods
		/// <summary>
		/// Close all the open windows.
		/// </summary>
		public static void CloseAllWindows()
		{
			List<string> windows = new List<string>(m_Windows.Keys);

			foreach (string winName in windows)
			{
				Window removed;
				if (m_Windows.TryRemove(winName, out removed))
				{
					ViewModelBase vm = removed.DataContext as ViewModelBase;
					removed.Close();
					if (vm != null)
					{
						vm.Dispose();
					}
				}
			}
		}

		private static void OnClosing(object sender, CancelEventArgs e)
		{
			Window win = sender as Window;
			if (win != null)
			{
				win.Closing -= OnClosing;
				string windowName = win.Tag as string;
				if (windowName != null)
				{
					Window trash;
					m_Windows.TryRemove(windowName, out trash);
					e.Cancel = false;
				}
			}
		}

		/// <summary>
		/// Open a window. You are responsible for creating the classes before passing them in.
		/// </summary>
		/// <param name="windowName">The name of the window for future lookup.</param>
		/// <param name="window">The windo object.</param>
		/// <param name="vm">The vm object for the window.</param>
		/// <param name="asDialog">Should this window be opened as a dialog.</param>
		/// <returns>A window if the window was opened, otherwise null is returned.</returns>
		public static Window OpenWindow(string windowName, Window window, ViewModelBase vm, bool asDialog = false)
		{
			if (windowName == null || 
				window == null || 
				vm == null || 
				m_Windows.ContainsKey(windowName))
			{
				return null;
			}

			if (!m_Windows.TryAdd(windowName, window))
			{
				return null;
			}
			window.DataContext = vm;
			window.Tag = windowName;
			window.Closing += OnClosing;
			if (asDialog)
			{
				window.ShowDialog();
			}
			else
			{
				window.Show();
			}

			return window;
		}
		#endregion
	}
}
