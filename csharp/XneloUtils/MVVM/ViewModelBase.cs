#region © 2018 Spencer Hoffa
// <file>ViewModelBase.cs</file>
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
using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace XneloUtils.MVVM
{
	public class ViewModelBase: INotifyPropertyChanged, IDisposable
	{
		#region Event
		public event PropertyChangedEventHandler PropertyChanged;
		#endregion

		#region Methods
		public virtual void Dispose()
		{ }

		/// <summary>
		/// Fire property changed event.
		/// </summary>
		/// <param name="propertyName">The name of the property data that changed.</param>
		public void NotifyPropertyChanged([CallerMemberName] string propertyName = "")
		{
			PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
		}

		/// <summary>
		/// Fire property changed event.
		/// </summary>
		/// <param name="sender">The object firing the event.</param>
		/// <param name="propertyName">The name of the property data that changed.</param>
		public void NotifyPropertyChanged(object sender, string propertyName)
		{
			PropertyChanged?.Invoke(sender, new PropertyChangedEventArgs(propertyName));
		}
		#endregion
	}
}
