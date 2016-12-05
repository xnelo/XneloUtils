#include "XneloUtils/Testing/Testing.hpp"
#include "XneloUtils/Core/Fallible.hpp"

XNELO_TEST_CASE(FallibleTest, TestFallibleConstructor)
{
	XNELO::CORE::Fallible fail;
	XNELO_TEST_ASSERT_EQUAL(fail.GetErrorCode(), XNELO::ERRORS::OK, "Constructor sets error correctly");
	XNELO_TEST_ASSERT_EQUAL(fail.GetErrorMessage(), std::string("OK"), "Constructor sets error message correctly");
}

XNELO_TEST_CASE(FallibleTest, TestFallibleSetters)
{
	XNELO::CORE::Fallible fail;
	std::string errorMessage = "Network Failed To Initialize";
	fail.SetError(XNELO::ERRORS::NETWORKING_FAILED_TO_INITIALIZE, errorMessage);
	XNELO_TEST_ASSERT_EQUAL(fail.GetErrorCode(), XNELO::ERRORS::NETWORKING_FAILED_TO_INITIALIZE, "SetError set code correctly");
	XNELO_TEST_ASSERT_EQUAL(fail.GetErrorMessage(), errorMessage, "SetError set message correctly");
}

XNELO_TEST_CASE(FallibleTest, TestFallibleIsOK)
{
	XNELO::CORE::Fallible fail;
	std::string errorMessage = "Network Failed To Initialize";
	XNELO_TEST_ASSERT_EQUAL(fail.IsOK(), true, "Check that IsOK returns true");
	fail.SetError(XNELO::ERRORS::NETWORKING_FAILED_TO_INITIALIZE, errorMessage);
	XNELO_TEST_ASSERT_EQUAL(fail.IsOK(), false, "Check that IsOK returns false");
}