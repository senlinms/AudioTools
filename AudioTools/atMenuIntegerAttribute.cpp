//
//  atMenuIntegerAttribute.cpp
//  AudioTools
//
//  Created by Alexandre Arsenault on 2016-04-08.
//  Copyright © 2016 Alexandre Arsenault. All rights reserved.
//

#include "atMenuIntegerAttribute.hpp"
#include <OpenAX/Button.h>
#include <OpenAX/ColorPicker.h>
#include <OpenAX/Label.h>
#include <OpenAX/TextBox.h>
#include <OpenAX/Toggle.h>
#include <OpenAX/WindowManager.h>
#include <OpenAX/Xml.h>

namespace at {
namespace inspector {
	IntegerAttribute::IntegerAttribute(
		const ax::Rect& rect, const std::string& name, const std::string& value, ax::Event::Function fct)
		: _name(name)
	{
		win = ax::Window::Create(rect);
		win->event.OnPaint = ax::WBind<ax::GC>(this, &IntegerAttribute::OnPaint);

		if (fct) {
			win->AddConnection(Events::ASSIGN_VALUE, fct);
		}

		ax::Label::Info labelInfo;
		labelInfo.normal = ax::Color(0.98);
		labelInfo.contour = ax::Color(0.88);
		labelInfo.font_color = ax::Color(0.0);
		labelInfo.font_size = 12;
		labelInfo.font_name = "fonts/Lato.ttf";
		labelInfo.alignement = ax::Utils::Alignement::axALIGN_LEFT;

		ax::Point pos(0, 0);
		win->node.Add(ax::shared<ax::Label>(ax::Rect(pos, ax::Size(90, 25)), labelInfo, _name));

		ax::TextBox::Info txtInfo;
		txtInfo.normal = ax::Color(1.0);
		txtInfo.hover = ax::Color(1.0);
		txtInfo.selected = ax::Color(1.0);
		txtInfo.highlight = ax::Color(0.4f, 0.4f, 0.6f, 0.2f);
		txtInfo.contour = ax::Color(0.88);
		txtInfo.cursor = ax::Color(1.0f, 0.0f, 0.0f);
		txtInfo.selected_shadow = ax::Color(0.8f, 0.8f, 0.8f);
		txtInfo.font_color = ax::Color(0.0);

		ax::NumberScroll::Info scroll_info;
		scroll_info.up_btn = "resources/drop_up.png";
		scroll_info.down_btn = "resources/drop_down.png";

		// Txt box.
		scroll_info.txt_info.normal = ax::Color(1.0);
		scroll_info.txt_info.hover = ax::Color(1.0);
		scroll_info.txt_info.selected = ax::Color(1.0);
		scroll_info.txt_info.highlight = ax::Color(0.4f, 0.4f, 0.6f, 0.2f);
		scroll_info.txt_info.contour = ax::Color(0.88);
		scroll_info.txt_info.cursor = ax::Color(1.0f, 0.0f, 0.0f);
		scroll_info.txt_info.selected_shadow = ax::Color(0.8f, 0.8f, 0.8f);
		scroll_info.txt_info.font_color = ax::Color(0.0);

		// Button.
		scroll_info.btn_info.normal = ax::Color(0.92);
		scroll_info.btn_info.hover = ax::Color(0.94);
		scroll_info.btn_info.clicking = ax::Color(0.90);
		scroll_info.btn_info.selected = scroll_info.btn_info.normal;
		scroll_info.btn_info.contour = ax::Color(0.88);
		scroll_info.btn_info.font_color = ax::Color(0.0, 0.0);


		double v = 0.0;
		
		if(!value.empty()) {
			v = std::stod(value);
		}

		auto w_scroll = ax::shared<ax::NumberScroll>(
			ax::Rect(ax::Point(90, 0), ax::Size(rect.size.x - 90, rect.size.y + 1)),
			ax::NumberScroll::Events(), scroll_info, v, ax::Utils::Control::Type::INTEGER,
			ax::Utils::Range<double>(0.0, 10000.0), 1.0);

		win->node.Add(w_scroll);
	}

	void IntegerAttribute::OnValueChange(const ax::NumberScroll::Msg& msg)
	{
	}

	void IntegerAttribute::OnPaint(ax::GC gc)
	{
		const ax::Rect rect(win->dimension.GetDrawingRect());

		gc.SetColor(ax::Color(0.96));
		gc.DrawRectangle(rect);

		gc.SetColor(ax::Color(0.88));
		gc.DrawRectangleContour(ax::Rect(rect.position, ax::Size(rect.size.x, rect.size.y + 1)));

		gc.SetColor(ax::Color(0.88));
		gc.DrawLine(ax::Point(91, 0), ax::Point(91, rect.size.y + 1));
	}
}
}