/*************************************************************************/
/*  spin_box.h                                                           */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           MESH ENGINE                                */
/*                      https://mesh-engine.com                          */
/*************************************************************************/
/* Copyright (c) 2007-2021 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2021 Mesh Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef SPIN_BOX_H
#define SPIN_BOX_H

#include "scene/gui/line_edit.h"
#include "scene/gui/range.h"
#include "scene/main/timer.h"

class SpinBox : public Range {
	GDCLASS(SpinBox, Range);

	LineEdit *line_edit;
	int last_w = 0;
	bool update_on_text_changed = false;

	Timer *range_click_timer;
	void _range_click_timeout();
	void _release_mouse();

	void _text_submitted(const String &p_string);
	virtual void _value_changed(double) override;
	void _text_changed(const String &p_string);

	String prefix;
	String suffix;

	void _line_edit_input(const Ref<InputEvent> &p_event);

	struct Drag {
		float base_val = 0.0;
		bool allowed = false;
		bool enabled = false;
		Vector2 capture_pos;
		float diff_y = 0.0;
	} drag;

	void _line_edit_focus_exit();

	inline void _adjust_width_for_icon(const Ref<Texture2D> &icon);

protected:
	virtual void gui_input(const Ref<InputEvent> &p_event) override;

	void _notification(int p_what);

	static void _bind_methods();

public:
	LineEdit *get_line_edit();

	virtual Size2 get_minimum_size() const override;

	void set_horizontal_alignment(HorizontalAlignment p_alignment);
	HorizontalAlignment get_horizontal_alignment() const;

	void set_editable(bool p_enabled);
	bool is_editable() const;

	void set_suffix(const String &p_suffix);
	String get_suffix() const;

	void set_prefix(const String &p_prefix);
	String get_prefix() const;

	void set_update_on_text_changed(bool p_enabled);
	bool get_update_on_text_changed() const;

	void apply();

	SpinBox();
};

#endif // SPIN_BOX_H