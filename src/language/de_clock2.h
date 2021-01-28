#ifndef WORDCLOCK_GRID_LANG_de_clock2_H
#define WORDCLOCK_GRID_LANG_de_clock2_H

class Grid_de_clock2 {
	public:
	static int time_it_is[5];
	static int time_minutes[12][12];
	static int time_hours[12][6];
    
	static void setSecond(int second);
	static void setSingleMinute(int minute);
	static void setTime(int hour, int minute);
	static void showGrid(bool inLoop);
};

typedef class Grid_de_clock2 Grid;

#endif
