#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Zorkish\StateManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ZorkishTests
{
	TEST_CLASS(StateTests)
	{
	public:

		TEST_METHOD(StateManagerInitTest)
		{
			StateManager* state_man = new StateManager();
			Assert::IsFalse(state_man == nullptr, L"Pointer is nothing", LINE_INFO());
			Assert::IsTrue(state_man->gameIsActive(), L"Game not initialised as active", LINE_INFO());
		}

		TEST_METHOD(GameActiveTest)
		{
			StateManager* state_man = new StateManager();
			Assert::IsTrue(state_man->gameIsActive(), L"Game not active", LINE_INFO());
		}

		TEST_METHOD(GameEndedTest)
		{
			StateManager* state_man = new StateManager();
			state_man->quitRequested();
			Assert::IsFalse(state_man->gameIsActive(), L"Game did not end", LINE_INFO());
		}
	};
}