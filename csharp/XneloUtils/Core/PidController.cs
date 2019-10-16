#region © 2019 Spencer Hoffa
// <file>PidController.cs</file>
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

namespace XneloUtils.Core
{
	/// <summary>
	/// A (P)roportional, (I)ntegral, (D)erivative Controller.
	/// </summary>
	/// <remarks>
	/// The controller should be able to control any process with a measureable value, a known 
	/// ideal value and an input to the process that will affect the measured value.
	/// </remarks>
	/// <see cref="https://en.wikipedia.org/wiki/PID_controller"/>
	public sealed class PidController
	{
		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="kp">Proportional gain.</param>
		/// <param name="ki">Integral gain.</param>
		/// <param name="kd">Derivative gain.</param>
		/// <param name="outMax">The max output value.</param>
		/// <param name="outMin">The min output value.</param>
		public PidController(double kp, double ki, double kd, double outMax, double outMin)
		{
			this.Kd = kd;
			this.Ki = ki;
			this.Kp = kp;
			this.OutputMax = outMax;
			this.OutputMin = outMin;
		}

		#region Properties
		public double Kd { get; set; } = 0;
		public double Ki { get; set; } = 0;
		public double Kp { get; set; } = 0;
		public double OutputMax { get; private set; } = 0;
		public double OutputMin { get; private set; } = 0;
		public double IntegralTerm { get; private set; } = 0;

		#region ProcessVariable
		private double m_ProcessVariable = 0;

		public double ProcessVariable
		{
			get { return m_ProcessVariable; }
			set
			{
				ProcessVariableLast = m_ProcessVariable;
				m_ProcessVariable = value;
			}
		}
		#endregion

		#region ProcessVariableLast
		public double ProcessVariableLast { get; private set; } = 0;
		#endregion

		public double SetPoint { get; set; } = 0;
		#endregion

		#region Methods
		private double Clamp(double variableToClamp)
		{
			if (variableToClamp <= OutputMin) { return OutputMin; }
			if (variableToClamp >= OutputMax) { return OutputMax; }
			return variableToClamp;
		}

		/// <summary>
		/// The controller output.
		/// </summary>
		/// <param name="timeSinceLastUpdate">
		/// Timespan of the elapsed time since the previous tim that controlvariable was called.
		/// </param>
		/// <returns>Value of the variable that needs to be controlled.</returns>
		public double ControlVariable(TimeSpan timeSinceLastUpdate)
		{
			double error = SetPoint - ProcessVariable;

			// integral term calc
			IntegralTerm += (Ki * error * timeSinceLastUpdate.TotalSeconds);
			IntegralTerm = Clamp(IntegralTerm);

			// derivative term calc
			double dInput = ProcessVariable - ProcessVariableLast;
			double derivativeTerm = Kd * (dInput / timeSinceLastUpdate.TotalSeconds);

			// proportional term calc
			double proportionalTerm = Kp * error;

			return Clamp(proportionalTerm + IntegralTerm - derivativeTerm);
		}
		#endregion
	}
}
