#pragma once
#include <list>
#include <memory>

class Obj;		//¸×½‚ÌÌßÛÄÀ²ÌßéŒ¾
using namespace std;

using sharedObj = shared_ptr <Obj>;
using sharedObjList = list<sharedObj>;
using sharedListObj = shared_ptr <sharedObjList>;
using weekListObj = weak_ptr <sharedObjList>;
using  ListObj_itr = sharedObjList::iterator;


struct AddObjList
{
	ListObj_itr operator()(weekListObj objList, sharedObj objPtr)
	{
		objList.lock()->push_back(std::move(objPtr));
		ListObj_itr itr = objList.lock()->end();
		itr--;
		return itr;
	}
};
