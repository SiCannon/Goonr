#include "screenutil.h"
#include "transform.h"

void print_debug_info(Mouse *mouse, Transform *tf_world, long ticks)
{
	//printText(true, rasterLeft, rasterBottom, "", 128, 128, 0);
	//printInt(true, rasterLeft, rasterBottom, mouse->x, 128, 128, 0);
	/*printText(false, 0, 0, ", ", 128, 128, 0);
	printInt(false, 0, 0, mouse->y, 128, 128, 0);

	printText(false, 0, 0, " - ", 128, 128, 0);
	printFloat(false, 0, 0, tf_world->scale, 128, 128, 0);

	printText(false, 0, 0, " - ", 128, 128, 0);
	printFloat(false, 0, 0, tf_world->translate_x, 128, 128, 0);

	printText(false, 0, 0, " :: ", 128, 128, 0);*/

	textYellow();
	textResetBottomLeft();
	textOut("ticks: ");
	textOutInt(ticks);

	//printText(true, rasterLeft, rasterBottom, "ticks: ", 255, 255, 0);
	//printInt(true, rasterLeft, rasterBottom, ticks, 255, 255, 0);
}
