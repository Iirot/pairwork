#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

class TextEditor {
	public:
		TextEditor();
		void init_editor();
		bool save_file(string s);
		bool load_file(string s);
		void insert_text();
	private:
		bool unsaved_changes;
		bool insert_mode;
};

TextEditor::TextEditor() {
	unsaved_changes = false;
	insert_mode = false;
}

void TextEditor::insert_text() { 
}

void TextEditor::init_editor() {

}
/* kopioitu */
class GapBuffer {
	
	private:

		char* start_ptr;
		char* cursor_ptr;
		char* gap_end_ptr;
		char* end_ptr;
		size_t capacity;
	
		void updateCapacity() {
			if (cursor_ptr == gap_end_ptr) {
				capacity *= 2;
				char* tmp_ptr = new char[capacity];
				copy(start_ptr, cursor_ptr, tmp_ptr);
				copy(gap_end_ptr, end_ptr, tmp_ptr + capacity - (end_ptr - gap_end_ptr));
	
				cursor_ptr = tmp_ptr + (cursor_ptr - start_ptr);
				gap_end_ptr = tmp_ptr + capacity - (end_ptr - gap_end_ptr);
				end_ptr = tmp_ptr + capacity;
	
				delete[] start_ptr;
				start_ptr = tmp_ptr;
			};
		};

	public:
		GapBuffer(size_t aInitialCapacity = 256) {
			capacity = aInitialCapacity;
			start_ptr = new char[capacity];
			cursor_ptr = start_ptr;
			end_ptr = start_ptr + capacity;
			gap_end_ptr = end_ptr;
		};

		~GapBuffer() {
			delete[] start_ptr;
		};

		GapBuffer(const GapBuffer& rhs) {
			capacity = rhs.capacity;
			start_ptr = new char[capacity];
			copy(rhs.start_ptr, rhs.end_ptr, start_ptr);
			end_ptr = start_ptr + capacity;
			gap_end_ptr = start_ptr + (rhs.gap_end_ptr - rhs.start_ptr);
		};

		friend void swap(GapBuffer& lhs, GapBuffer& rhs) {
			swap(lhs.capacity, rhs.capacity);
			swap(lhs.start_ptr, rhs.start_ptr);
			swap(lhs.cursor_ptr, rhs.cursor_ptr);
			swap(lhs.end_ptr, rhs.end_ptr);
			swap(lhs.gap_end_ptr, rhs.gap_end_ptr);
		};

		GapBuffer& operator=(GapBuffer rhs) {
			swap(*this, rhs);
			return *this;
		};

		void insert(char c) {
			(*cursor_ptr++) = c;
			updateCapacity();
		};

		void removeLastChar() {
			--cursor_ptr;
		};

		void moveCursor(ptrdiff_t aOffset = 1) {
			if (aOffset > 0) {
			
				copy(gap_end_ptr, gap_end_ptr + aOffset, cursor_ptr);
				gap_end_ptr += aOffset;
				cursor_ptr += aOffset;
			} else if (aOffset < 0) {
				copy(cursor_ptr + aOffset, cursor_ptr, gap_end_ptr + aOffset);
				gap_end_ptr += aOffset;
				cursor_ptr += aOffset;
			};
		};
};

int main() {
	TextEditor t = TextEditor();
	GapBuffer gb = GapBuffer();
	t.TextEditor::init_editor();
	return 0;
}

