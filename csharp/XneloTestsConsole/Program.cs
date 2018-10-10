#region © 2018 Spencer Hoffa
// <file>Program.cs</file>
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

using XneloUtils.MVVM;

namespace XneloTestsConsole
{
	class Program
	{
		static void Main(string[] args)
		{
			test t = new test();
			t.PropertyChanged += testPropChange;

			t.testProp = true;

			t.PropertyChanged -= testPropChange;
			t.Dispose();
			t = null;
		}

		private static void testPropChange(object sender, System.ComponentModel.PropertyChangedEventArgs e)
		{
			System.Console.WriteLine("Passed");
		}
	}

	public class test: ViewModelBase
	{
		private bool m_TestProp;
		public bool testProp
		{
			get
			{ return m_TestProp; }

			set
			{
				m_TestProp = value;
				NotifyPropertyChanged(nameof(testProp));
			}
		}
	}
}
