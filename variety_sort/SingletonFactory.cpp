#include "stdafx.h"
#include "SingletonFactory.h"
#include "FactoryInsertion.h"
#include "FactorySelection.h"
#include "FactoryBubble.h"
#include "FactoryHeap.h"
#include "FactoryQuick.h"
#include "FactoryRadix.h"
#include "FactoryMerge.h"

//下面之所以能够调用私有成员变量，应该是因为他们是static的缘故

SingletonFactory *SingletonFactory::m_Instance = NULL;
SingletonFactory::GC SingletonFactory::gc;

FactoryBubble *FactoryBubble::m_InstanceBubble = NULL;
FactoryBubble::GC FactoryBubble::gc;

FactorySelection *FactorySelection::m_InstanceSelection = NULL;
FactorySelection::GC FactorySelection::gc;

FactoryInsertion *FactoryInsertion::m_InstanceInsertion = NULL;
FactoryInsertion::GC FactoryInsertion::gc;

FactoryHeap *FactoryHeap::m_InstanceHeap = NULL;
FactoryHeap::GC FactoryHeap::gc;

FactoryQuick *FactoryQuick::m_InstanceQuick = NULL;
FactoryQuick::GC FactoryQuick::gc;

FactoryRadix *FactoryRadix::m_InstanceRadix = NULL;
FactoryRadix::GC FactoryRadix::gc;

FactoryMerge *FactoryMerge::m_InstanceMerge = NULL;
FactoryMerge::GC FactoryMerge::gc;


SingletonFactory *SingletonFactory::GetInstance(FactoryEnum factory)
{
	

	/* 
	*   每一个工厂，一个实例,能够调用派生类的private成员变量是因为他们声明singletonfactory为friend类型
	*/
		switch (factory)
		{
		case kFactory_bubble:
			if(FactoryBubble::m_InstanceBubble == NULL)
			{
				FactoryBubble::m_InstanceBubble = new FactoryBubble();
			}
			return FactoryBubble::m_InstanceBubble;
			

		case kFactory_selection:
			if(FactorySelection::m_InstanceSelection == NULL)
			{
				FactorySelection::m_InstanceSelection = new FactorySelection();
			}
			return FactorySelection::m_InstanceSelection;

		case kFactory_insertion:
			if(FactoryInsertion::m_InstanceInsertion == NULL)
			{
				FactoryInsertion::m_InstanceInsertion = new FactoryInsertion();
			}
			return FactoryInsertion::m_InstanceInsertion;

		case  kFactory_heap:
			if(FactoryHeap::m_InstanceHeap == NULL)
			{
				FactoryHeap::m_InstanceHeap = new FactoryHeap();
			}
			return FactoryHeap::m_InstanceHeap;

		case  kFactory_quick:
			if(FactoryQuick::m_InstanceQuick == NULL)
			{
				FactoryQuick::m_InstanceQuick = new FactoryQuick();
			}
			return FactoryQuick::m_InstanceQuick;

		case kFactory_radix:
			if (FactoryRadix::m_InstanceRadix == NULL) {
				FactoryRadix::m_InstanceRadix = new FactoryRadix();
			}
			return FactoryRadix::m_InstanceRadix;

		case kFactory_merge:
			if (FactoryMerge::m_InstanceMerge == NULL) {
				FactoryMerge::m_InstanceMerge = new FactoryMerge();
			}
			return FactoryMerge::m_InstanceMerge;


		default:
			// This is the default, you can change the implementation
			if(FactoryBubble::m_InstanceBubble == NULL)
			{
				FactoryBubble::m_InstanceBubble = new FactoryBubble();
			}
			return FactoryBubble::m_InstanceBubble;
		}
	
	//return m_Instance;
}
