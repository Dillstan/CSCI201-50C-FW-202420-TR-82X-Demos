#include <CtrlLib/CtrlLib.h>
#include <AutoScroller/AutoScroller.h>
#define LAYOUTFILE <Drinks/drinks.lay>
#include <CtrlCore/lay.h>
#include "drinks.h"

using namespace Upp;

class MyAppWindow : public WithMainAppWindow<TopWindow>
{
	public:
		MyAppWindow();
		//~MyAppWindow();
		
	private:
		AutoScroller scroller;
		WithDrinks<ParentCtrl> scroller_view;
		Option flavor[NUM_FLAV];
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
	int l = 0;
	int optionSize = 120;
	int checkDist = 20;
	int checkCount = 0;
	for(int i = 0; i < NUM_FLAV; i++)
	{
		flavor[i].SetLabel(flavStr[i].c_str());
		scroller_view.flavorOptions.Add(flavor[i].LeftPosZ(l+optionSize*(i%2),optionSize).TopPosZ(0 + checkDist * checkCount));
		if(i%2 == 1)
		{
			checkCount++;
		}
	}
	
	
}



GUI_APP_MAIN
{
	MyAppWindow w;
	w.Run();
}
