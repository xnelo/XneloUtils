#region File Info
// Original code found at http://svetoslavsavov.blogspot.com/2009/07/switching-wpf-interface-themes-at.html
// Author: Svetoslav Savov
// Posted Date: Saturday, July 25, 2009 9:14 PM
// Access Date: Tuesday, August 21, 2018 11:55 PM
//
// All code below is property of the respective author, Svetoslav Savov.
//
// How To Use:
// local:MkThemeSelector.CurrentThemeDictionary="{Binding ElementName=cmbThemes, Path=SelectedItem.Tag}"
#endregion

using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;

namespace XneloUtils.WPFUtils.Themes
{
	/// <summary>
	/// Inherits ResourceDictionary, used to identify a theme resource dictionary in the merged 
	/// dictionaries collection
	/// </summary>
	public class ThemeResourceDictionary : ResourceDictionary
	{ }

	public class MKThemeSelector: DependencyObject
	{
		public static readonly DependencyProperty CurrentThemeDictionaryProperty =
			DependencyProperty.RegisterAttached("CurrentThemeDictionary", 
												typeof(Uri),
												typeof(MKThemeSelector),
												new UIPropertyMetadata(null, 
																CurrentThemeDictionaryChanged));

		public static Uri GetCurrentThemeDictionary(DependencyObject obj)
		{
			return (Uri)obj.GetValue(CurrentThemeDictionaryProperty);
		}

		public static void SetCurrentThemeDictionary(DependencyObject obj, Uri value)
		{
			obj.SetValue(CurrentThemeDictionaryProperty, value);
		}

		private static void CurrentThemeDictionaryChanged(DependencyObject obj, 
														  DependencyPropertyChangedEventArgs e)
		{
			if (obj is FrameworkElement) // works only on FrameworkElement objects
			{
				ApplyTheme(obj as FrameworkElement, GetCurrentThemeDictionary(obj));
			}
		}

		private static void ApplyTheme(FrameworkElement targetElement, Uri dictionaryUri)
		{
			if (targetElement == null) return;

			try
			{
				ThemeResourceDictionary themeDictionary = null;
				if (dictionaryUri != null)
				{
					themeDictionary = new ThemeResourceDictionary();
					themeDictionary.Source = dictionaryUri;

					// add the new dictionary to the collection 
					// of merged dictionaries of the target object
					targetElement.Resources.MergedDictionaries.Insert(0, themeDictionary);
				}

				// find if the target element already has a theme applied
				var dictionaries = targetElement.Resources.MergedDictionaries;

				List<ThemeResourceDictionary> existingDictionaries =
					(from dictionary in dictionaries.OfType<ThemeResourceDictionary>()
					 select dictionary).ToList();

				// remove the existing dictionaries 
				foreach (ThemeResourceDictionary thDictionary in existingDictionaries)
				{
					if (themeDictionary == thDictionary)
					{
						continue;  // don't remove the newly added dictionary
					}
					targetElement.Resources.MergedDictionaries.Remove(thDictionary);
				}
			}
			finally { }
		}
	}
}
