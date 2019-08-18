#region © 2019 Spencer Hoffa
// <file>IPAddressValidator.cs</file>
// <author> Spencer Hoffa </author>
//
// <copyright> 2019 Spencer Hoffa </copyright>
//
// <license>
// The zlib/libpng License
// Copyright(c) 2019 Spencer Hoffa
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
using System.Windows.Controls;

namespace XneloUtils.WPFUtils.Validators
{
	public class IPAddressValidator : ValidationRule
	{
		#region Properties
		#region RequirePort
		/// <summary>
		/// Should a port number be required.
		/// </summary>
		public bool RequiredPort { get; set; } = false;
		#endregion
		#endregion

		#region Methods
		private ValidationResult GetStandardError()
		{
			return new ValidationResult(false, "Invalid IP Address. Must be in form xxx.xxx.xxx.xxx:xxx.");
		}

		public override ValidationResult Validate(object value, CultureInfo cultureInfo)
		{
			string toValidate = value as string;
			if (toValidate == null)
			{
				return new ValidationResult(false, "Passed in value cannot be null.");
			}
			
			var parts = toValidate.Split('.');
			
			if (parts.Length != 4)
			{
				return GetStandardError();
			}

			if (ValidatePart(parts[0]) &&
				ValidatePart(parts[1]) &&
				ValidatePart(parts[2]) &&
				ValidatePart(parts[3], true))
			{
				return ValidationResult.ValidResult;
			}
			else
			{
				return GetStandardError();
			}
		}

		private bool IsValidNumber(string num)
		{
			if (string.IsNullOrWhiteSpace(num))
				return false;

			if (num[0] == '0' && num.Length > 1)
				return false;

			foreach (char c in num)
			{
				if (!char.IsDigit(c))
					return false;
			}

			return true;
		}

		private bool IsValidPort(string portNum)
		{
			const int MinPortNum = 1;
			const int MaxPortNum = 65535;

			bool retVal = false;

			try
			{
				if (IsValidNumber(portNum))
				{
					int port = int.Parse(portNum);
					retVal = (port >= MinPortNum && port <= MaxPortNum);
				}
			}
			catch (Exception)
			{
				retVal = false;
			}

			return retVal;
		}

		private bool IsValidIPPart(string part)
		{
			const int MaxIpPartNum = 255;
			const int MinIpPartNum = 0;

			bool retVal = false;

			try
			{
				if (IsValidNumber(part))
				{
					int val = int.Parse(part);

					retVal = (val >= MinIpPartNum && val <= MaxIpPartNum);
				}
			}
			catch (Exception)
			{
				retVal = false;
			}

			return retVal;
		}

		private bool ValidatePart(string part, bool isLast = false)
		{
			bool isValid = false;

			if (!string.IsNullOrWhiteSpace(part))
			{
				if (isLast == false)
				{
					isValid = IsValidIPPart(part);
				}
				else
				{
					// does it have a port number
					var splits = part.Split(':');
					if (splits.Length == 1)
					{
						// no

						// is a port required?
						if (RequiredPort)
						{
							isValid = false;
						}
						else
						{
							isValid = IsValidIPPart(part);
						}
					}
					else if (splits.Length == 2)
					{
						// yes
						isValid = IsValidIPPart(splits[0]) &&
								IsValidPort(splits[1]);
					}
					// anything else is invalid
				}
			}

			return isValid;
		}
		#endregion
	}
}
