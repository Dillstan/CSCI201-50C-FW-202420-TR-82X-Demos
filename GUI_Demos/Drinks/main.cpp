#include <CtrlLib/CtrlLib.h>
#include <AutoScroller/AutoScroller.h>
#define LAYOUTFILE <Drinks/drinks.lay>
#include <CtrlCore/lay.h>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "drinks.h"

using namespace Upp;

class MyAppWindow : public WithMainAppWindow<TopWindow>
{
	public:
		MyAppWindow();
		//~MyAppWindow();
		void checkPrice();
		//void Paint(Draw&);
		
	private:
		AutoScroller scroller;
		WithDrinks<ParentCtrl> scroller_view;
		Option flavor[NUM_FLAV];
		drink d;
		std::vector<drink> order;
		OptionTree optree;
};

MyAppWindow::MyAppWindow()
{
	CtrlLayout(*this, "Drink Order Form");
	Sizeable().Zoomable();
	scroller.EnableScroll();
	Add(scroller.SizePos());
	CtrlLayout(scroller_view);
	scroller.AddPane(scroller_view);
	scroller_view.base = -1;
	scroller_view.temp = -1;
	scroller_view.size = -1;
	for(int i = 0; i < NUM_DAIRY; i++)
	{
		scroller_view.dairy.Add(dairyStr[i]);
	}
	scroller_view.dairy.GoBegin();
	int l = 0;
	int optionSize = 120;
	int checkDist = 20;
	
	int checkCount = 0;
	optree.SetRoot("All Flavors");
	for(int i = 0; i < NUM_FLAV; i++)
	{
		//flavor[i].SetLabel(flavStr[i].c_str());
		//scroller_view.flavorOptions.Add(flavor[i].LeftPosZ(l+optionSize*(i%2),optionSize).TopPosZ(0 + checkDist * checkCount));
		//if(i%2 == 1)
		//{
		//	checkCount++;
		//}
		optree.Add(0,flavor[i],flavStr[i].c_str());
		flavor[i] << [&, this, i]
		{
			if(flavor[i].Get())
			{
				d.addFlavor(flavs[i]);
			}
			else
			{
				d.removeFlavor(flavs[i]);
			}
			checkPrice();
		};
	}
	scroller_view.flavorOptions.Add(optree.SizePos());
	//optree. << [&, this]
	//{
			
	//};
	
	scroller_view.base << [&, this]
	{
		baseType b = static_cast<baseType>((int)scroller_view.base);
		d.setBase(b);
		checkPrice();
	};
	
	scroller_view.size << [&, this]
	{
		sizeType s = static_cast<sizeType>((int)scroller_view.size);
		d.setSize(s);
		checkPrice();
	};
	scroller_view.temp << [&, this]
	{
		tempType t = static_cast<tempType>((int)scroller_view.temp);
		d.setTemperature(t);
		checkPrice();
	};
	
	scroller_view.dairy << [&, this]
	{
		d.setDairy(scroller_view.dairy.GetData().ToStd());
		checkPrice();
	};
	
	
	
}

//void MyAppWindow::Paint(Draw& w)
//{
	//w.DrawRect(GetSize(), Color(165,156,149));
//}

void MyAppWindow::checkPrice()
{
	if((int)scroller_view.temp != -1 && (int)scroller_view.size != -1 && (int)scroller_view.base != -1)
	{
			std::ostringstream priceStr;
			priceStr << std::setprecision(2) << std::fixed << std::showpoint;
			priceStr << "$" << d.getPrice();
			scroller_view.price.SetData(priceStr.str());
	}
}


GUI_APP_MAIN
{
	MyAppWindow w;
	w.Run();
}
