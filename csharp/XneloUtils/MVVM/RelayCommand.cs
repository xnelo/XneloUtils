#region © 2018 Spencer Hoffa
// <file>RelayCommand.cs</file>
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
using System.Diagnostics;
using System.Windows.Input;

namespace XneloUtils.MVVM
{
	/// <summary>
	/// Simple command implementation
	/// Found at: http://msdn.microsoft.com/en-us/magazine/dd419663.aspx#id0090030
	/// </summary>
	public class RelayCommand : ICommand
	{
		#region Fields
		private readonly Action<object> _execute;
		private readonly Predicate<object> _canExecute;
		private bool m_CanExecute;
		#endregion // Fields

		#region Constructors
		public RelayCommand(Action<object> execute)
		: this(execute, null)
		{
		}

		public RelayCommand(Action<object> execute, Predicate<object> canExecute)
		{
			if (execute == null)
				throw new ArgumentNullException("execute");

			_execute = execute;
			_canExecute = canExecute;
		}
		#endregion // Constructors

		#region ICommand Members
		[DebuggerStepThrough]
		public bool CanExecute(object parameter)
		{
			bool retval = _canExecute == null ? true : _canExecute(parameter);
			if (m_CanExecute != retval)
			{
				m_CanExecute = retval;
				CanExecuteChanged?.Invoke(this, new EventArgs());
			}

			return retval;
		}

		public event EventHandler CanExecuteChanged;

		public void Execute(object parameter)
		{
			_execute(parameter);
		}
		#endregion // ICommand Members
	}
}
