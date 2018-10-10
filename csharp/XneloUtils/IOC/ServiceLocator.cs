#region © 2018 Spencer Hoffa
// <file>ServiceLocator.cs</file>
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
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.ComponentModel.Composition.Hosting;
using System.Linq;

namespace XneloUtils.IOC
{
	public static class ServiceLocator
	{
		#region Fields
		private static CompositionContainer m_CompositionContainer;
		#endregion

		#region Constructor
		static ServiceLocator()
		{
			Init();
		}

		public static void Init()
		{
			if (!IsInitialized)
			{
				//An aggregate catalog that combines multiple catalogs  
				var catalog = new AggregateCatalog();
				catalog.Catalogs.Add(new DirectoryCatalog("./"));
				m_CompositionContainer = new CompositionContainer(catalog);

				IsInitialized = true;
			}
		}

		/// <summary>
		/// Dispose of the Service Locator class. This should only ever be called at the end of the 
		/// program. Undefined behavior should be expected if called in the middle of the program.
		/// </summary>
		public static void Dispose()
		{
			// Dispose all AutoDisposed
			foreach (IAutoDisposable disposable in GetAllServices<IAutoDisposable>())
			{
				disposable.AutoDispose();
			}

			if (m_CompositionContainer != null)
			{
				m_CompositionContainer.Dispose();
				m_CompositionContainer = null;
			}

			IsInitialized = false;
		}
		#endregion

		#region Properties
		#region IsInitialized
		/// <summary>
		/// Is the Service Locator initialized. If this returns false then you must call Init();
		/// </summary>
		public static bool IsInitialized { get; private set; } = false;
		#endregion
		#endregion

		#region Methods
		/// <summary>
		/// Get all objects that export tye typeparam.
		/// </summary>
		/// <typeparam name="T">A class type to find an export for.</typeparam>
		/// <returns>An iterable object with all the classes.</returns>
		public static IEnumerable<T> GetAllServices<T>()
		{
			if (IsInitialized)
				return m_CompositionContainer.GetExportedValues<T>();
			else
				return null;
		}

		/// <summary>
		/// Get a single object that exports the typeparam.
		/// </summary>
		/// <remarks>
		/// If there are multiple objects that export the typeparam then the first one is 
		/// returned. There is no guarantee which object will be the first.
		/// </remarks>
		/// <typeparam name="T">An class type to find an export for.</typeparam>
		/// <returns>
		/// A constructed object of type T if a valid object is found. Otherwise null.
		/// </returns>
		public static T GetService<T>()
		{
			T retVal = default(T);
			if (IsInitialized)
			{
				try
				{
					retVal = m_CompositionContainer.GetExportedValueOrDefault<T>();
				}
				catch (ImportCardinalityMismatchException)
				{
					retVal = m_CompositionContainer.GetExportedValues<T>().FirstOrDefault();
				}
			}
			return retVal;
		}
		#endregion
	}
}
