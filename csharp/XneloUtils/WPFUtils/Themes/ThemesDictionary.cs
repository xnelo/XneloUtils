#region © 2018 Spencer Hoffa
// <file>ThemesDictionary.cs</file>
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

using System.Collections.Generic;

namespace XneloUtils.WPFUtils.Themes
{
	public static class ThemesDictionary
	{
		public static readonly ThemeData DefaultTheme = new ThemeData("Default", null);

		private static Dictionary<string, ThemeData> m_Themes;

		static ThemesDictionary()
		{
			m_Themes = new Dictionary<string, ThemeData>();
			
			m_Themes.Add("IG", new ThemeData("IG", "/XneloUtils;component/WPFUtils/Themes/IG/IG.MSControls.Core.Implicit.xaml"));
			m_Themes.Add("Metro", new ThemeData("Metro", "/XneloUtils;component/WPFUtils/Themes/Metro/Metro.MSControls.Core.Implicit.xaml"));
			m_Themes.Add("Metro Dark", new ThemeData("Metro Dark", "/XneloUtils;component/WPFUtils/Themes/MetroDark/MetroDark.MSControls.Core.Implicit.xaml"));
			m_Themes.Add("Office 2010 Blue", new ThemeData("Office 2010 Blue", "/XneloUtils;component/WPFUtils/Themes/Office2010Blue/Office2010Blue.MSControls.Core.Implicit.xaml"));
			m_Themes.Add("Office 2013", new ThemeData("Office 2013", "/XneloUtils;component/WPFUtils/Themes/Office2013/Office2013.MSControls.Core.Implicit.xaml"));
		}

		/// <summary>
		/// All the available themes (including the default).
		/// </summary>
		public static IEnumerable<ThemeData> AllThemes
		{
			get
			{
				List<ThemeData> newList = new List<ThemeData>();
				newList.Add(DefaultTheme);
				newList.AddRange(Themes);
				return newList;
			}
		}

		/// <summary>
		/// All the available themes (except for the default).
		/// </summary>
		public static IEnumerable<ThemeData> Themes
		{
			get
			{
				return m_Themes.Values;
			}
		}

		/// <summary>
		/// Lookup a theme by it's name.
		/// </summary>
		/// <param name="themeName">The name of the theme to lookup.</param>
		/// <returns>
		/// The theme data if it is found, otherwise the default theme is returned.
		/// </returns>
		public static ThemeData LookupTheme(string themeName)
		{
			bool throwAway;
			return LookupTheme(themeName, out throwAway);
		}

		/// <summary>
		/// Lookup a theme by it's name.
		/// </summary>
		/// <param name="themeName">The name of the theme to lookup.</param>
		/// <param name="foundTheme">Was the theme found is placed in this variable.</param>
		/// <returns>
		/// The theme data if it is found, otherwise the default theme is returned.
		/// </returns>
		public static ThemeData LookupTheme(string themeName, out bool foundTheme)
		{
			ThemeData retVal = DefaultTheme;
			if (themeName == DefaultTheme.ThemeName)
			{
				foundTheme = true;
			}
			else
			{
				foundTheme = m_Themes.TryGetValue(themeName, out retVal);
			}

			return retVal;
		}
	}
}
