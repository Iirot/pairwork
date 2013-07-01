
#include <ncurses.h>
#include <fstream>
using namespace std;

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
bool open_file(char *f);
int main() {

	WINDOW *text_area;
	WINDOW *status_area;
	int ch;
	int winx = 1, winy = 1;
	bool cmd_mode = true;
	bool exit = false;
	//bool unsaved_changes = false;
	char *filename[55];
	initscr();
	cbreak();
	noecho();
	nonl(); // göö

	while (!exit) {
		ch = wgetch(text_area); 
		text_area = create_newwin(LINES - 10, COLS, 0, 0);
		scrollok(text_area, true);
		keypad(text_area, true);
		wrefresh(text_area);
		status_area = create_newwin(10, COLS, LINES - 10, 0);
		mvwaddnstr(status_area, 1, 1, "text editor", -1);
		wrefresh(status_area);

		if (cmd_mode) {
			switch (ch) {
				case (int) ':':
					destroy_win(status_area);
					status_area = create_newwin(10, COLS, LINES - 10, 0);
					mvwaddnstr(status_area, 2, 1, "Command: ", -1);
					//wrefresh(status_area);
					break;
				case (int) 'o':			// avaa uusi tiedosto
					echo();
					/**

					  def_prog_mode();
					  endwin();

					  open_file();
					  reset_prog_mode();

					 */
					destroy_win(status_area);
					status_area = create_newwin(10, COLS, LINES - 10, 0);
					mvwaddnstr(status_area, 2, 1, "open file: ", -1);
					wgetstr(status_area, *filename);
					open_file(*filename);
					wrefresh(status_area);

					break;
				case (int) 's':			// tallenna tiedosto
					destroy_win(status_area);
					status_area = create_newwin(10, COLS, LINES - 10, 0);
					mvwaddnstr(status_area, 2, 1, "save file: ", -1);
					break;
				case (int) 'i':			// siirry kirjoitustilaan
					destroy_win(status_area);
					status_area = create_newwin(10, COLS,  LINES - 10, 0);
					wattron(status_area, A_BOLD);
					mvwaddnstr(status_area, 2, 1, "ins", -1);
					mvwaddnstr(status_area, 3, 1, "press ESCAPE KEY to switch back to command mode", -1);
					wattroff(status_area, A_BOLD);
					cmd_mode = false;
					break;
				case (int) 'q':			// poistu editorista
					exit = true;
				case ERR:
					break;
				default:
					mvwaddnstr(status_area, 5, 1, "unknown command", -1);
					mvwaddnstr(status_area, 6, 1, "Try: (i)nsert, (o)pen, (s)ave, (q)uit", -1);
					break;
			}
			wrefresh(text_area);
			wrefresh(status_area);
		} else {
			switch (ch) {
				case (127):		// backspace
					if (winx > 1) { --winx; }
					else { --winy; winx = COLS; }
					break;
				case (27):		// escape
					destroy_win(status_area);
					status_area = create_newwin(10, COLS, LINES - 10, 0);
					wattron(status_area, A_BOLD);
					mvwaddnstr(status_area, 2, 1, "cmd", -1);
					wattroff(status_area, A_BOLD);
					wrefresh(status_area);
					cmd_mode = true;
					break;
				case (13):		// enter
					++winy;
					winx = 1;
					break;
				case KEY_UP:
					if (winy > 1) { --winy; }
					break;
				case KEY_DOWN:
					if (winy < LINES) { ++winy; }
					break;
				case KEY_LEFT:
					if (winx > 1) { --winx; }
					break;
				case KEY_RIGHT:
					if (winx < COLS) { ++winx; }
					break;
				default:
					mvwaddch(text_area, winy, winx++, ch);
					break;
			}
			wrefresh(text_area);
			//wrefresh(status_area);
		}
	}
	endwin();
	return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx) {
	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	box(local_win, 0, 0);
	wrefresh(local_win);
	return local_win;
}

void destroy_win(WINDOW *local_win) {
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}

bool open_file(char *f) {
	ofstream file;
	file.open(f);
	
	if (file.is_open()) { 
		file.close(); 
		return true; 
	}
	else { return false; }
}

