#pragma once
#include <list>
#include <memory>

class Obj;		//¸×½‚ÌÌßÛÄÀ²ÌßéŒ¾
using namespace std;

using uniqueObj = shared_ptr <Obj>;
using uniqueObjList = list<uniqueObj>;
using sharedListObj = shared_ptr <uniqueObjList>;
using weekListObj = weak_ptr <uniqueObjList>;
using ListObj_itr = uniqueObjList::iterator;

struct AddObjList
{
	ListObj_itr operator()(weekListObj objList, uniqueObj objPtr)
	{
		objList.lock()->push_back(std::move(objPtr));
		ListObj_itr itr = objList.lock()->end();
		itr--;
		return itr;
	}
};
