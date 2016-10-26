#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\Zorkish\Inventory.h"
#include "..\Zorkish\GameItems.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ZorkishTests
{
	TEST_CLASS(InventoryTest)
	{
	public:

		TEST_METHOD(InventoryInitTest)
		{
			Inventory* inventory = new Inventory();
			Assert::IsFalse(inventory == nullptr, L"Pointer is nothing", LINE_INFO());
		}

		TEST_METHOD(InventoryAddItemTest)
		{
			Inventory* inventory = new Inventory();
			Assert::IsTrue(inventory->addItem(new Sword()), L"Sword not added", LINE_INFO());
			Assert::IsTrue(inventory->addItem(new Key()), L"Key not added", LINE_INFO());
			Assert::IsTrue(inventory->addItem(new Sword()), L"Sword not added", LINE_INFO());
		}

		TEST_METHOD(InventoryMaxQuantityTest)
		{
			Inventory* inventory = new Inventory(2);
			Assert::IsTrue(inventory->addItem(new Sword()), L"Sword not added", LINE_INFO());
			Assert::IsTrue(inventory->addItem(new Key()), L"Key not added", LINE_INFO());
			Assert::IsTrue(inventory->addItem(new Sword()), L"Sword not added", LINE_INFO());
			Assert::IsFalse(inventory->addItem(new HealthPotion()), L"Potion was added", LINE_INFO());
		}

		TEST_METHOD(InventoryGetItemTest)
		{
			Inventory* inventory = new Inventory();
			Sword* sword = new Sword();
			inventory->addItem(sword);
			Sword* gotsword = (Sword*)inventory->getItem(InventoryItem::SWORD);
			Assert::AreEqual(sword->getID(), gotsword->getID(), L"Objects are not the same", LINE_INFO());
			Assert::AreEqual(sword->getName(), gotsword->getName(), L"Objects are not the same", LINE_INFO());
		}

	};
}