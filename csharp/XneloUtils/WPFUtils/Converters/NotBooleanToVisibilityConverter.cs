#region © 2018 Spencer Hoffa
// <file>NotBooleanToVisibilityConverter.cs</file>
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

using System;
using System.Globalization;
using System.Windows;
using System.Windows.Data;

namespace XneloUtils.WPFUtils.Converters
{
	public class NotBooleanToVisibilityConverter: IValueConverter
	{
		public object Convert(object value, Type targetType, object parameter, CultureInfo language)
		{
			var retVal = Visibility.Collapsed;

			if (value is bool)
			{
				if (((bool)value) == false)
				{
					retVal = Visibility.Visible;
				}
			}

			return retVal;
		}

		public object ConvertBack(object value, Type targetType, object parameter, CultureInfo language)
		{
			bool retVal = true;

			if (value is Visibility)
			{
				if (((Visibility)value) == Visibility.Visible)
				{
					retVal = false;
				}
			}

			return retVal;
		}
	}
}
