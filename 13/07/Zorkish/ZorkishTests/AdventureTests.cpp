#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Zorkish\Adventure.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ZorkishTests
{
	TEST_CLASS(AdventureTests)
	{
	public:

		TEST_METHOD(AdventuresSingletonTest)
		{
			Assert::IsFalse(&Adventures::instance() == nullptr, L"Instance is nothing", LINE_INFO());
		}

		TEST_METHOD(CurrentAdventureTest)
		{
			Adventure* adv = new Adventure();
			adv->setName("TestAdv");
			Adventures::instance().addAdventure(1, adv);
			Adventures::instance().setCurrentAdventure(1);
			Assert::AreEqual(std::string("TestAdv"), Adventures::instance().current()->getName(), L"Adventure name different", LINE_INFO());
		}

		TEST_METHOD(AdventureNameTest)
		{
			Adventure* adv1 = new Adventure();
			adv1->setName("Test1");
			Adventure* adv2 = new Adventure();
			adv2->setName("Test2");
			Assert::AreEqual(std::string("Test1"), adv1->getName(), L"Adventure name different", LINE_INFO());
			Assert::AreEqual(std::string("Test2"), adv2->getName(), L"Adventure name different", LINE_INFO());
		}

		TEST_METHOD(AllLocationsTest)
		{
			Adventure* adv = new Adventure();
			adv->setName("TestAdv");
			Location* loc = new Location();
			adv->addLocation(1, loc);
			loc = new Location();
			adv->addLocation(2, loc);
			loc = new Location();
			adv->addLocation(3, loc);
			size_t expected_size = 3;
			Assert::IsTrue(adv->getAllLocations().size() == expected_size, L"Adventure location size is incorrect", LINE_INFO());
		}

		TEST_METHOD(CurrentLocationTest)
		{
			Adventure* adv = new Adventure();
			adv->setName("TestAdv");
			Location* loc = new Location();
			loc->setId(1);
			adv->addLocation(1, loc);
			loc = new Location();
			loc->setId(2);
			adv->addLocation(2, loc);
			loc = new Location();
			loc->setId(3);
			adv->addLocation(3, loc);
			adv->setCurrentLocation(1);
			Assert::IsTrue(adv->getCurrentLocation().getId() == 1, L"Current location is incorrect", LINE_INFO());
			adv->setCurrentLocation(2);
			Assert::IsTrue(adv->getCurrentLocation().getId() == 2, L"Current location is incorrect", LINE_INFO());
			adv->setCurrentLocation(1);
			Assert::IsTrue(adv->getCurrentLocation().getId() == 1, L"Current location is incorrect", LINE_INFO());
		}

		TEST_METHOD(LocationDetailsTest)
		{
			Location* loc = new Location();
			loc->setId(1);
			loc->setName("TestLocation");
			loc->setDetail("Test details for this location");
			Assert::IsTrue(loc->getId() == 1, L"ID incorrect", LINE_INFO());
			Assert::IsTrue(loc->getName() == "TestLocation", L"Name incorrect", LINE_INFO());
			Assert::IsTrue(loc->getDetail() == "Test details for this location", L"Detail incorrect", LINE_INFO());
		}

		TEST_METHOD(ConnectionTest)
		{
			Location* loc = new Location();
			loc->addConnection("up", 1);
			loc->addConnection("down", 2);
			loc->addConnection("left", 3);
			loc->addConnection("right", 4);
			map<string, int> test_map = loc->getConnections();
			Assert::IsTrue(test_map.at("up") == 1, L"Connection not successful", LINE_INFO());
			Assert::IsTrue(test_map.at("down") == 2, L"Connection not successful", LINE_INFO());
			Assert::IsTrue(test_map.at("left") == 3, L"Connection not successful", LINE_INFO());
			Assert::IsTrue(test_map.at("right") == 4, L"Connection not successful", LINE_INFO());
		}
	};
}